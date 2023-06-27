#include <stdio.h>
#include <stdlib.h>

typedef struct HeapStruct* Heap;
struct HeapStruct{
    int capacity;
    int size;
    int* element;
};

Heap CreateHeap (int heapSize){
    Heap tmpHeap = (Heap)malloc(sizeof(struct HeapStruct));
    
    tmpHeap->capacity = heapSize + 1;
    tmpHeap->size = 0;
    tmpHeap->element = (int*)malloc(sizeof(int) * tmpHeap->capacity);
    
    return tmpHeap;
}

int Find (Heap heap, int value){
    for (int i = 1; i <= heap->size; i++){
        if (value == heap->element[i]){
            return 1;
        }
    }
    
    return 0;
}

void Insert (Heap heap, int value){
    int i;
    
    if (heap->capacity - 1 <= heap->size){
        printf("Insertion Error: Max Heap is full.\n");
        return;
    }
    
    if (heap->size == 0){
        heap->element[++heap->size] = value;
        printf("Insert %d\n", value);
        return;
    }
    
    if (Find(heap, value)){
        printf("%d is already in the heap.\n", value);
        return;
    }

    for (i = ++heap->size; heap->element[i/2] < value && i > 1; i /= 2){
        heap->element[i] = heap->element[i/2];
    }
    
    heap->element[i] = value;
    printf("Insert %d\n", heap->element[i]);
}

void PrintHeap (Heap heap){
    if (heap->size == 0){
        printf("Max heap is empty!\n");
        return;
    }
    
    for (int i = 1; i <= heap->size; i++){
        printf("%d ", heap->element[i]);
    }
    printf("\n");
}


void DeleteMax (Heap heap){
    if (heap->size == 0){
        printf("Deletion Error: Max heap is empty!\n");
        return;
    }
    
    int parent = 0, child, maxElement, lastElement;
    
    maxElement = heap->element[1];
    lastElement = heap->element[heap->size--];
    
    heap->element[1] = lastElement;
    
    for (int parent = 1; parent * 2 <= heap->size; parent = child){
        child = parent * 2;
        
        if (child != heap->size && heap->element[child] < heap->element[child + 1]){
            ++child;
        }

        if (lastElement < heap->element[child]){
            int tmp = heap->element[parent];
            heap->element[parent] = heap->element[child];
            heap->element[child] = tmp;
        }
        else{
            break;
        }
    }
    
    heap->element[parent] = lastElement;
    printf("Max element(%d) deleted.\n", maxElement);
}

void FreeHeap (Heap heap){
    free(heap->element);
    free(heap);
}

int main(int argc, char* argv[]){
    FILE *fi = fopen(argv[1], "r");
    char cv;
    Heap maxHeap = NULL;
    int value;
    
    while(!feof(fi)){
        fscanf(fi, "%c", &cv);
        switch(cv){
            case 'n':
                fscanf(fi, "%d", &value);
                maxHeap = CreateHeap(value);
                break;
                
            case 'i':
                fscanf(fi, "%d", &value);
                Insert(maxHeap, value);
                break;
                
            case 'd':
                DeleteMax(maxHeap);
                break;
                
            case 'f':
                fscanf(fi, "%d", &value);
                if (Find(maxHeap, value)){
                    printf("%d is in the heap.\n", value);
                }
                else{
                    printf("%d is not in the heap.\n", value);
                }
                break;
                
            case 'p':
                PrintHeap(maxHeap);
        }
    }
    
    FreeHeap(maxHeap);
}
