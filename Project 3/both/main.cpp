/*Jason Chalom 711985 and Ariel Rosenfeld 2013*/
/*Some code is Richard's*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

//#include <stdlib.h>
//#include <string>
#include <math.h>

#define MAX_UNIQUE_CHARS 256
#define MAX_LENGTH 255
#define MAX_CODE_LENGTH 256

using namespace std;

struct EncodedChar
{
  string code;
  struct EncodedChar *next;
};

void AddEncChar(EncodedChar *EC, string code)
{
  EncodedChar *trav = EC;

  while(trav != NULL)
    {
      trav = trav->next;
    }
  EncodedChar *node = new EncodedChar();
  node -> code = code;
  node -> next = NULL;
  trav->next = node;
}

struct TreeNode
{
  char character;
  int frequency;
	
  struct TreeNode *left;
  struct TreeNode *right;
};

struct Tree
{
  TreeNode *root;
};

struct FreqQueue
{
  char character;
  int frequency;
  FreqQueue *next;
};

//init FreqQueue
FreqQueue *initFreq(char character)
{
  FreqQueue *FQ = new FreqQueue();
  FQ -> character = character;
  FQ -> frequency = 1; 
  FQ -> next = NULL;
  
  return FQ;
}

void traverseData(FreqQueue *FQ)
{
  FreqQueue *trav = FQ;
  cout << "\n" << "Will print out data structure sequentially from root." << endl;
  //cout << "Character: " << trav->character << " |frequency: " << trav->frequency << endl;
  while(trav != NULL)
    {
      cout << "Character: " << trav->character << " |frequency: " << trav->frequency << endl;
      trav = trav->next;
    }
}

//find in queue then return node or NULL
FreqQueue *SearchQueue(FreqQueue *FQ, char character)
{
  if(FQ == NULL)
    {
      return NULL;
    }

  //FreqQueue *trav = FQ;
  if (character == FQ->character)
    {
      return FQ;
    }
  else if (FQ->next != NULL && character != FQ->character)
    {
      SearchQueue(FQ->next, character);
    }
  else //if(trav->next == NULL && character != trav->character)
    {
      return NULL;
    }
 
}

//enqueue
void enqueue(FreqQueue *FQ, char character)
{
  if(FQ == NULL)
    {
      FQ = new FreqQueue();
      FQ -> character = character;
      FQ -> frequency = 1;
      FQ -> next = NULL;
    }
  else
    {
      FreqQueue *trav = FQ;
      FreqQueue *node = new FreqQueue();
      //FQ = new FreqQueue();
      node -> character = character;
      node -> frequency = 1;
      node -> next = NULL;
      //FQ = node
      while(trav->next != NULL)
	{
	  trav = trav->next;
	}
      trav->next = node;

      //traverseData(FQ);
    }
}

//dequeue
//not needed for now
void delNode(FreqQueue *FQ, FreqQueue *node)
{
  FreqQueue *trav = FQ;
  if(FQ == node)
    {      
      FreqQueue *tmp = FQ;
      FQ = FQ -> next;
      free(tmp);
    }
  else if (trav->next == node)
    {
      FreqQueue *parent = trav;
      trav = trav->next;
      parent -> next = trav -> next;
      free(trav);
    }
  else
    {
      while(trav->next != node)
	{
	  trav = trav->next;
	}
      delNode(trav, node);
      /*      
	      FreqQueue *parent = trav;
	      trav = trav->next;
      
	      parent -> next = trav -> next;
	      free (trav);
      */
    }
}

FreqQueue *dequeue(FreqQueue *FQ)
{
  FreqQueue *head = FQ;
  FQ = FQ->next;
  return head;
}

