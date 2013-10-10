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
}

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
	char c;
	struct _List *next;	
};
typedef struct _List List;

struct _Stack{
	int val;
	struct _Stack *forward;
	struct _Stack *backward;	
};
typedef struct _Stack Stack;

void print_Stack(Stack* s){
	while(s->forward!=NULL){
		s=s->forward;
		printf("The following is found in the stack [%d]\n", s->val);
	}
	
}

Stack* init_stack(){
	Stack *s=(Stack*)malloc(sizeof(Stack));
	
	s->val=0;
	s->forward=NULL;
	s->backward=NULL;
	
	return s;
}

void push(Stack *s,int val){
	s->val++;
	
	Stack *temp=init_stack();	
	temp->backward=s;
	temp->forward=s->forward;
	
	if(s->val==1){
		temp->forward=NULL;
	}
	
	if(s->val>1){
		temp->forward->backward=temp;
	}
	
	temp->val=val;
	s->forward=temp;	
}

int pop(Stack *s){
	if(s->val>0){
		Stack *temp=init_stack();
		temp=s->forward;
		int val=s->forward->val;
	
		if(s->val>1){
			s->forward=s->forward->forward;
			s->forward->backward=s;
		}
		
		free(temp);
		s->val--;
		return val;
	}
	else{
		return -8;
	}	
}

int* stack_Path(Stack *s){
	int *array=(int*)malloc(sizeof(int)*(s->val));
	int i=0;
	
	do{
		s=s->forward;	
	}while(s->forward!=NULL);
	
	while(s->backward!=NULL){
		array[i++]=s->val;
		s=s->backward;	
	}
	
	return array;
}

int* code_return(List* l, char c, int *size){
	l = l->next;
	
	while(l->c!=c){
		l=l->next;
	}
	
	*size=l->size;
	
	if(l->c==c){
		return l->path;
	}
	else{
		return NULL;
	}	
}

List* init_list(int path){
	List *l=(List*)malloc(sizeof(List));
	l->path=(int*)malloc(sizeof(int)*path);
	l->c='&';
	l->next=NULL;
	l->size=0;
	
	return l;
}

void enqueue(List* l, int* path, char c, int size){
	int i=0;
	l->size++;
	List *temp=init_list(size);
	for(i=0;i<=size;i++){
		temp->path[i]=path[i];
	}
	
	temp->size=size;
	temp->c=c;
	temp->next=l->next;
	l->next=temp;	
}

void print_list(List* l){
	int i=0;
	
	while(l->next!=NULL){
		l=l->next;
		
		printf("character[%c] \t code[", l->c);
		for(i=0;i<=l->size;i++){
			printf("%d",l->path[i]);
		}
		
		printf("]\n");
	}
	
}

List* recursive_Encoding(TreeNode *t, Stack *s, List *l){
	if((t->right==NULL) && (t->left==NULL)){
		int *array=stack_Path(s);
		enqueue(l, array, t->c, s->val-1);
	}
		
	if(t->left!=NULL){
		push(s, 0);
		recursive_Encoding(t->left, s, l);
		pop(s);
	}
		
	if(t->right!=NULL){
		push(s, 1);
		recursive_Encoding(t->right, s, l);
		pop(s);
	}
	
	if(s->val==0){
		return l;
	}
	
	else{
		return NULL;
	}
}

int* BinaryPath(TreeNode *t, List *l,char *input, int size_S, int* size_R){
	int i=0, j=0, k=0, size=0;
	
	int *R_Path=(int*)malloc(sizeof(int)*MAX_LENGTH);
	
	while(i<size_S){
		size = 0;
		int *code=code_return(l, input[i++], &size);
		if(code!=NULL){
			for(j=0;j<=size;j++){
				R_Path[k++] = code[j];
			}
		}
	}
	*size_R=k;
	
	return R_Path;
}

int main(void){

	char *input=(char*)malloc(sizeof(char)*MAX_LENGTH);
	int i=0;
	PQueue *min = pq_init();
	
	while(input[i-1]!='\n'){
		scanf("%c",&input[i++]);
	}
	
	input[i-1] = '&';
	
	int size_Inp=i-1;	
	int j=0, k=0;
	int freq=1;
	char *Inp=(char*)malloc(sizeof(char)*size_Inp);	
	
	for(i=0;i<size_Inp;i++){
		Inp[i]=input[i];
	}
	
	for(j=0;j<size_Inp-1;j++){
		if(input[j]=='&'){
			while(input[j]=='&'){
				j++;
			}
		}
				
		for(k=j+1;k<size_Inp;k++){
			if(input[j]==input[k]){
				freq++;
				input[k]='&';
			}					
		}
				
		Tree *node=tree_init(freq, input[j]);
		pq_enqueue(min, node, freq);
		freq=1;
	}	
	
	pq_print_chars(min);
	pq_print_freq(min);
		
	while(min->size>1){
		Tree *left=pq_dequeue(min);
		Tree *right=pq_dequeue(min);
		Tree *node=tree_merge(left, right);	
		pq_enqueue(min, node, node->root->freq);		
	}
	
	List *l = init_list(0);
	Stack *s=init_stack();
	
	l=recursive_Encoding(min->data[0]->root, s, l);	
	
	int code_size=0;
	int *path=BinaryPath(min->data[0]->root, l, Inp, size_Inp, &code_size);
	
	for(i=0;i<code_size;i++){
		printf("%d", path[i]);
	}
		
	printf("\n");
	printf("Total Bits (Original):%d\n",(size_Inp+1) * 8);	
	printf("Total Bits (Coded):%d\n",code_size);
}
