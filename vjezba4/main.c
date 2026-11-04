#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILEPATH "C:\\Users\\antem\\Desktop\\faks\\strukturePodataka\\vjezba4\\tekst.txt"
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
            default:\
                printf("Greska pri vracanju vrijednosti funkcije\n");\
                break;\
        }\
    }while (0)

typedef struct _Poly{
    int coef;
    int exp;
    struct _Poly* next;
}Poly;

int readPoly(Poly**,Poly**,char*);
int sortedInput(Poly**, int, int);
int addPoly(Poly*,Poly*);
int multiPoly(Poly*, Poly*);
int freePoly(Poly*);
int printPoly(Poly*);

int main(){ 
    Poly Head1 = {0, 0, NULL};
    Poly Head2 = {0, 0, NULL};
    int n, mP, aP, rP;
    rP = readPoly(&Head1.next, &Head2.next, FILEPATH);
    ERRORMESSAGE(rP);
    printf("1 za mnozenje, 2 za zbrajanje: ");
    scanf("%d", &n);
    switch(n){
        case 1:
            mP = multiPoly(&Head1, &Head2);
            ERRORMESSAGE(mP);
            break;
        case 2:
            aP = addPoly(&Head1, &Head2);
            ERRORMESSAGE(aP);
            break;
        default:
            printf("Nepodrzan unos");
            break;

    }
    freePoly(Head1.next);
    freePoly(Head2.next);
    return 0;
}

int readPoly(Poly** head1, Poly** head2, char* fileName){
    char poly[1000];
    int m = 1;
    FILE* f = fopen(fileName, "r");
    if (f==NULL){
        return 2;
    }
    while(fgets(poly, sizeof(poly), f) != NULL){
        int n = (int)strlen(poly);
        for(int i = 1; i<n; i+=2){
            if(m == 1){
                sortedInput(head1, (poly[i-1] - '0'), (poly[i] - '0'));
                printf("%c",poly[i-1]);
                printf("%c ",poly[i]);
            }
            else if (m == 2){
                sortedInput(head2, (poly[i-1] - '0'), (poly[i] - '0'));
                printf("%c",poly[i-1]);
                printf("%c ",poly[i]);
            }   
        } 
        m++;
    }
    fclose(f);
    return 0;
}

int sortedInput(Poly** head, int c, int e){
    Poly** p = head;
    if (c == 0){
        return 0;
    }
    while (*p != NULL && (*p)->exp > e){
        p = &(*p)->next;
    }
    if (*p != NULL && (*p)->exp == e){
        (*p)->coef += c;
        if ((*p)->coef == 0){              
            Poly* tmp = *p;
            *p = tmp->next;
            free(tmp);
        }
        return 0;
    }
    Poly* newPoly = (Poly*)malloc(sizeof(Poly));
    if (newPoly == NULL)
        return 1;
    newPoly->coef = c;
    newPoly->exp  = e;
    newPoly->next = *p;
    *p = newPoly;
    return 0;
}

int addPoly(Poly* head1, Poly* head2){
    Poly result = {0, 0, NULL};
    Poly* p;
    for(p = head1->next; p != NULL; p = p->next){      
        if (sortedInput(&result.next, p->coef, p->exp) != 0){
            freePoly(result.next);
            return 1;
        }
    }
    for(p = head2->next; p != NULL; p = p->next){      
        if (sortedInput(&result.next, p->coef, p->exp) != 0){
            freePoly(result.next);
            return 1;
        }
    }
    printPoly(&result);
    freePoly(result.next);
    return 0;
}

int multiPoly(Poly* head1, Poly* head2){
    Poly result = {0, 0, NULL};
    Poly* p1 = head1->next;
    Poly* p2 = head2->next;
    while(p1 != NULL){
        p2 = head2->next;
        while(p2 != NULL){
            if (sortedInput(&result.next,(p1->coef * p2->coef), (p1->exp + p2->exp)) != 0){
                freePoly(result.next);
                return 1;
            }
            p2 = p2->next;
        }
        p1 = p1->next;   
    }
    printPoly(&result);
    freePoly(result.next);
    return 0;
}

int printPoly(Poly* head){
    Poly* p = head->next;
    while(p != NULL){
        if (p->exp == 0){
            printf("%d ", p->coef);
        }
        else{
            printf("%dx^%d ", p->coef, p->exp);
        }
        p = p->next;
    }
    return 0;
}

int freePoly(Poly* head){
    Poly* p = NULL;
    while(head != NULL){
        p = head->next;
        free(head);
        head = p;
    }
    return 0;
}