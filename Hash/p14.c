#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_length 100

typedef struct HashTable{
    int size;
    int* list;
} HashTable;

int hash(int key, int size){
    return key % size;
}

int find(int key, HashTable* H){ // return key
    int initialIndex = hash(key, H->size);
    int index = initialIndex;
    
    do {
        if (H->list[index] == key){
            return key;
        }

        index = hash(index + 1, H->size);
        
    } while (index != initialIndex);
    
    return 0;
}

void insert(int key, HashTable* H){
    int initialIndex = hash(key, H->size);
    int index = initialIndex;
    
    do {
        if (H->list[index] == '\0'){
            H->list[index] = key;
            printf("%d is inserted at address %d\n", key, index);
            return;
        }
        else if (H->list[index] == key){
            return;
        }
        
        printf("%d collision has been occurred with %d\n", key, H->list[index]);
        index = hash(index + 1, H->size);
        
    } while (index != initialIndex);
}

int main(int argc, char* argv[]){
    FILE* f;
    f = fopen(argv[1], "r");
    int size, indexNumber;
    int i, tmp;
    char index[max_length];
    char *ptr1, *ptr2, *ptr3;
    char *ptrtmp[3];
    
    fgets(index, 100, f);
    
    ptr1 = strtok_r(index, " ", &ptrtmp[0]);
    size = atoi(ptr1);
    
    HashTable* table;
    table = malloc(sizeof(HashTable));
    table->size = size;
    table->list = malloc(sizeof(int) * table->size);
    for (i = 0; i < table->size; i++){
        table->list[i] = 0;
    }
    
    fgets(index, 100, f);
    ptr2 = strtok_r(index, " ", &ptrtmp[1]);
    while(ptr2 != NULL){
        indexNumber = atoi(ptr2);
        
        insert(indexNumber, table);
        
        ptr2 = strtok_r(NULL, " ", &ptrtmp[1]);
    }
    
    fgets(index, 100, f);
    ptr3 = strtok_r(index, " ", &ptrtmp[2]);
    while(ptr3 != NULL){
        indexNumber = atoi(ptr3);
        tmp = find(indexNumber, table);
        
        if (tmp == 0){
            printf("%d is not in the table\n", indexNumber);
        }
        else{
            printf("%d is in the table\n", indexNumber);
        }
        ptr3 = strtok_r(NULL, " ", &ptrtmp[2]);
    }
    
    return 0;
}
