#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct tree_node tree_node;
struct tree_node {
    tree_node *left_node, *right_node;
    char data;
};

tree_node* new_node(char data){
    tree_node* node = (tree_node*)malloc(sizeof(tree_node));
    node->data = data;
    node->left_node = node->right_node = NULL;
    return node;
}

void insert_node(tree_node **root, char data){
    
    if (*root == NULL){									 // check if the tree is empty
        *root = new_node(data);
        return;
    }

    tree_node** prev = NULL;
    tree_node** curr = root;

    while(*curr){
        prev = curr;
        if(data < (*curr)->data)
            curr = &(*curr)->left_node;
        else
            curr = &(*curr)->right_node;
    }
    
    if(data < (*prev)->data)								//insert left node
        (*prev)->left_node = new_node(data);
    else										//otherwise right node
        (*prev)->right_node = new_node(data);
}


tree_node* searchTree(tree_node *root, char data){
    if (root == NULL){
        printf("Empty Tree \n");
        return NULL;
    }
    tree_node *curr = root;

    while(curr){
        if(data == curr->data){ 							//value found
            printf("Found %c \n", data);
            return curr;
        }
        else if(data < curr->data) 							// val is greater, go left
            curr = curr->left_node;	
        else                       							// else go right
            curr = curr->right_node;
    }
    printf("%c not in tree \n", data); 							//if value not found 
    return NULL;
}


void printTree (tree_node *root){
    if(root == NULL)
        return;
    printTree(root->left_node); 							//go to left subtree
    printf("%c ", root->data); 
    printTree(root->right_node); 							//go to right subtree
}


void deleteTree(tree_node *node){
    if (node != NULL){
        deleteTree(node->left_node);
        deleteTree(node->right_node);
        free(node);
    }
}

int main(){
    tree_node *root = NULL;
    char treeData[] = {'F', 'L', 'O', 'C', 'C', 'I', 'N', 'A', 'U', 'C', 'I', 'N', 'I',
         'H', 'I', 'L', 'I', 'P', 'I', 'L', 'I', 'F', 'I', 'C', 'A', 'T','T', 'I', 'O', 'N'};
    
    for (int i=0; i< strlen(treeData); i++)
        insert_node(&root, treeData[i]);

    printTree(root);
    printf("\n");

    // Generate random character
	srand((unsigned) time(NULL));

    char randomletter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand() % 26];
    searchTree(root, randomletter);
    randomletter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand() % 26];
    searchTree(root, randomletter);

    deleteTree(root);
    root = NULL;

    return 0;
}


