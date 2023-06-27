#include <stdio.h>
#include <stdlib.h>

const int INF = (int)2e9;

typedef struct Node{
    int vertex;
    int dist;
    int prev;
} Node;

typedef struct Graph{
    int size;
    Node* nodes;
    int** matrix;
} Graph;

Graph* createGraph(int X){
    Graph* g = (Graph*)malloc(sizeof(Graph));
        
    g->size = X + 1;
        
    g->nodes = (Node*)malloc(sizeof(Node) * g->size);
    for (int i = 0; i < g->size; i++){
        g->nodes[i].vertex = i;
        g->nodes[i].dist = INF;
        g->nodes[i].prev = 0;
    }
        
    g->matrix = (int**)malloc(sizeof(int*) * g->size); //weight
    for (int i = 0; i <= g->size; i++){ //index i부터 시작
        g->matrix[i] = (int*)malloc(sizeof(int) * g->size);
    }
    for (int i = 1; i <= g->size; i++){
        for (int j = 1; j <= g->size; j++){
            g->matrix[i][j] = 0;
        }
    }
        
    return g;
}

typedef struct Heap{
    int capacity;
    int size;
    Node* elements;
} Heap;

Heap* createMinHeap(int X){
    Heap* tmpHeap = (Heap*)malloc(sizeof(struct Heap));
        
    tmpHeap->capacity = X;
    tmpHeap->size = 0;
    
    tmpHeap->elements = (Node*)malloc(sizeof(Node) * (tmpHeap->capacity + 1));
        
    return tmpHeap;
}

void insert(Heap* H, Node N){
    int i;
    int X = N.dist;
    
    for (i = ++H->size; H->elements[i/2].dist > X && i > 1; i /= 2){
        H->elements[i] = H->elements[i/2];
    }
    
    H->elements[i] = N;
}

Node deleteMin(Heap* H){
    int i, Child;
    Node minNode, lastNode;
        
    minNode = H->elements[1];
    lastNode = H->elements[H->size--];
        
    for(i = 1; i * 2 <= H->size; i = Child){
        Child = i * 2;
        if (Child != H->size && H->elements[Child + 1].vertex < H->elements[Child].vertex){
            Child++;
        }
        
        if (lastNode.vertex > H->elements[Child].vertex){
            H->elements[i] = H->elements[Child];
        }
        else{
            break;
        }
    }
    
    H->elements[i] = lastNode;
    return minNode;
}

void decreaseKey(Heap* H, Node N){
    for (int i = 1; i <= H->size + 1; i++){
        if (H->elements[i].vertex == N.vertex){
            H->elements[i] = N;
            break;
        }
    }
}

Graph* findShortestPath(Graph* G, int s){
    G->nodes[s].dist = 0;
    G->nodes[s].prev = s;
    
    Heap* H = createMinHeap(G->size);
    
    for (int i = 1; i < H->capacity; i++){
        insert(H, G->nodes[i]);
    }
    
    while(H->size){
        Node u = deleteMin(H);
        
        for (int j = 1; j <= H->capacity; j++){
            if (G->matrix[u.vertex][j] != 0 && u.dist + G->matrix[u.vertex][j] < G->nodes[j].dist){
                G->nodes[j].dist = u.dist + G->matrix[u.vertex][j];
                G->nodes[j].prev = u.vertex;
                
                for (int i = 1; i <= H->size + 1; i++){ //decreaseKey 함수 없이 과제 구현 가능해 decreaseKey 함수를 사용하지 않았음
                    if (H->elements[i].vertex == G->nodes[j].vertex){
                        H->elements[i] = G->nodes[j];
                        break;
                    }
                }
            }
        }
    }
    
    free(H->elements);
    free(H);

    return G;
}

void printShortestPath(Graph* G){
    for (int i = 2; i < G->size; i++){
        if (G->nodes[i].dist == INF){
            printf("%d can not be reached.\n", G->nodes[i].vertex);
        }
        else{
            printf("%d", G->nodes[i].vertex);
            
            int j = i;
            while (G->nodes[j].vertex != 1){
                printf("<-%d", G->nodes[j].prev);
                j = G->nodes[j].prev;
            }
            
            printf(" cost: %d\n", G->nodes[i].dist);
        }
    }
    
    for (int i = 0; i < G->size; i++){
        free(G->matrix[i]);
    }
    free(G->matrix);
    
    free(G->nodes);
    free(G);
}

int main(int argc, char* argv[]){
    FILE* fi = fopen(argv[1], "r");
    int size;
    
    fscanf(fi, "%d", &size);
    
    Graph* G = createGraph(size);
    
    int node_s, node_d, weight;
    while(fscanf(fi, "%d %d %d", &node_s, &node_d, &weight) != EOF){
        G->matrix[node_s][node_d] = weight;
    }
    
    G = findShortestPath(G, 1);
    
    printShortestPath(G);
    
    return 0;
}
