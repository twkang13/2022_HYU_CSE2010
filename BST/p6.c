#include <stdio.h>
#include <stdlib.h>

typedef struct BinarySearchTree* Tree;
struct BinarySearchTree{
    int value;
    Tree left;
    Tree right;
};

Tree insertNode(Tree root, int key){
    if (root == NULL){
        root = (Tree)malloc(sizeof(struct BinarySearchTree));
        
        root->value = key;
        root->left = NULL;
        root->right = NULL;
        
        printf("Insert %d\n", key);
    }
    else if (key < root->value){
        root->left = insertNode(root->left, key);
    }
    else if (key > root->value){
        root->right = insertNode(root->right, key);
    }
    else{ //key == root->value
        printf("Insertion Error: There is already %d in the tree\n", key);
    }
    
    return root;
}

Tree getMaxValueInTree(Tree root){
    if (root == NULL){
        return NULL;
    }
    else if (root->right == NULL){
        return root;
    }
    else{
        return getMaxValueInTree(root->right);
    }
}

Tree deleteNode(Tree root, int key){
    Tree tmp;
    
    if (root == NULL){
        printf("Deletion Error: %d is not in the tree\n", key);
    }
    else if (key < root->value){
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->value){
        root->right = deleteNode(root->right, key);
    }
    else if (root->left && root->right){ //key == root->value
        tmp = getMaxValueInTree(root->left);
        printf("Delete %d\n", root->value);
        
        root->value = tmp->value;
        root->left = deleteNode(root->left, root->value);
    }
    else{
        tmp = root;
        
        if (root->left == NULL){
            root = root->right;
        }
        else if (root->right == NULL){
            root = root->left;
        }
        
        free(tmp);
    }
    
    return root;
}

void findNode(Tree root, int key){
    if (root == NULL){
        printf("%d is not in the tree\n", key);
        return;
    }
    
    if (key < root->value){
        findNode(root->left, key);
    }
    else if (key > root->value){
        findNode(root->right, key);
    }
    else{ //key == root->value
        printf("%d is in the tree\n", key);
    }
}

void printInorder(Tree root){
    if (root){
        printInorder(root->left);
        printf("%d ", root->value);
        printInorder(root->right);
    }
}

void printPreorder(Tree root){
    if (root){
        printf("%d ", root->value);
        printPreorder(root->left);
        printPreorder(root->right);
    }
}

void printPostorder(Tree root){
    if (root){
        printPostorder(root->left);
        printPostorder(root->right);
        printf("%d ", root->value);
    }
}

int main(int argc, char* argv[]){
    FILE *fi = fopen(argv[1], "r");
    char cmd;
    int key;
    
    Tree root = NULL;
    
    while(!feof(fi)){
        fscanf(fi, "%c", &cmd);
        
        switch(cmd){
            case 'i':
                fscanf(fi, "%d", &key);
                root = insertNode(root, key);
                break;
            case 'd':
                fscanf(fi, "%d", &key);
                root = deleteNode(root, key);
                break;
            case 'p':
                fscanf(fi, "%c", &cmd);
                if (cmd == 'i'){
                    printInorder(root);
                }
                else if (cmd == 'r'){
                    printPreorder(root);
                }
                else if (cmd == 'o'){
                    printPostorder(root);
                }
                printf("\n");
                break;
            case 'f':
                fscanf(fi, "%d", &key);
                findNode(root, key);
                break;
            default:
                break;
        }
    }
    
    return 0;
}
