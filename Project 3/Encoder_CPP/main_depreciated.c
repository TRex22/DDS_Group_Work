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

int main(){
	char input[255];
	fgets(line, 255, stdin);
	
	PQueue* pq=pq_init();
	
}
