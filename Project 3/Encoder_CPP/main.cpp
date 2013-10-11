/*Jason Chalom 711985 and Ariel Rosenfeld 2013*/
/*Some code is Richard's*/

#include <iostream>
#include <cstdio>

#include <stdlib.h>
#include <string>
#include <math.h>

#define MAX_UNIQUE_CHARS 256
#define MAX_LENGTH 255

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

void Traversal(TreeNode *t, char **enc, string code)
{
  //string code = "t";
  //code = "";

  if (t->left !=NULL)
    {
      code = code+'0';
      Traversal(t->left, enc, code);
      //cout<<"\nLeft: "+code<<endl;
    }

  if (t->right != NULL) 
    {
      //cout<< "Code before: "<<code<<endl;
      code.erase(code.end()-1,code.end());
      //always go back one when going right so delete 1 left 
      //cout<< "Code after: "<<code<<endl;
      code = code+'1';
      Traversal(t->right, enc, code);
      //cout<<"\nRight: "+code<<endl;
    }

  if((t->right == NULL) && (t->left == NULL))
    {
      //enc[t->character] = (char*)malloc(256*sizeof(char));
      //cout << code+" char: "<<t->character << endl;
      //cout<<code<<endl;
      //enc[t->character] = new char[256];
      enc[t->character] = (char*)code.c_str();
      //cout << enc[t->character] << endl;
      code = "";
    }
}

int main()
{
  //get input
  int OriginalBits;
  int CodedBits;
  string input;
  //cin >> input;
  getline(cin, input);
  FreqQueue *FQ = new FreqQueue();//initFreq(input[0]);

  //cout << "\n: " << input[1]<<endl;

  if (!input.empty())
    {
      //i starts at 1;
      //input[i]
      FQ -> character = input.at(0);
      FQ -> frequency = 1;
      FQ -> next = NULL;
      //FQ = NULL;
      OriginalBits = 2; //one for first char and one for \0

      FreqQueue *SQ = FQ;// = new FreqQueue();
      for(int i = 1; input[i] != '\0'; i++)
	//for(int i = 1; i != input.end(); i++)
        {
	  //cout<<input[i]<<endl;
	  SQ = SearchQueue(FQ, input.at(i));
	  if(input.at(i) != '\0')
            {
	      if(SQ != NULL)
                {
		  //increase frequency
		  SQ -> frequency ++;
                }
	      else
                {
		  enqueue (FQ, input[i]);
                }
            }
	  OriginalBits ++;
        }
      //figure out original bits
      OriginalBits *= 8;
      //cout << "\nOriginal bits: "<<OriginalBits<<endl;
      //now sort the frequency queue

      //run a check
      //traverseData(FQ);

      PQueue *p = pq_init();
      Tree *t;

      FreqQueue *trav = FQ;

      while(trav != NULL){
	t = tree_init(trav->frequency, trav->character);
	pq_enqueue(p, t, trav->frequency);
	trav = trav->next;
      }
      pq_print_chars(p);
      pq_print_freq(p);

      Tree *s;

      while(p->size > 1){
	t = pq_dequeue(p);
	s = pq_dequeue(p);

	t = tree_merge(t, s);
	pq_enqueue(p, t, t->root->frequency);
      }

      t = pq_dequeue(p);
      //tree_print(t);
	
      //minSort(FQ);

      ////run a check
      //traverseData(FQ);

      //run the traversal and get stuff
      char **enc = (char**)malloc(256*sizeof(char*));
      string code = "";
      Traversal(t->root, enc, code);
      CodedBits = 0;
      string encode = "";
      for (int j = 0; j< input.length(); j++)
	{
	  //cout<<enc[input[j]]<<endl;
	  encode = encode + enc[input[j]];
	  //CodedBits += enc[input[j]].length();
	}
      cout<<encode<<endl;
      //cout<<"\ny: "<<enc['y']<<endl;
      CodedBits = encode.length();
      //cout<<endl;
      //cout << "\nb: " << enc['b']<<endl;
	
      cout << "Total Bits (Original):" <<OriginalBits<<endl;
      cout << "Total Bits (Coded):"<<CodedBits <<endl;
    }
  else
    {
      //cheerz
    }

  return 0;
}
