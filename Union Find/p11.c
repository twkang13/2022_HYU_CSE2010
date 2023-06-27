#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _DisjointSet{
    int size;
    int *ptr_arr;
} DisjointSets;

typedef struct _PrintDisjointSet{
    int size;
    int *ptr_arr;
} PrintDisjointSets;

void init (DisjointSets* sets, PrintDisjointSets* maze, int n){
    sets->size = n*n;
    sets->ptr_arr = (int*)malloc(sizeof(int) * (sets->size + 1));
    for (int i = 1; i <= sets->size; i++){
        sets->ptr_arr[i] = 0;
    }
    
    maze->size = 2*n*(n+1);
    maze->ptr_arr = (int*)malloc(sizeof(int) * (maze->size));
    for (int i = 0; i < maze->size; i++){
        maze->ptr_arr[i] = 1;
    }
    maze->ptr_arr[n] = 0;
    maze->ptr_arr[maze->size - n - 1] = 0;
}

int find (DisjointSets* sets, int x){
    if (sets->ptr_arr[x] <= 0){
        return x;
    }
    else{
        return sets->ptr_arr[x] = find(sets, sets->ptr_arr[x]);
    }
}

void union_ (DisjointSets* sets, int i, int j){
    int p1 = find(sets, i);
    int p2 = find(sets, j);
    
    if (sets->ptr_arr[p2] < sets->ptr_arr[p1]){
        sets->ptr_arr[p1] = p2;
    }
    else{
        if (sets->ptr_arr[p2] == sets->ptr_arr[p1]){
            sets->ptr_arr[p1]--;
        }
        sets->ptr_arr[p2] = p1;
    }
}

void createMaze (DisjointSets* sets, PrintDisjointSets* maze, int n){
    srand((unsigned int)time(NULL));
    
    while(find(sets, 1) != find(sets, sets->size)){
        int ran = 0, divideNum = 2*n+1;
        while ((0 <= ran && ran <= n-1) || (ran % divideNum == n || ran % divideNum == 2*n)){
            ran = rand() % (maze->size - n);
        }
        int adjCell1, adjCell2;
        
        if (ran % divideNum < n){
            adjCell1 = (ran / divideNum - 1) * n + ran % divideNum + 1;
            adjCell2 = adjCell1 + n;
        }
        else{
            adjCell1 = ran / divideNum * n + ran % divideNum - n;
            adjCell2 = adjCell1 + 1;
        }
        
        int u = find(sets, adjCell1);
        int v = find(sets, adjCell2);
        
        if (u != v){
            union_(sets, u, v);
            maze->ptr_arr[ran] = 0;
        }
    }
}

void printMaze (PrintDisjointSets* maze, int n){
    int divideNum = 2*n+1;
    
    for (int i = 0; i < maze->size; i++){
        if (maze->ptr_arr[i] == 1){
            if (i % divideNum < n-1){
                printf(" - ");
            }
            else if (i % divideNum == n-1){
                printf(" -\n");
            }
            else if (i % divideNum < divideNum - 1){
                printf("|  ");
            }
            else if (i % divideNum == divideNum - 1){
                printf("|\n");
            }
        }
        else{
            if (i % divideNum == n-1 || i % divideNum == divideNum - 1){
                printf("\n");
            }
            else{
                printf("   ");
            }
        }
    }
}

void freeMaze (DisjointSets* sets, PrintDisjointSets* maze){
    free(sets->ptr_arr);
    free(sets);
    
    free(maze->ptr_arr);
    free(maze);
}

int main(int argc, const char * argv[]) {
    int num;
    FILE *fi = fopen(argv[1], "r");
    fscanf(fi, "%d", &num);
    fclose(fi);
    
    DisjointSets* sets;
    PrintDisjointSets* maze;
    
    sets = (DisjointSets*)malloc(sizeof(DisjointSets));
    maze = (PrintDisjointSets*)malloc(sizeof(PrintDisjointSets));
    
    init(sets, maze, num);
    
    createMaze(sets, maze, num);
    
    printMaze(maze, num);
    
    freeMaze(sets, maze);
    
    return 0;
}
