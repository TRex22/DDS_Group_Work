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
	
	//for(i=0;i<DEFAULT_SIZE;i++)
	while(p[i]!='\0')
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
	//for(i=0;i<DEFAULT_SIZE;i++)
	while(in[i]!='\0')
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

/*psudocode:
		
		I have found problems with the pow function where sometimes like in the case of 10 to the power
		of 3 it comes up as 999 instead of 1000. This is the case on my machine and so I
		will program my own function so that this problem does not occur. I have decided not
		to use Math.h because of this major flaw.

		PowerFn Function:
			recieves the number and power
			checks if the power is 0
				then output is then 1
			checks if the output is 1
				then the output is the inputted number
			every other positive power is in the else statement
				make the answer equal the input
				run a for loop which loops the amount of times of the magnitude of the power
					make the number times the answer from the previous loop
				output the final number */

int PowerFn (int no, int power)
{
	int j, ans;
	if (power == 0)
	{
		ans = 1;
	}
	else if (power == 1)
	{
		ans = no;
	}
	else
	{
		ans = no;
		for (j = 1; j < power; j++)
		{
			ans = ans*no;
		}
	}
	return ans;
}

int calculate_extra(char* p){
	int i=0;
	IntStack *s=stack_i_init();
	
	//for(i=0;i<DEFAULT_SIZE;i++)
	while(p[i]!='\0')
	{
		int num1, num2;
		int count =1;
		int tempNo, tempNo2;
		
		//blank spaces later
		if(p[i]>='0' && p[i]<='9')
		{
			tempNo = p[i]-'0';
			//if it is a number then work out using powers of 10
			//int tempNo;
			//printf("\n\nTest: %c\n\n", p[i]);
			i++;
			
			while(p[i] != ' ')
			{
				if(p[i]==NULL)
				{
					break;
				}
				//printf("\n  cmNO: %d p at i: %d\n", tempNo, (int)(p[i]-'0'));
				tempNo = ((tempNo)*(PowerFn(10,count)))+(p[i]-'0');
				//printf("\n  poNO: %d\n", tempNo);
				count++;
				i++;
				
			}
			
			//printf("\nNO: %d\n", tempNo);
			s->size++;
			s->data[s->size]=tempNo;			
		}
		else if(p[i]=='+'|p[i]=='-'|p[i]=='*'|p[i]=='/')
		{
			//while(p[i] != ' ')
			//{
				//printf("\n\nTest: %c\n\n", p[i]);
				if(p[i]==NULL)
				{
					break;
				}
				
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
				
				if(p[i]==NULL)
				{
					break;
				}
				//i++;
			//}
		}
		else if(p[i]==NULL)
		{
			break;
		}
		
		if (p[i]==' ')
		{
			//ignore the blank space but then move on.
			//reset the count
			count = 1;
			//int tmpno = tempNo2;
			//tempNo2=tempNo;
			//tempNo = tmpno;
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
		//check
		//printf(" Test ans: %d\n",num);
		return num;
	}

}


