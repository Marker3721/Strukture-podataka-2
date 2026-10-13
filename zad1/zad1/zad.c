#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SCORE 75
#define FILEPATH "zad1/zadFile.txt"


typedef struct {
	char name[15];
	char surname[15];
	int aps_score;
	float rel_score;
}_Student;				

int calculate_rows(char*);
_Student* student_input(char*, int);
void student_output(_Student*, int);			

int main() {
	int num_rows;
	char* filename = FILEPATH;
	_Student* students;

	num_rows = calculate_rows(filename);
	if (num_rows == -1) {
		printf("Datoteka nema redova!\n");
		return 1;
	}

	students = student_input(filename, num_rows);
	if (students == NULL) {
		printf("Neuspjelo ucitavanje studenata.\n");
		return 1;
	}
	student_output(students, num_rows);
	printf("Broj redaka je: %d", num_rows);

	free(students);				
	return 0;
}

int calculate_rows(char* file) {
	FILE* fp = fopen(file, "r");
	if (fp == NULL) {										
		printf("Ne mogu otvoriti datoteku!\n");
		return -1;
	}

	int counter = 0;
	char buffer[1020];
	while (fgets(buffer, 1020, fp)) {			
		counter++;
	}

	if (counter == 0) {	
		fclose(fp);
		return -1;
	}

	return counter;
}

_Student* student_input(char* file, int num_rows) {
	FILE* fp = fopen(file, "r");
	if (fp == NULL) {
		printf("Ne mogu otvoriti datoteku!\n");
		return NULL;
	}

	_Student* s = malloc(num_rows * sizeof(_Student));				
	if (s == NULL) {
		printf("Nema dovoljno memorije!\n");
		fclose(fp);
		return NULL;
	}

	for (int i = 0; i < num_rows; i++) {										
		fscanf(fp, "%14s %14s %d", s[i].name, s[i].surname, &s[i].aps_score);
		s[i].rel_score = ((float)s[i].aps_score / MAX_SCORE) * 100;			
	}

	fclose(fp);
	return s;
}

void student_output(_Student* s, int num_rows) {
	printf("%-20s %-20s %-20s %-10s\n", "Ime", "Prezime", "Bodovi", "Relativni");
	for (int i = 0; i < num_rows; i++) {
		printf("%-20s %-20s %-20d %.2f% %\n", s[i].name, s[i].surname, s[i].aps_score, s[i].rel_score);		
	}
}