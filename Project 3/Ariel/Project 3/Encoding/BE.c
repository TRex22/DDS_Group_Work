#define MAX_LENGTH 255
#define MAX_UNIQUE_CHARS 128

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/************************ Tree Headers ***************************************/
// Tree Nodes
struct _TreeNode{
    int freq;
    char c;

    struct _TreeNode *left;
    struct _TreeNode *right;
};
typedef struct _TreeNode TreeNode;

// Tree Wrapper
struct _Tree{
    TreeNode *root;
};
typedef struct _Tree Tree;

// TreeNode create a new node in the tree with relevant frequency and char
TreeNode* tn_init(int freq, char c);

// Print a tree node in a pre-order traversal
//   Root[left traversal][right traversal]
void tn_print(TreeNode *t);

// Create a new Tree with a single root node
Tree* tree_init(int freq, char c);

// Take 2 trees and merge them as the left and right children of a new node
Tree* tree_merge(Tree *left, Tree *right);

// Print a tree using a pre-order traversal
void tree_print(Tree *t);

/************************ Tree Functions ***************************************/
// TreeNode create a new node in the tree with relevant frequency and char
TreeNode* tn_init(int freq, char c){
    TreeNode *tn = (TreeNode*) malloc(sizeof(TreeNode));
    tn->freq = freq;
    tn->c    = c;

    tn->left = NULL;
    tn->right = NULL;
    return tn;
};

// Print a tree node in a pre-order traversal
//   Root[left traversal][right traversal]
void tn_print(TreeNode *t){
    if(t->left == NULL || t->right == NULL){
        printf("'%c'(%d)", t->c, t->freq);
    }else{
        printf("%d[", t->freq);
        tn_print(t->left);
        printf("][");
        tn_print(t->right);
        printf("]");
    }
}
// Create a new Tree with a single root node
Tree* tree_init(int freq, char c){
    Tree *t = (Tree*) malloc(sizeof(Tree));
    t->root = tn_init(freq, c);
    return t;
}

// Take 2 trees and merge them as the left and right children of a new node
Tree* tree_merge(Tree *left, Tree *right){
    Tree *t = tree_init(left->root->freq + right->root->freq, '\0');
    
    t->root->left  = left->root;
    t->root->right = right->root;

    // Just free the old tree dummy heads, not the actual trees
    free(left);
    free(right);

    return t;
}

// Print a tree using a pre-order traversal
void tree_print(Tree *t){
    if(t->root == NULL) return;

    tn_print(t->root);
}

/****************** Priority Queue Headers ****************************************************/
/**
 * Richard Klein (2013)
 *
 * Priority Queue Implementation based on Arrays.
 *
 * Note that this is not an optimal strategy. Binary Heaps are better in most circumstances.
 *
 * The priority queue works by keeping a sorted array.
 * Each insertion is done by searching for the correct index and then shifting all 
 *      elements to the right by one. Best and Worst case for a single insertion are both Θ(n).
 *      We need i comparisons to discover that we insert at index i.
 *      We then need to move n-i numbers to the right to make space. 
 *      
 * Deletion is done at the back and requires that we only adjust the size variable. This takes Θ(1).
 */

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

    while(i < p->size && priority == p->priority[i] && t->root->c > p->data[i]->root->c)
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
        printf("%c ", p->data[i]->root->c);
    }
    printf("%c\n", p->data[i]->root->c);
}
// Print all the frequencies in the roots stored in the priority queue.
void pq_print_freq(PQueue *p){
    int i;
    for(i = p->size -1; i > 0; i--){
        printf("%d ", p->data[i]->root->freq);
    }
    printf("%d\n", p->data[i]->root->freq);
}

/********************** YOUR CODE HERE ***************************************/

struct _List{
	int *path;
	int size;
	char character;
	struct _List *next;	
};

typedef struct _List List;

struct _Stack{
	int val;
	struct _Stack *forward;
	struct _Stack *backward;	
};

typedef struct _Stack Stack;

Stack* init_stack();
void push(Stack*,int);
int pop(Stack *);
int* stack_Path(Stack*);
void print_Stack(Stack*);


void print_Stack(Stack* head){
	while(head->forward != NULL){
	head = head->forward;
	printf("The following is found in the stack [%d]\n", head->val);	
	}
	
}

Stack* init_stack(){
	Stack *head = (Stack*) malloc(sizeof(Stack));
	head->val = 0;
	head->forward = NULL;
	head->backward = NULL;
	
	return head;
}

void push(Stack *head,int val){
	head->val++;
	
	Stack *Extra = init_stack();	
	Extra->backward = head;
	Extra->forward = head->forward;
	
	if(head->val == 1)
		Extra->forward = NULL;
	
	
	if(head->val > 1)
	Extra->forward->backward = Extra;
	
	Extra->val = val;
	head->forward = Extra;	
}

int pop(Stack *head){
	
	if(head->val > 0){
		Stack *temp = init_stack();
		temp = head->forward;
		int val = 8;	
			val = head->forward->val;
			
		//printf("This is head->forward val %d\n", head->forward->val);
		if(head->val > 1)
			head->forward = head->forward->forward;	
		
		
		if(head->val > 1)
			head->forward->backward = head;
			
		free(temp);
		head->val--;
		return val;
	}
	else
	return -8;	
	
	
}

int* stack_Path(Stack *head){
	int *array = (int*) malloc(sizeof(int) * (head->val));
	int i = 0;
	
	do{
		head = head->forward;	
	}while(head->forward != NULL);
	
	while(head->backward != NULL){
		array[i++] = head->val;
		head = head->backward;	
		
	}

	return array;
	
}


