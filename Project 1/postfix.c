#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "postfix.h"
/*********************************************************/
// Allocate the stack and setup size and capacity
CharStack* stack_c_init(){
	CharStack *s=(CharStack*)malloc(sizeof(CharStack));
	s->capacity=DEFAULT_SIZE;
	s->size=-1;
	s->data=(char*)malloc((s->capacity)*sizeof(char));
	return s;
}

// Push to the top of stack
void stack_c_push(CharStack* s, char c){
	s->size++;
	s->data[s->size]=c;
}

// Pop off the top of stack
char stack_c_pop(CharStack* s){
	if(s->size>-1)
	{
		s->size--;
	}
	return s->data[s->size+1];
}

// Return the top of the stack without removing it
char stack_c_peek(CharStack* s){
	return s->data[(s->size)];
}

/*********************************************************/
// Allocate the stack and setup size and capacity
IntStack* stack_i_init(){
	IntStack *s=(IntStack*)malloc(sizeof(IntStack));
	s->capacity=DEFAULT_SIZE;
	s->size=-1;
	s->data=(int*)malloc(s->capacity*sizeof(int));
}

// Push to the top of stack
void stack_i_push(IntStack* s, int c){
	s->size++;
	s->data[s->size]=c;
}

// Pop from the top of stack
int  stack_i_pop(IntStack* s){
	if(s->size>-1)
	{
		s->size--;
	}
	return s->data[s->size+1];
}

// Return the top of the stack without removing it
int  stack_i_peek(IntStack* s){
	return s->data[(s->size)];
}

/*********************************************************/
int calculate(char* p){
	
	int i;
	IntStack *s=stack_i_init();
	
	for(i=0;i<DEFAULT_SIZE;i++)
	{
		int num1, num2;
		if(p[i]>='0' && p[i]<='9')
		{
			s->size++;
			s->data[s->size]=p[i]-'0';
		}
		else if(p[i]=='+'|p[i]=='-'|p[i]=='*'|p[i]=='/')
		{
			if(s->size>0)
			{
				num1=stack_i_pop(s);
				num2=stack_i_pop(s);
			
				switch(p[i])
				{
					case '+':
						stack_i_push(s, (num2+num1));
						break;
					case '-':
						stack_i_push(s, (num2-num1));
						break;
					case'*':
						stack_i_push(s, (num2*num1));
						break;
					case '/':
						stack_i_push(s, (num2/num1));
						break;
				}
			}
			else
			{
				return -2000;
				break;
			}			
		}
		else if(p[i]==NULL)
		{
			break;
		}
	}
	
	if(s->size>0)
	{
		return -1000;
	}
	else
	{
		int num=stack_i_pop(s);
		free(s);
		return num;
	}
}

char* convert(char* in){
	//initialise a stack
  //int DEFAULT = 10;
  CharStack *s=stack_c_init();
  char *out;
  out = (char*)malloc(DEFAULT_SIZE*sizeof(char));
  
  int i, outSize = 0;
  //for each char/token in the string do
  for(i=0;i<DEFAULT_SIZE;i++)
  {
  	//if it is a number then
  	char c=in[i];
	//int ascii=(int)in[i];
  	
  	//if(ascii>=48 && ascii<=57)
  	if(in[i]-'0' >= 0 && in[i]-'0' <=9)
	{
		//append to output string
		out[outSize]=c;
		outSize++;
	}
  	//   else if it is left brace then
  	else if(c=='(')
	{
		//push it onto the stack
		stack_c_push(s, c);
	}
  	//   else if it is an opperator then
  	else if(c=='/'|c=='*'|c=='+'|c=='-')//|c=='^')
	{
	  	//      if the stack is empty then
	  	//if(s->size==-1)
	  	if(s->size==-1)
		{
			//push it onto the stack
			stack_c_push(s, c);
		}
	  	
	  	//   else
	  	else
		{
			//while the top of the stack has higher precedence do
			while(s->size>-1)
			{
				//pop and append to output string
  				//end while
				out[outSize]=stack_c_pop(s);
				outSize++;
			}
			//push the token/char to the stack
			stack_c_push(s, c);
		}
	} //end if
	//else if it is right brace then
	else if(c==')')
	{
	  	//while the stack is not empty and the top item isn't a left brace do
	  	while(s->size>-1 & s->data[s->size]!='(')
		{
			//pop from stack and append to output string
			out[outSize]=stack_c_pop(s);
			outSize++;
	  	}//end while
	  	//finally pop out and disgard the left brace.
	  	stack_c_pop(s);
  	}//end if
	  else if(c==NULL)	
	  {
	  	break;
	  }
  }//end for 
  
  //if there is any input in the stack, pop and append each item to the output string.
  while(s->size>-1)
	{
		out[outSize]=stack_c_pop(s);
		outSize++;
	}
  
	//return the output string.
	//test:
	//printf("\n\nTest:%s\n\n",out);
	//system("PAUSE");
	//out = "93/11+-";
	return out; 	
}


int calculate_extra(char* in){

}

