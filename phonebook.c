#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "phonebook.h"
#define SIZE 100
int main() {
	struct phonebook p;
	menu(&p);
	return 0;
}
void menu(phonebook *p) {
	while(1) {
		int choice;
		printf("\n\n\t\t\t  MENU\t\t\n");
		printf("\t1.Add New Record  \t2.List Records  \t3.Modify a Record  \n\t4.Search a Record  \t5.Delete a Record  \t6.Exit\n");
		printf("Enter your choice of operation\n");
		scanf("%d", &choice);
		switch(choice) {
			case 1: addrecord(p);
				break;
			case 2: listrecord(p);
				break;
			case 3: modifyrecord(p);
				break;
			case 4: searchrecord(p);
				break;
			case 5: deleterecord(p);
				break;
			case 6: 
				printf("Application closed.\n");
				exit(0);
			default: printf("Sorry! Wrong Choice.\n"); 	
				 break;
		}
	}
}

int addrecord(phonebook *p) {
	FILE *fp = fopen("record.txt", "a");
	if(fp == NULL) {
		perror("Database File opened failed:");
		return errno;
	}
	printf("Enter first name: ");
	scanf("%s", p->fname);
        save(p->fname);
        printf("Enter middle name: ");
        scanf("%s", p->mname);
        save(p->mname);
        printf("Enter last name: ");
	scanf("%s", p->lname);
        save(p->lname);
        printf("Enter mobile no: ");
	scanf("%lf", &p->mobile_no); 
        printf("Enter City:");
	scanf("%s",p->address);
	save(p->address);
        printf("Enter sex:");
	scanf("%s", p->sex);
        save(p->sex);
        printf("Enter e-mail:");
	scanf("%s", p->mail);
        save(p->mail);
	 printf("Enter Date of Birth:");
	scanf("%s", p->dob);
        save(p->dob);
	fprintf(fp, "\n");
	fclose(fp);
	printf("Record saved successfully.\n");
	return 0;
}

int save(char *data) {
	FILE *fp = fopen("record.txt", "a");
	if(fp == NULL) {
		perror("Database File opened failed:");
		return errno;
	}
	else {
		fprintf(fp, "%s ", data);
		fclose(fp); 
	}
	return 0;	
}

int listrecord(phonebook *p) {
	int count = 0;
	FILE *fp = fopen("record.txt", "r");
	if(fp == NULL) {
		perror("File opened failed:");
		return errno;
	}
	printf("Your records are..\n");
	while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, &p->mobile_no,
	p->dob) != EOF) {
		count++;
		printf("%d\n",count);
		printf("Name:%s %s %s\nCity:%s\nMobile No:%0.0lf\nSex:%s\nE-mail:%s\n ", p->fname, p->mname, p->lname, p->address,
		p->mobile_no, p->sex, p->mail, p->dob);    
	}
	fclose(fp);
	return 0;
}

int modifyrecord(phonebook *p) {
	return 0;
}

int searchrecord(phonebook *p) {
	return 0;
}

int deleterecord(phonebook *p) {
	return 0;
}

int isavailable(phonebook *p) {
	return 0;
}
