//min Sort queue
void minSort (FreqQueue *FQ)
{
  //traverse
  FreqQueue *trav = FQ;
  FreqQueue *minNode = FQ;
  FreqQueue *tmp = FQ;
  //FreqQueue *tmp2 = FQ;

  while (trav->next != NULL)
    {
      if(trav->next->frequency < minNode -> frequency)// && trav->next->frequency > 0)
        {
	  //if (minNode == FQ)
	  {
	    tmp = minNode;
	    minNode -> character = trav->next->character;
	    minNode -> frequency = trav->next->frequency;
	    trav -> next -> character = tmp -> character;
	    trav -> next -> frequency = tmp -> frequency;
	  }
        }
      trav = trav->next;
    }

  trav = FQ;
  if (trav -> next != NULL)
    {
      minSort (trav -> next);
    }

  free(tmp);
}

/*some tree code is Richard's:*/

TreeNode* tn_init(int freq, char c){
  TreeNode *tn = new TreeNode();
  tn->frequency = freq;
  tn->character = c;

  tn->left = NULL;
  tn->right = NULL;
  return tn;
}

Tree* tree_init(int freq, char c){
  Tree *t = (Tree*) malloc(sizeof(Tree));
  t->root = tn_init(freq, c);
  return t;
}

Tree* tree_merge(Tree *left, Tree *right){
  Tree *t = tree_init(left->root->frequency + right->root->frequency, '\0');
    
  t->root->left  = left->root;
  t->root->right = right->root;

  // Just free the old tree dummy heads, not the actual trees
  free(left);
  free(right);

  return t;
}
// Priority Queue Structure
struct _PQueue{
  int size;
  int capacity;
  int*  priority;
  Tree** data;

};
typedef struct _PQueue PQueue;

// Create a new empty priority queue
PQueue* pq_init();

// Insert an item into the queue in the correct place so that elements are ordered by priority
void pq_enqueue(PQueue *p, Tree *t, int priority);

// Remove the item with the lowest priority
Tree* pq_dequeue(PQueue *p);

// Print all the trees stored in the priority queue.
// Use tree_print to print each item.
void pq_print(PQueue *p);

// Print all the characters in the roots stored in the priority queue.
void pq_print_chars(PQueue *p);

// Print all the frequencies in the roots stored in the priority queue.
void pq_print_freq(PQueue *p);

/****************** Priority Queue Implementations ****************************************************/
// Create a new empty priority queue
PQueue* pq_init(){
  PQueue *p = (PQueue*) malloc(sizeof(PQueue));

  p->data = (Tree**) malloc(sizeof(Tree*)*MAX_UNIQUE_CHARS);
  p->priority = (int*) malloc(sizeof(int)*MAX_UNIQUE_CHARS);
  if(p->data == NULL || p->priority == NULL){
    printf("Memory Allocation failed.\n");
    exit(1);
  }
  p->size = 0;
  p->capacity = MAX_UNIQUE_CHARS;

  return p;
}
// Insert an item into the queue in the correct place so that elements are ordered by priority
void pq_enqueue(PQueue *p, Tree *t, int priority){
  int i = 0;
  while(i < p->size && priority < p->priority[i])
    i++;

  while(i < p->size && priority == p->priority[i] && t->root->character > p->data[i]->root->character)
    i++;

  int j;
  for(j = p->size; j >= i; j--){
    p->data[j] = p->data[j-1];
    p->priority[j] = p->priority[j-1];
  }

  p->priority[i] = priority;
  p->data[i] = t;
  p->size++;
}



// Remove the item with the lowest priority
Tree* pq_dequeue(PQueue *p){
  if(p->size == 0) return NULL;

  p->size--;

  Tree *t = p->data[p->size];
  p->data[p->size] = NULL;

  return t;
}


// Print a tree node in a pre-order traversal
//   Root[left traversal][right traversal]
void tn_print(TreeNode *t){
  if(t->left == NULL || t->right == NULL){
    printf("'%c'(%d)", t->character, t->frequency);
  }else{
    printf("%d[", t->frequency);
    tn_print(t->left);
    printf("][");
    tn_print(t->right);
    printf("]");
  }
}
// Print a tree using a pre-order traversal
void tree_print(Tree *t){
  if(t->root == NULL) return;

  tn_print(t->root);
}



