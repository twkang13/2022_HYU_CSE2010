#include <stdio.h>
#include <stdlib.h>

typedef struct _Queue{
    int size;
    int* key;
    int front;
    int rear;
} Queue;

Queue* CreateQueue(int X){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    
    q->size = X;
    
    q->key = (int*)malloc(sizeof(int) * q->size);
    for (int i = 0; i < q->size; i++){
        q->key[i] = 0;
    }
    
    q->front = 0;
    q->rear = -1;
    
    return q;
}

void Enqueue(Queue* Q, int item){
    if (Q->rear < Q->size - 1){
        Q->key[++Q->rear] = item;
    }
}

int Dequeue(Queue* Q){
    if (Q->front <= Q->rear){
        return Q->key[Q->front++];
    }
    
    return 0;
}

typedef struct _Graph{
    int size;
    int* vertex;
    int** edge;
} Graph;

Graph* CreateGraph(int X){
    Graph* g = (Graph*)malloc(sizeof(Graph));
    
    g->size = X;
    
    g->vertex = (int*)malloc(sizeof(int) * g->size);
    for (int i = 0; i < g->size; i++){
        g->vertex[i] = 0;
    }
    
    g->edge = (int**)malloc(sizeof(int*) * g->size);
    for (int i = 0; i < g->size; i++){
        g->edge[i] = (int*)malloc(sizeof(int) * g->size);
    }
    for (int i = 0; i < g->size; i++){
        for (int j = 0; j < g->size; j++){
            g->edge[i][j] = 0;
        }
    }
    
    return g;
}

int findIndex(Graph* G, int x){
    int i = 0;
    
    for (i = 0; i < G->size; i++){
        if (G->vertex[i] == x){
            return i;
        }
    }
    
    return -1;
}

void InsertEdge(Graph* G, int u, int v){
    int i = findIndex(G, u);
    int j = findIndex(G, v);
    
    if (i == -1 || j == -1){
        return;
    }
    
    G->edge[i][j] = 1;
}

void Topsort(Graph* G){
    Queue* q = CreateQueue(G->size);
    int* inDegree = (int*)malloc(sizeof(int) * G->size);
    for (int i = 0; i < G->size; i++){
        *(inDegree + i) = 0;
    }
    
    for (int j = 0; j < G->size; j++){
        for (int i = 0; i < G->size; i++){
            int indexI = findIndex(G, G->vertex[i]), indexJ = findIndex(G, G->vertex[j]);
            if (G->edge[indexI][indexJ] == 1){
                ++inDegree[indexJ];
            }
        }
    }
    
    for (int i = 0; i < G->size; i++){
        if (inDegree[i] == 0){
            Enqueue(q, G->vertex[i]);
        }
    }
    
    while(!(q->rear < q->front)){
        int element = Dequeue(q);
        printf("%d ", element);
        
        for (int i = 0; i < G->size; i++){
            for (int j = 0; j < G->size; j++){
                int indexI = findIndex(G, G->vertex[i]), indexJ = findIndex(G, G->vertex[j]);
                
                if (G->edge[indexI][indexJ] == 1){
                    if (--inDegree[indexJ] == 0){
                        Enqueue(q, G->vertex[indexJ]);
                    }
                    
                    G->edge[indexI][indexJ] = 0;
                }
            }
        }
    }
    printf("\n");
    
    free(inDegree);
    
    free(q->key);
    free(q);
    
    for (int i = 0; i < G->size; i++){
        free(G->edge[i]);
    }
    free(G->edge);
    free(G->vertex);
    free(G);
}

int main(int argc, char* argv[]){
    FILE* fi = fopen(argv[1], "r");
    int X, u, v;
    
    fscanf(fi, "%d", &X);
    
    Graph* G = CreateGraph(X);
    
    for (int i = 0; i < X; i++){
        fscanf(fi, "%d", &G->vertex[i]);
    }
    
    while(fscanf(fi, "%d %d", &u, &v) != EOF){
        InsertEdge(G, u, v);
    }
    
    Topsort(G);
    
    return 0;
}
