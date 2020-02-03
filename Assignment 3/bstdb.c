#include "bstdb.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct tree_node tree_node;
struct tree_node{
	char *name;
	int count;
	int id;
	tree_node *left_node, *right_node;
};


int initialize_array(int size);
tree_node* newNode(char *name, int count);
tree_node* searchTree (int id);
void delete_tree(tree_node *node);
int tree_height(tree_node* node);
int count_nodes(tree_node* node);
int max(int a, int b);

tree_node* root = NULL; 										// Initialise root of tree
static int * unique_arr = NULL;
static int arr_index = 0;
const int arr_size = 128000;
static int num_node = 0;
static int num_search = 0;



// Write your submission in this file
//
// A main function and some profiling tools have already been set up to test
// your code in the task2.c file. All you need to do is fill out this file
// with an appropriate Binary Search Tree implementation.
//
// The input data will be books. A book is comprised of a title and a word
// count. You should store both these values in the tree along with a unique
// integer ID which you will generate.
//
// We are aiming for speed here. A BST based database should be orders of
// magnitude faster than a linked list implementation if the BST is written
// correctly.
//
// We have provided an example implementation of what a linked list based
// solution to this problem might look like in the db/listdb.c file. If you
// are struggling to understand the problem or what one of the functions
// below ought to do, consider looking at that file to see if it helps your
// understanding.
//
// There are 6 functions you need to look at. Each is provided with a comment
// which explains how it should behave. The functions are:
//
//  + bstdb_init
//  + bstdb_add
//  + bstdb_get_word_count
//  + bstdb_get_name
//  + bstdb_stat
//  + bstdb_quit
//
// Do not rename these functions or change their arguments/return types.
// Otherwise the profiler will not be able to find them. If you think you
// need more functionality than what is provided by these 6 functions, you
// may write additional functions in this file.

int initialize_array(int size) {

    if (size >= 0) {
        if (unique_arr != NULL) 									// if memory is not free
            free (unique_arr);	
        if ((unique_arr = malloc (sizeof(int) * size)) == NULL)
            return 0;												// something went wrong
        for (int i = 0; i  < size; i++)	
            unique_arr[i] = i;
		for (int i = 0; i < size - 1; i++) {						// randomize
          int j = i + rand() / (RAND_MAX / (size - i) + 1);
          int t = unique_arr[j];
          unique_arr[j] = unique_arr[i];
          unique_arr[i] = t;
        }
		return 1;
    }
	return 0; // something went wrong
}

int bstdb_init ( void ) {  									// this will check if array is inialized or not
	time_t t; 													
	srand((unsigned) time(&t));								// initialize a random value at every second
	if (initialize_array(arr_size)){
		return 1;
	}
	else
		return 0;

}

tree_node *newNode(char *name, int count) {
	
	tree_node* node = (tree_node*)malloc(sizeof(tree_node));

	if (node) {												// if malloc fails, this makes sure node points to something
		node->count = count;
		node->left_node = node->right_node = NULL;
		
		node->id = unique_arr[arr_index];
		arr_index++;

		int length = strlen(name) + 1;
		node->name = calloc(length, sizeof(char));

		if (node->name) {
			
			strcpy(node->name, name);						//copy file name into ndoe
			return node;
		}
		else {
			free(node);
			node = NULL;									// for reporting error if calloc failed
			return NULL;
		}
	}
	return NULL; // something went wrong
}


int bstdb_add ( char *name, int count ) {
	// This function should create a new node in the binary search tree, 
	// populate it with the name and count of the arguments and store
	// the result in the tree.
	//
	// This function should also generate and return an identifier that is
	// unique to this document. A user can find the stored data by passing
	// this ID to one of the two search functions below.
	//
	// If something goes wrong and the data cannot be stored, this function
	// should return -1. Otherwise it should return the ID of the new node

	tree_node* new = newNode(name, count);

	if(new == NULL) // somwthing went wrong
		return -1;

	if (root == NULL){ // The tree is empty
		root = new;
		return root->id;
	}

	tree_node* prev = NULL;
    tree_node* current = root;
	
	
    while(current){												// find the parent of new node
        prev = current;
        if(new->id < current->id)
            current = current->left_node;
        else
            current = current->right_node;
    }
   
    if(new->id < prev->id){										//insert left child
        prev->left_node = new;
		//printf("%d\n", new->id);
		return new->id;
	}
	
    else if (new->id > prev->id) {								// insert right child
        prev->right_node = new;		
		return new->id;
	}
	else // something went wrong
		return -1;
}

int bstdb_get_word_count ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1

	tree_node* node = searchTree(doc_id);

	if(node != NULL)
		return node->count;

	return -1;
}

char* bstdb_get_name ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return NULL or 0

	tree_node* node = searchTree(doc_id);

	if(node != NULL)
		return node->name;

	return 0;
}


tree_node* searchTree (int id){

	num_search++; 											// Count the number of times the function was called

	if (root == NULL){ 										// Tree is empty
        return NULL;
    }

    tree_node *current = root;

    while(current){
        if(id == current->id){ 										// current value is matches our value
            return current;
        }
        else if (id < current->id){						    		// go to left node
            current = current->left_node;
        }
        else                      									//  go to right node
            current = current->right_node;			
		num_node++;
	}
	
    return NULL;											// if value is not found
}


void bstdb_stat ( void ) {
	// Use this function to show off! It will be called once after the 
	// profiler ends. The profiler checks for execution time and simple errors,
	// but you should use this function to demonstrate your own innovation.
	//
	// Suggestions for things you might want to demonstrate are given below,
	// but in general what you choose to show here is up to you. This function
	// counts for marks so make sure it does something interesting or useful.
	//
	//  + Check if your tree is balanced and print the result
	//
	//  + Does the number of nodes in the tree match the number you expect
	//    based on the number of insertions you performed?
	//
	//  + How many nodes on average did you need to traverse in order to find
	//    a search result? 
	//
	//  + Can you prove that there are no accidental duplicate document IDs
	//    in the tree?
	
	int nodesPerSearch = num_node/num_search;
	printf("Average number of nodes per search: %d\n", nodesPerSearch );
	printf("Height of left sub-tree: %d\n", tree_height(root->left_node));			 	// Get height of left and right sub-trees
	printf("Height of right sub-tree: %d\n", tree_height(root->right_node));
	printf("Num nodes in left sub tree: %d\n", count_nodes(root->left_node));			// Get num of nodes in left and right sub-tree
	printf("Num nodes in right sub tree: %d\n", count_nodes(root->right_node));
	
	if(tree_height(root->left_node)==tree_height(root->right_node) || tree_height(root->left_node) == tree_height(root->right_node))
	printf("The tree is balanced \n");
	else printf("Tree is not balanced\n");
}


void bstdb_quit ( void ) {
	// This function will run once (and only once) when the program ends. Use
	// it to free any memory you allocated in the course of operating the
	// database.
	delete_tree(root);
	free(unique_arr);
}


void delete_tree(tree_node *node){
    if (node != NULL){
        delete_tree(node->left_node);
        delete_tree(node->right_node);
        free(node);
    }
}


int tree_height(tree_node* node){

	if(node == NULL){ 										// tree is empty
		return 0;
	}
   	return 1 + max(tree_height(node->left_node), tree_height(node->right_node)); 
}


int max(int a, int b) { 
  return (a >= b)? a: b; 
} 


int count_nodes(tree_node* node){
	if(node == NULL){ 										// tree is empty
		return 0;
	}
	int i;
	i = 1 + count_nodes(node->left_node) + count_nodes(node->right_node);
	return i;
}
