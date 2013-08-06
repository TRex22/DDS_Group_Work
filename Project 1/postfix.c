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
	s->size--;
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
	s->size--;
	return s->data[s->size+1];
}

// Return the top of the stack without removing it
int  stack_i_peek(IntStack* s){
	return s->data[(s->size)];
}

/*********************************************************/
int calculate(char* p){
	
}

char* convert(char* in){
	CharStack *s=stack_c_init();
	char* out=(char*)malloc(DEFAULT_SIZE*sizeof(char));
	int outSize=0;
	
	int i;
	for(i=0;i<DEFAULT_SIZE;i++)
	{
		char c=in[i];
		int ascii=(int)in[i];
		
		if(ascii>=48 && ascii<=57)
		{
			out[outSize]=c;
			outSize++;
		}
		else if(c=='(')
		{
			stack_c_push(s, c);
		}
		else if(c=='/'|c=='*'|c=='+'|c=='-'|c=='^')
		{
			if(s->size==0)
			{
				stack_c_push(s, c);
			}
			else
			{
				while(s->size>-1)
				{
					out[outSize]=stack_c_pop(s);
					outSize++;
				}
				stack_c_push(s, c);
			}
		}
		else if(c==')')
		{
			while(s->size>-1 & s->data[s->size]!='(')
			{
				out[outSize]=stack_c_pop(s);
				outSize++;
			}
			stack_c_pop(s);
		}
	}
	
	while(s->size>-1)
	{
		out[outSize]=stack_c_pop(s);
		outSize++;
	}
	
	return out;
}


int calculate_extra(char* in){

}

