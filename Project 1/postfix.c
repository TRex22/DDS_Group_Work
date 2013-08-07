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
		return s->data[s->size+1];
	}
	else
	{
		return NULL;
	}
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
		return s->data[s->size+1];
	}
	else
	{
		return NULL;
	}
}

// Return the top of the stack without removing it
int  stack_i_peek(IntStack* s){
	return s->data[(s->size)];
}

/*********************************************************/
int calculate(char* p){
	
	int i=0;
	IntStack *s=stack_i_init();
	
	while(p[i]!=NULL)
	{
		int num1, num2;
		if(p[i]>='0' && p[i]<='9')
		{
			stack_i_push(s, p[i]-'0');
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
		
		i++;
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
	CharStack *s=stack_c_init();
	char* out=(char*)malloc(DEFAULT_SIZE*sizeof(char));
	int outSize=0;
	
	int i=0;
	while(in[i]!=NULL)
	{
		char c=in[i];
		
		if(c>='0' && c<='9')
		{
			out[outSize]=c;
			outSize++;
		}
		else if(c=='(')
		{
			stack_c_push(s, c);
		}
		else if(c=='/'|c=='*'|c=='+'|c=='-')
		{
			if(s->size<0)
			{
				stack_c_push(s, c);
			}
			else
			{
				while(s->size>-1 && stack_c_peek(s)!='(')
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
		
		i++;
	}
	
	while(s->size>-1)
	{
		out[outSize]=stack_c_pop(s);
		outSize++;
	}
	
	return out;
}


int calculate_extra(char* p){
	int i;
	IntStack *s=stack_i_init();
	
	while(p[i]!=NULL)
	{
		int num1, num2;
		if(p[i]>='0' && p[i]<='9')
		{
			stack_i_push(s, p[i]-'0');
			
			while(p[i+1]>='0' && p[i+1]>='9')
			{
				int temp=stack_i_pop(s);
				i++;
				temp=(temp*10)+(p[i]-'0');
				stack_i_push(s, temp);
			}
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
			
		i++;
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
