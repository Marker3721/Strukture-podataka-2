
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
            case 4:\
                printf("Greska pri otvaranju datoteke\n");\
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
int insertAfter(Person* Head, char* Surname);
int insertBefore(Person* Head, char* Surname);
int writeToFile(Person* Head, char* fileName);
int readFromFile(Person* Head, char* fileName);
int sortBySurname(Person* Head);

int main(){
    Person head = { "", "", 0, NULL };
    char name[20], surname[20], fileName[20];
    int year, choice, s;

    do {
        
        printf("1 Dodaj na pocetak\n");
        printf("2 Dodaj na kraj\n");
        printf("3 Ispisi listu\n");
        printf("4 Pronadji po prezimenu\n");
        printf("5 Obrisi po prezimenu\n");
        printf("6 Dodaj iza\n");
        printf("7 Dodaj ispred\n");
        printf("8 Upisi u datoteku\n");
        printf("9 Procitaj iz datoteke\n");
        printf("10 Sortiraj po prezimenu\n");
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
                printf("Prezime: \n");  
                scanf("%19s", surname);
                printf("Godina: \n");   
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

            case 6:
                printf("Prezime iza kojeg dodajemo: ");
                scanf("%19s", surname);
                s = insertAfter(&head,surname);
                ERRORMESSAGE(s);
                break;

            case 7:
                printf("Prezime ispred kojeg dodajemo: ");
                scanf("%19s", surname);
                s = insertBefore(&head, surname);
                ERRORMESSAGE(s);
                break;

            case 8:
                printf("Ime datoteke za upis: ");
                scanf("%49s", fileName);
                s = writeToFile(&head, fileName);
                ERRORMESSAGE(s);
                break;

            case 9:
                printf("Ime datoteke za citanje: ");
                scanf("%49s", fileName);
                s = readFromFile(&head, fileName);
                ERRORMESSAGE(s);
                break;

            case 10:
                s = sortBySurname(&head);
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
    return 0;
}

int insertAfter(Person* Head, char* Surname){
    Person* p = NULL;
    p = findLastName(Head,Surname);
    if (p == NULL){
        return 3;
    }
    char Name[20];
    char surname[20];
    int Year;
    printf("Ime: ");      
    scanf("%19s", Name);
    printf("Prezime: ");  
    scanf("%19s", surname);
    printf("Godina: ");   
    scanf("%d", &Year);
    
    return insertBegin(Name, surname, Year, p);
}

int insertBefore(Person* Head, char* Surname){
    Person* prev = Head;
     if (prev == NULL){
        return 2;
    }
    while (prev->next != NULL){
        if (strcmp(prev->next->surname, Surname) == 0){
            char Name[20];
            char surname[20];
            int Year;
            printf("Ime: ");      
            scanf("%19s", Name);
            printf("Prezime: ");  
            scanf("%19s", surname);
            printf("Godina: ");   
            scanf("%d", &Year);
            return insertBegin(Name, surname, Year, prev);
        }
        prev = prev->next;
    }
    return 3;
}

int writeToFile(Person* Head, char* fileName){
    Person* p = Head->next;
    if (p==NULL){
        return 2;
    }
    FILE* f = fopen(fileName, "w");
    if (f==NULL){
        return 4;
    }
    while(p != NULL){
        fprintf(f, "%s %s %d\n", p->name, p->surname, p->year);
        p = p->next;
    }
    fclose(f);
    return 0;
}

int readFromFile(Person* Head, char* fileName){
    FILE* f = fopen(fileName,"r");
    if (f==NULL){
        return 4;
    }
    char Name[20];
    char Surname[20];
    int Year;

    while (fscanf(f, "%19s %19s %d", Name, Surname, &Year) == 3){
        insertEnd(Name, Surname, Year, Head);
    }
    fclose(f);
    return 0;
}

int sortBySurname(Person* Head){
    if (Head->next == NULL){
		return 2;
    }
    Person* sorted = NULL;
    Person* p = NULL;
    Person* q = NULL;
    Person* temp = NULL;
    while (Head->next != sorted){
        q = Head;
        p = Head->next;

        while (p->next != sorted){
            if (strcmp(p->surname, p->next->surname) > 0){
                temp = p->next;
                q->next = temp;
                p->next = temp->next;
                temp->next = p;
                q = temp;
            }
            else {
                q = p;
                p = p->next;
            }
        }
        sorted = p;
    }
    return 0;
}
