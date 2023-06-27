#include <stdio.h>
#include <stdlib.h>

struct AVLNode;
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;

struct AVLNode{
    ElementType Element;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

int Height(Position Node){
    if (Node == NULL){
        return -1;
    }
    else{
        return Node->Height;
    }
}

int Max(ElementType heightLeft, ElementType heightRight){
    if (heightLeft >= heightRight){
        return heightLeft;
    }
    else{
        return heightRight;
    }
}

Position SingleRotateWithLeft(Position Node){
    Position P;
    
    P = Node->Left;
    
    Node->Left = P->Right;
    P->Right = Node;
    
    Node->Height = Max(Height(Node->Left), Height(Node->Right)) + 1;
    P->Height = Max(Height(P->Left), Node->Height) + 1;
    
    return P;
}

Position SingleRotateWithRight(Position Node){
    Position P;
    
    P = Node->Right;
    
    Node->Right = P->Left;
    P->Left = Node;
    
    Node->Height = Max(Height(Node->Left), Height(Node->Right)) + 1;
    P->Height = Max(Height(P->Left), Node->Height) + 1;
    
    return P;
}

Position DoubleRotateWithLeft(Position Node){
    Node->Left = SingleRotateWithRight(Node->Left);
    
    return SingleRotateWithLeft(Node);
}

Position DoubleRotateWithRight(Position Node){
    Node->Right = SingleRotateWithLeft(Node->Right);
    
    return SingleRotateWithRight(Node);
}

AVLTree Insert(ElementType X, AVLTree T){
    if (T == NULL){
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        
        T->Element = X;
        T->Height = 0;
        T->Left = NULL;
        T->Right = NULL;
    }
    else if (X < T->Element){
        T->Left = Insert(X, T->Left);
        
        if (Height(T->Left) - Height(T->Right) == 2){
            if (X < T->Left->Element){
                T = SingleRotateWithLeft(T);
            }
            else{
                T = DoubleRotateWithLeft(T);
            }
        }
    }
    else if (X > T->Element){
        T->Right = Insert(X, T->Right);
        
        if (Height(T->Right) - Height(T->Left) == 2){
            if (X > T->Right->Element){
                T = SingleRotateWithRight(T);
            }
            else{
                T = DoubleRotateWithRight(T);
            }
        }
    }
    else{
        printf("Insertion Error: %d already in the tree!\n", T->Element);
    }
    
    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    return T;
}

void PrintInorder(AVLTree T){
    if (T){
        PrintInorder(T->Left);
        printf("%d(%d) ", T->Element, T->Height);
        PrintInorder(T->Right);
    }
}


void DeleteTree(AVLTree T){
    if (T->Left != NULL){
        DeleteTree(T->Left);
    }
    if (T->Right != NULL){
        DeleteTree(T->Right);
    }
    free(T);
}

int main(int argc, const char * argv[]) {
    FILE *fi = fopen(argv[1], "r");
    AVLTree myTree = NULL;
    int key;
    
    while(fscanf(fi, "%d", &key) != EOF){
        myTree = Insert(key, myTree);
        PrintInorder(myTree);
        printf("\n");
    }
    
    DeleteTree(myTree);
}
