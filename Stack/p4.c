#include <stdio.h>
#include <stdlib.h>

typedef struct Stack{
    int* key;
    int top;
    int max_stack_size;
} Stack;

Stack* CreateStack (int max){
    Stack* S;
    
    S = malloc(sizeof(Stack));
    if (S == NULL){
        printf("Out of space!!!\n");
    }
    
    S->key = (int*)malloc(sizeof(int) * max);
    if (S->key == NULL){
        printf("Out of space!!!\n");
    }
    
    S->top = -1;
    S->max_stack_size = max;
    return S;
}

int IsEmpty (Stack* s){
    return s->top == -1;
}

int IsFull (Stack* s){
    return s->top == s->max_stack_size - 1;
}

void Push (Stack* s, int x){
    if (IsFull(s)){
        printf("Full stack\n");
        exit(0);
    }
    else{
        s->key[++s->top] = x;
    }
}

int Pop (Stack* s){
    if (IsEmpty(s)){
        printf("Empty stack\n");
        exit(0);
    }
    else{
        int num = s->key[s->top];
        s->top--;
        
        return num;
    }
}

int Top (Stack* s){
    if (IsEmpty(s)){
        return -1;
    }
    else{
        return s->key[s->top];
    }
}

void DeleteStack (Stack* s){
    free(s);
}

void Postfix (Stack* s, char input_str){
    if (input_str >= 48 && input_str <= 57){
        Push(s, atoi(&input_str));
    }
    else{
        int num1, num2;
        num2 = Pop(s);
        num1 = Pop(s);
        
        if (input_str == '+'){
            Push(s, num1 + num2);
        }
        else if (input_str == '-'){
            Push(s, num1 - num2);
        }
        else if (input_str == '*'){
            Push(s, num1 * num2);
        }
        else if (input_str == '/'){
            Push(s, num1 / num2);
        }
        else if (input_str == '%'){
            Push(s, num1 % num2);
        }
    }
}

int main(int argc, char* argv[]){
    FILE* fi = fopen(argv[1], "r");
    
    Stack* stack = CreateStack(10);
    
    char c;
    printf("Top numbers: ");
    while(1){
        fscanf(fi, "%c", &c);
        
        if (c == '#'){
            break;
        }
        
        Postfix(stack, c);
        printf("%d ", Top(stack));
    }
    printf("\n");
    printf("evaluation result: %d\n", Pop(stack));
    
    fclose(fi);
    DeleteStack(stack);

    return 0;
}

