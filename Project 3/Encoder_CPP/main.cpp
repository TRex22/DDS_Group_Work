/*Jason Chalom 711985 and Ariel Rosenfeld 2013*/
/*Some code is Richard's*/

#include <iostream>
#include <cstdio>

#include <stdlib.h>
#include <string>
#include <math.h>

using namespace std;

struct TreeNode
{
  char character;
  int frequency;
	
  struct Tree *left;
  struct Tree *right;
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
  cout << "Character: " << trav->character << " |frequency: " << trav->frequency << endl;
  while(trav->next != NULL)
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

int main()
{
  //get input
  int OriginalBits;
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
	  cout<<input[i]<<endl;
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
      traverseData(FQ);

      minSort(FQ);

      //run a check
      traverseData(FQ);

      //now create a string which will contain a linear version of the binary tree which will then be created later.


      //actual tree merging stuff here
    }
  else
    {
      //cheerz
    }
  
  return 0;
}