List* init_list(int);
void List_enque(List*, int*,char,int);
void List_Print(List*);
int* code_return(List*, char, int*);
int* BinaryPath(TreeNode*, List*,char*, int, int*);


int* code_return(List* head, char search_C, int *size){
	head = head->next;
	while(head->character != search_C){
		head = head->next;
		
		
	}
	
	*size = head->size;
	
	
	if(head->character == search_C)
		return head->path;
	else
		return NULL;
	
}

List* init_list(int path_S){
	List *list =(List*) malloc(sizeof(List));
	list->path =(int*) malloc(sizeof(int)*path_S);
	list->character = '&';
	list->next = NULL;
	list->size = 0;
	
	return list;
}



void List_enque(List* list, int* path,char character,int _size){
	int i =0;
	list->size++;
	List *extra = init_list(_size);
	for(i=0;i <= _size;i++)
	extra->path[i] = path[i];
	
	//for(i=0;i <= _size;i++)
	//printf("[%d]->", extra->path[i]);
	
	//printf("\n");
	
	extra->size = _size;
	extra->character = character;
	extra->next = list->next;
	list->next = extra;	
}

void List_Print(List* list){
		int i = 0;
		
		while(list->next != NULL){
			list = list->next;
			i=0;
			
			
			printf("character[%c] \t code[", list->character);
			for(i=0;i<=list->size;i++)
			printf("%d",list->path[i]);	
			
			printf("]\n");
			
		}
	
}

List* recursive_Encoding(TreeNode *t, Stack *front, List *head){
	
	//printf("1\n");
		
	if((t->right == NULL) && (t->left == NULL)){
		//printf("4\n");
		int *array = stack_Path(front);
		List_enque(head, array,t->c,front->val-1);
		
		
	}	
	if(t->left != NULL){
		//printf("2\n");
		push(front, 0);
		recursive_Encoding(t->left,front,head);
		pop(front);
	}	
	if(t->right != NULL){
		//printf("3\n");
		push(front, 1);
		recursive_Encoding(t->right,front,head);
		pop(front);
	}		
		
	//printf("This is stack->size %d\n", front->val);
	if(front->val == 0){
		//printf("It has reached here\n");
		return head;
	}
	else
		return NULL;
}

int* BinaryPath(TreeNode *t, List *head,char *sentence, int size_S, int* size_R){
	int i=0;
	int j=0;
	int k = 0;
	int size = 0;
	
	int *R_Path = (int*) malloc(sizeof(int) *MAX_LENGTH);
	
	while(i<size_S){
		size = 0;
		//printf("This is the character %c\n", sentence[i]);
		int *code = code_return(head,sentence[i++],&size);
		if(code != NULL){
			for(j=0;j<=size;j++){
				R_Path[k++] = code[j];
				
			}
		}
		
		
	}
	*size_R = k;
	
	return R_Path;
}

int main(){

	char *Input = (char*) malloc(sizeof(char)* MAX_LENGTH);
	int i = 0;
	//char *Inp = (char*) malloc(sizeof(char)* MAX_LENGTH);
	PQueue *Min_Que = pq_init();
	
	//for(i=0;i<MAX_LENGTH;i++){
		//Input[i] = '&';
		//Inp[i] = '&';
	//}
		
		
	i=0;
	
	while(Input[i-1] != 10)
		scanf("%c",&Input[i++]);
		
		
	//printf("%s\n", Input);
	Input[i-1] = '&';
	//Inp[i-1] = '&';
	
	
	//printf("It is here printing INP\n");	
	
	int size_Inp = i-1;	
	int j =0, k =0;
	int Frequency = 1;
	char *Inp = (char*) malloc(sizeof(char) * size_Inp);
	
		
	//printf("It is here printing INPUT\n");	
		
		for(i=0;i<size_Inp;i++)
			Inp[i] = Input[i];
	
	//printf("%s\n", Inp);
	
	//printf("end printing INPUT\n");
		
		for(j=0;j<size_Inp-1;j++){
			if(Input[j] == '&'){
				while(Input[j] == '&')
					j++;
			}			
			for(k=j+1;k<size_Inp;k++){
				if(Input[j] == Input[k]){
					
					Frequency++;
					Input[k] = '&';
					
				}					
			}
			//printf("The following is Input[j] [%c]\n", Input[j]);			
			Tree *Node = tree_init(Frequency, Input[j]);
			pq_enqueue(Min_Que, Node, Frequency);
			Frequency = 1;
		}	
		pq_print_chars(Min_Que);
		pq_print_freq(Min_Que);
		
	//printf("Min_Que size [%d]\n",Min_Que->size);	
	while(Min_Que->size > 1){
		Tree *left = pq_dequeue(Min_Que);
		Tree *right = pq_dequeue(Min_Que);
		Tree *node = tree_merge(left, right);
		//printf("This is the frequency of node added [%d]\n", node->root->freq);	
		pq_enqueue(Min_Que, node, node->root->freq);		
	}
	
	//pq_print_freq(Min_Que);
	
	List *head = init_list(9);
	Stack *front = init_stack();
	
	//printf("This is the Min_Que size %d\n", Min_Que->size);
	head = recursive_Encoding(Min_Que->data[0]->root, front, head);
	//printf("It has reached here\n");
	//printf("This is list character [%c]", head->character);
	//if(head->next != NULL)
	//List_Print(head);
	
	
	
	int code_size = 0;
	int *path = BinaryPath(Min_Que->data[0]->root, head,Inp, size_Inp, &code_size);
	
	for(i=0;i<code_size;i++)
		printf("%d",path[i]);
	printf("\n");
	printf("Total Bits (original) :%d\n",(size_Inp+1) * 8);	
	printf("Total Bits (coded) :%d\n",code_size);

	return 0;

}