// Print all the trees stored in the priority queue.
// Use tree_print to print each item.
void pq_print(PQueue *p){
  int i;
  for(i = p->size -1; i >= 0; i--){
    tree_print(p->data[i]);
    printf(", ");
  }
  printf("\n");
}

// Print all the characters in the roots stored in the priority queue.
void pq_print_chars(PQueue *p){
  int i;
  for(i = p->size -1; i > 0; i--){
    printf("%c ", p->data[i]->root->character);
  }
  printf("%c\n", p->data[i]->root->character);
}
// Print all the frequencies in the roots stored in the priority queue.
void pq_print_freq(PQueue *p){
  int i;
  for(i = p->size -1; i > 0; i--){
    printf("%d ", p->data[i]->root->frequency);
  }
  printf("%d\n", p->data[i]->root->frequency);
}

string Traversal(TreeNode *head, string encode)
{
  string decode = "";
  TreeNode *t = head;
  
  char c;
  for(int i = 0; i < encode.length(); i++)
    {
      c = encode[i];

      if(c == '0')
	{
	  t = t->left;
	}

      else
	{
	  t = t->right;
	} 

      if(t->left == NULL){
	decode += t->character;
	t = head;
      }

    }
  return decode;
  /*
    if(!encode.empty())
    {
    if((t->right == NULL) && (t->left == NULL))
    {
    //here lies some leaves to clean up
    decode += t->character;
    t = head;
    }

    //0 left
    if(encode.at(0) == 0)
    {
    //remove the 0
    encode.erase(0,0);
    decode += Traversal(head, t->left, encode);
    }

    //1 right
    else if(encode.at(1) == 1)
    {
    //remove the 1
    encode.erase(0,0);
    decode += Traversal(head, t->right, encode);
    }
    return decode;
    }
  */
}


int main()
{
    //read first two lines
    string CharSet;
    string CharCount;

    getline(cin, CharSet);
    getline(cin, CharCount);

    FreqQueue *FQ = new FreqQueue();

    if(!CharSet.empty())
    {
      //FQ -> character = CharSet.at(0);
      //FQ -> frequency = CharCount.at(0);
      //FQ -> next = NULL;

      FreqQueue *trav = FQ;
	
      trav -> character = CharSet.at(0);
      trav -> frequency = CharCount.at(0);
      trav -> next = NULL;
	
      for(int i = 0; CharSet[i] != '\0'; i++)
	{
	  //cout<<"Char Set at i: "<<CharSet[i]<<endl;
	  if (CharSet[i] != ' ')
	    {
	      cout<<"CharSet at i: "<<CharSet[i]<<endl;
	      //probably bad because of double digits ect
	      //rather use whitespace finding ect...

	      //trav = trav -> next;
	      trav->next = new FreqQueue();

	      trav->next -> character = CharSet.at(i);
	      trav->next -> frequency = CharCount.at(i)-'0';
	      trav->next -> next = NULL;

	      trav = trav->next;
	    }
	}

      PQueue *p = pq_init();
      Tree *t;

      trav = FQ;

      while(trav != NULL){
	t = tree_init(trav->frequency, trav->character);
	pq_enqueue(p, t, trav->frequency);
	trav = trav->next;
      }
      //pq_print(p);

      Tree *s;

      while(p->size > 1){
	t = pq_dequeue(p);
	s = pq_dequeue(p);

	t = tree_merge(t, s);
            pq_enqueue(p, t, t->root->frequency);
        }
        //free(s);
        //free(p);

        t = pq_dequeue(p);
	
	//cout<<endl;
        tree_print(t);
	//cout<<endl<<endl;
        //read the encoded text now
        string encode = "";
        cin >> encode;
	
        //find decode
        string decode = "";
        decode = Traversal(t->root, encode);

        cout << decode;

    }  
    return 0;
}
