#include <stdio.h>
#include <stdlib.h>

struct TreeStruct{
    int size;
    int numOfNode;
    int* element;
};

typedef struct TreeStruct* Tree;

Tree CreateTree (int size){
    Tree tmpTree = (Tree)malloc(sizeof(struct TreeStruct));
    
    tmpTree->size = size + 1;
    tmpTree->numOfNode = 1;
    tmpTree->element = (int*)malloc(sizeof(int) * tmpTree->size);
    
    return tmpTree;
}

void Insert (Tree tree, int value){
    if (tree->numOfNode == tree->size){
        printf("Error! Tree is full.\n");
    }
    else{
        tree->element[tree->numOfNode++] = value;
    }
}

void PrintPreorder (Tree tree, int index){
    if (index > 0 && tree->element[index] != '\0'){
        printf("%d ", tree->element[index]);
        if (2 * index < tree->size){
            PrintPreorder(tree, 2 * index);
        }
        if (2 * index + 1 <  tree -> size){
            PrintPreorder(tree, 2 * index + 1);
        }
    }
}

void PrintInorder (Tree tree, int index){
    if (index > 0 && tree->element[index] != '\0'){
        if (2 * index < tree->size){
            PrintInorder(tree, 2 * index);
        }
        printf("%d ", tree->element[index]);
        if (2 * index + 1 < tree->size){
            PrintInorder(tree, 2 * index + 1);
        }
    }
}

void PrintPostorder (Tree tree, int index){
    if (index >  0 && tree->element[index] != '\0'){
        if (2 * index < tree->size){
            PrintPostorder(tree, 2 * index);
        }
        if (2 * index + 1 < tree->size){
            PrintPostorder(tree, 2 * index + 1);
        }
        printf("%d ", tree->element[index]);
    }
}

void PrintTree (Tree tree){
    printf("Preorder: ");
    PrintPreorder(tree, 1);
    printf("\n");
    
    printf("Inorder: ");
    PrintInorder(tree, 1);
    printf("\n");
    
    printf("Postorder: ");
    PrintPostorder(tree, 1);
    printf("\n");
}


void DeleteTree (Tree tree){
    free(tree->element);
    free(tree);
}

int main(int argc, char* argv[]){
    FILE *fi;
    Tree tree;
    int treeSize;
    int tmpNum;
    
    fi = fopen(argv[1], "r");
    fscanf(fi, "%d", &treeSize);
    tree = CreateTree(treeSize);
    
    while(fscanf(fi, "%d", &tmpNum) == 1){
        Insert(tree, tmpNum);
    }
    
    PrintTree(tree);
    DeleteTree(tree);
    
    return 0;
}

