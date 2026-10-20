
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
                printf("Lista je prazna\n");\
                break;\
            case 3:\
                printf("Greska pri pronalazenju prezimena\n");\
                break;\
        }\
    }while (0)

typedef struct _Person {
	 char name[20];
     char surname[20];
     int year;
	 struct _Person* next; //unutar strukture koristi _ime*
}Person;

int insertBegin(char* Name, char* Surname, int Year, Person* Head);
int insertEnd(char* Name, char* Surname, int Year, Person* Head);
int printList(Person* Head);
Person* findLastName(Person* Head, char* Surname);
int deletePerson(Person* Head, char* Surname);

int main(){
    Person head = { "", "", 0, NULL };
    char name[20], surname[20];
    int year, choice, s;

    do {
        
        printf("1 Dodaj na pocetak\n");
        printf("2 Dodaj na kraj\n");
        printf("3 Ispisi listu\n");
        printf("4 Pronadji po prezimenu\n");
        printf("5 Obrisi po prezimenu\n");
        printf("0 Izlaz\n");

        if (scanf("%d", &choice) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            choice = -1;
        }

        switch (choice) {
            case 1:
                printf("Ime: ");      
                scanf("%19s", name);
                printf("Prezime: ");  
                scanf("%19s", surname);
                printf("Godina: ");   
                scanf("%d", &year);
                s = insertBegin(name, surname, year, &head);
                ERRORMESSAGE(s);
                break;

            case 2:
                printf("Ime: ");      
                scanf("%19s", name);
                printf("Prezime: ");  
                scanf("%19s", surname);
                printf("Godina: ");   
                scanf("%d", &year);
                s = insertEnd(name, surname, year, &head);
                ERRORMESSAGE(s);
                break;

            case 3:
                s = printList(&head);
                if (s != 0){
                    ERRORMESSAGE(s);
                }
                break;

            case 4:
                printf("Prezime: ");  
                scanf("%19s", surname);
                Person* found = findLastName(&head, surname);
                if (found != NULL) {
                    ERRORMESSAGE(0);
                } else {
                    ERRORMESSAGE(3);
                }
                break;

            case 5:
                printf("Prezime: ");  
                scanf("%19s", surname);
                s = deletePerson(&head, surname);
                ERRORMESSAGE(s);
                break;

            case 0:
                break;

            default:
                printf("Nepoznata opcija.\n");
                break;
        }
    } while (choice != 0);
    return 0;
}

int insertBegin(char* Name, char* Surname,int Year,Person* Head ){
    Person* newPerson = (Person*)malloc(sizeof(Person));
    if (newPerson == NULL){
        return 1;
    }

    newPerson->year = Year;
    strcpy(newPerson->name, Name);
    strcpy(newPerson->surname, Surname);
    newPerson->next = Head->next;
    Head->next = newPerson;
    
    return 0;
}

int printList(Person* Head){
    if (Head == NULL){
        return 2; 
    }
    Person* p = Head->next;
    while (p!= NULL){
            printf("%s %s %d\n", p->name, p->surname, p->year);
            p = p->next;
        }
    return 0;
}

int insertEnd(char* Name, char* Surname, int Year, Person* Head){
    Person* newPerson = (Person*)malloc(sizeof(Person));
    if (newPerson == NULL){
        return 1;
    }
    newPerson->next = NULL;
    newPerson->year = Year;
    strcpy(newPerson->name, Name);
    strcpy(newPerson->surname, Surname);

    while(Head->next != NULL){
        Head = Head->next;
    }
    Head->next = newPerson;
    return 0;
} 

Person* findLastName(Person* Head, char* Surname){
    for (Head = Head->next;Head !=NULL;Head=Head->next){
        if (strcmp(Head->surname, Surname) == 0){
             return Head;
        }
    }
    return NULL;
}

int deletePerson(Person* Head, char* Surname){
	Person* prev = Head;
	Person* curr = findLastName(Head, Surname);
    if (curr == NULL) {
        return 3;
    }
	while (prev->next != curr) {
		prev = prev->next;
	}
	prev->next = curr->next;
    free(curr);
    return 0;
}