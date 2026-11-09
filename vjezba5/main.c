#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define FILEPATH "C:\\Users\\antem\\Desktop\\faks\\strukturePodataka\\vjezba5\\tekst.txt"
#define ERRORMESSAGE(a)\
    do{\
        switch(a){\
            case 0:\
                printf("Uspjeh\n");\
                break;\
            case 1:\
                printf("Greska pri alokaciji\n");\
                break;\
            case 2:\
                printf("Greska pri otvaranju datoteke\n");\
                break;\
            case 3:\
                printf("Stack je prazan\n");\
                break;\
            default:\
                printf("Greska pri vracanju vrijednosti funkcije\n");\
                break;\
        }\
    }while (0)

typedef struct _Stack{
    int value;
    struct _Stack* next;
}Stack;

int push(Stack*, int);
int pop(Stack*);

int main(){
    char c[32];
    int a, b, r, s;
    Stack head = {0, NULL};
    FILE* f = fopen(FILEPATH,"r");
    if (f == NULL){
        fclose(f);
        ERRORMESSAGE(2);
        return 2;
    }
    while (fscanf(f, "%31s", c) == 1){
        if (isdigit(c[0])){
            s = push(&head, atoi(c));
            ERRORMESSAGE(s);
        }
        else{
            a = pop(&head);
            b = pop(&head);
            switch(c[0]){
                case '+':
                    s = push(&head, a+b);
                    ERRORMESSAGE(s);
                    break;
                case '-':
                    s = push(&head, b-a);
                    ERRORMESSAGE(s);
                    break;
                case '*':
                    s = push(&head, a*b);
                    ERRORMESSAGE(s);
                    break;
                case '/':
                    if (a == 0){
                        printf("Dijeljenje sa nulom\n");
                        fclose(f);
                        return 1;
                    }
                    s = push(&head, b/a);
                    ERRORMESSAGE(s);
                    break; 
                default:
                    printf("Nepoznat operator\n");
                    return 1;
            }
        }
    }
    r = pop(&head);
    printf("%d", r);
    fclose(f);
    return 0;

}

int push(Stack* head, int Value){
    Stack* newStack = (Stack*)malloc(sizeof(Stack));
    if(newStack == NULL){
        return 1;
    }
    newStack->value = Value;
    newStack->next = head->next;
    head->next = newStack;
    return 0;
}

int pop(Stack* head){
    int Value;
    if(head->next == NULL){
        return 3;
    }
    Stack* temp = NULL;
    temp = head->next;
    Value = temp->value;
    head->next = temp->next;
    free(temp);
    return Value;
}
