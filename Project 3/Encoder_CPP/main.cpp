/*Jason Chalom 711985 and Ariel Rosenfeld 2013*/

#include <iostream>
#include <cstdio>

#include <stdlib.h>
#include <string>
#include <math.h>

using namespace std;

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
      if(trav->next->frequency < minNode -> frequency)
	{
	  if (minNode == FQ)
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

      traverseData(FQ);
    }
  else
    {
      //cheerz
    }
  
  return 0;
}
