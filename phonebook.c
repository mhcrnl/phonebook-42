#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include<time.h>
#include<unistd.h>
#include<ctype.h>
#include "phonebook.h"

#define CLEAR "clear"

int main() {
	menuchoice();
	return 0;
}
void menu(phonebook *p) {
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
			exitapp();
		default: printf("Sorry! Wrong Choice.\n"); 	
			 break;
	}
}

void menuchoice() {
	struct phonebook p;
	FILE *login;
	char password[10], temp[10], *t, pwd[10], *tmp;
	int n;
	system(CLEAR);
	login = fopen("password.txt", "rw+");
	if(login == NULL) {		
		printf("\nSign Up Please\n");
		t = getpass("\nEnter Password :");
		strcpy(password, t);
		t = getpass("\nRe Enter Password :");
		strcpy(temp, t);
		memset(t, 0, strlen(t));
		n = adminsignup(password, temp);
		while(n == 1) {
			system(CLEAR);
			printf("\n Password did not match! \n");
			t = getpass("\nEnter Password :");
			strcpy(password, t);
			t = getpass("\nRe Enter Password :");
			strcpy(temp, t);
			memset(t, 0, strlen(t));
			n = adminsignup(password, temp);
		}		
	}
	else {	
		t_display();
		printf("\n =========== LOG IN =======================\n");	
		t = getpass("\n Enter Password : ");
		strcpy(pwd, t);
		memset(t, 0, strlen(t));
		n = adminsignin(pwd);
		while(n == 1) {
			printf("\n Password did not match! \n");
			t = getpass("\nEnter Password :");
			strcpy(pwd, t);
			memset(t, 0, strlen(t));
			n = adminsignin(pwd);	
		}		
	}
	menu(&p);
}

int addrecord(phonebook *p) {
	char ch;
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
        printf("Enter Address:");
	scanf("%s",p->address);
	save(p->address);
        printf("Enter sex:");
	scanf("%s", p->sex);
        save(p->sex);
        printf("Enter e-mail:");
	scanf("%s", p->mail);
        save(p->mail);
	printf("Enter mobile no: ");
	scanf("%lf", &p->mobile_no); 
	fprintf(fp, "%0.0lf\t", p->mobile_no);
	printf("Enter Date of Birth:");
	scanf("%s", p->dob);
        save(p->dob);
	fprintf(fp, "\n");
	backup(p);
	groupassign(p);
	fclose(fp);
	printf("Record saved successfully.\n");
	printf("Do you wish to continue? (Y/N)\n");
	scanf("%c", &ch);
	if(ch == 'Y' || ch == 'y')
		returnfunc();
	else
		exitapp();
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
	int count = 0, choice;
	char ch;
	printf("Which contacts do you wish to see?\n");
	printf("\t1.Family  \t2.Friends  \t3.Collegue/Office Contacts  \n\t4.Emergency  \t5.All\n");
	printf("Enter your choice of operation\n");
	scanf("%d", &choice);
	if(choice == 1) {
		FILE *fp = fopen("family.txt", "r");
		if(fp == NULL) {
			perror("File opened failed:");
			return errno;
		}
		printf("Your records are..\n");
		while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 			&p->mobile_no, p->dob) != EOF) {
			count++;
			printf("%d\n",count);
			printf("Name:%s %s %s\nAddress:%s\nSex:%s\nE-mail:%s\nMobile No:%0.0lf\nDate of Birth:%s\n", p->fname,        				p->mname, p->lname, p->address, p->sex, p->mail, p->mobile_no, p->dob);  
		}              	        
		fclose(fp);
	}
	else if(choice == 2) {
		FILE *fp = fopen("friends.txt", "r");
		if(fp == NULL) {
			perror("File opened failed:");
			return errno;
		}
		printf("Your records are..\n");
		while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 			&p->mobile_no, p->dob) != EOF) {
			count++;
			printf("%d\n",count);
			printf("Name:%s %s %s\nAddress:%s\nSex:%s\nE-mail:%s\nMobile No:%0.0lf\nDate of Birth:%s\n", p->fname,        				p->mname, p->lname, p->address, p->sex, p->mail, p->mobile_no, p->dob);  
		}              	        
		fclose(fp);
	}
	else if(choice == 3) {
		FILE *fp = fopen("office.txt", "r");
		if(fp == NULL) {
			perror("File opened failed:");
			return errno;
		}
		printf("Your records are..\n");
		while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 			&p->mobile_no, p->dob) != EOF) {
			count++;
			printf("%d\n",count);
			printf("Name:%s %s %s\nAddress:%s\nSex:%s\nE-mail:%s\nMobile No:%0.0lf\nDate of Birth:%s\n", p->fname,        				p->mname, p->lname, p->address, p->sex, p->mail, p->mobile_no, p->dob);  
		}              	        
		fclose(fp);
	}
	else if(choice == 4) {
		FILE *fp = fopen("emergency.txt", "r");
		if(fp == NULL) {
			perror("File opened failed:");
			return errno;
		}
		printf("Your records are..\n");
		while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 			&p->mobile_no, p->dob) != EOF) {
			count++;
			printf("%d\n",count);
			printf("Name:%s %s %s\nAddress:%s\nSex:%s\nE-mail:%s\nMobile No:%0.0lf\nDate of Birth:%s\n", p->fname,        				p->mname, p->lname, p->address, p->sex, p->mail, p->mobile_no, p->dob);  
		}              	        
		fclose(fp);
	}
	else if(choice == 5) {
		FILE *fp = fopen("record.txt", "r");
		if(fp == NULL) {
			perror("File opened failed:");
			return errno;
		}
		printf("Your records are..\n");
		while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 			&p->mobile_no, p->dob) != EOF) {
			count++;
			printf("%d\n",count);
			printf("Name:%s %s %s\nAddress:%s\nSex:%s\nE-mail:%s\nMobile No:%0.0lf\nDate of Birth:%s\n", p->fname,        				p->mname, p->lname, p->address, p->sex, p->mail, p->mobile_no, p->dob);  
		}              	        
		fclose(fp);
	}
	else 
		printf("Sorry! Wrong Choice.\n"); 
	printf("Do you wish to continue? (Y/N)\n");
	scanf("%c", &ch);
	if(ch == 'Y' || ch == 'y')
		returnfunc();
	else
		exitapp();	
	return 0;
}

int modifyrecord(phonebook *p) {
	double mobile_no;
	int flag = 0, choice;
	phonebook *x, *q;
	char ch;
	FILE *fp = fopen("record.txt", "a+");
	FILE *fpb = fopen("backup.txt", "a+");
	if(fp == NULL) {
		perror("File opened failed:");
		return errno;
	}
	if(fpb == NULL) {
		perror("File opened failed:");
		return errno;
	}
	printf("Enter orignal/initial mobile no. of the contact whose data you need to modify:\n");
	scanf(" %lf", &mobile_no);
	x = isavailable(p, mobile_no);
	if(x != NULL) {
		printf("Data found..\n");
		printf("%s\n %s\n %s\n %s\n %s\n %s\n %0.0lf\n %s\n", x->fname, x->mname, x->lname, x->address, x->sex, x->mail, 			x->mobile_no, x->dob);
		printf("Enter New Data to modify the record\n");
		printf("----------------------------------------\n");
		printf("Which field do you wish to modify for the specified contact?\n"); 
		printf("1.First Name\n2.Middle Name\n3.Last Name\n4.Mobile No.\n5.Address\n6.Sex\n7.E-mail\n8.DOB\n");
		scanf("%d", &choice);
		switch(choice) {
			case 1:			
				printf("Enter first name: ");
				scanf("%s", x->fname);
				break;
			case 2:			
				printf("Enter middle name: ");
				scanf("%s", x->mname);
				break;
			case 3:			
				printf("Enter last name: ");
				scanf("%s", x->lname);
				break;
			case 4:			
				printf("Enter mobile no: ");
				scanf("%lf", &x->mobile_no);
				break;
			case 5:
				printf("Enter Address:");
				scanf("%s",x->address);
				break;
			case 6:			
				printf("Enter sex:");
				scanf("%s", x->sex);
				break;
			case 7:
				printf("Enter e-mail:");
				scanf("%s", x->mail);
				break;
			case 8:
				printf("Enter date of birth:");
				scanf("%s", x->dob);
				break;
		}
		printf("CONFIRMATION!\n");
		printf("Do you wish to modify this record?(Y/N)\n");
		scanf("%c", &ch);
		if(ch == 'y' || 'Y') {
			strcpy(q->fname, x->fname);
			strcpy(q->mname, x->mname);
			strcpy(q->lname, x->lname);
			strcpy(q->address, x->address);
			strcpy(q->sex, x->sex);
			strcpy(q->mail, x->mail);
			strcpy(q->dob, x->dob);
			q->mobile_no = x->mobile_no;
			fprintf(fp, "\n");
              		fprintf(fp,"%s %s %s %s %s %s %0.0lf %s", q->fname, q->mname, q->lname, q->address, q->sex, q->mail, 
			q->mobile_no, q->dob);
			x->fname[0] = x->lname[0] = x->mname[0] = x->address[0] = x->sex[0] = x->mail[0] = x->dob[0] = '\0';
			x->mobile_no = -1;
			fclose(fpb);
			flag = 1;
			if(flag == 1) {
				backup(q);
				printf("*******************************\n");
				printf("Record Updated Successfully.\n");
				printf("-------------------------------\n");
			}
			else {
				printf("*******************\n");
				printf("Data not found.\n");
				printf("-------------------\n");
			}
		}
		else
			return;
	}
	else {
		printf("*******************\n");
		printf("Data not found.\n");
		printf("-------------------\n");	
	}	
	fclose(fp);
	printf("Do you wish to continue? (Y/N)\n");
	scanf("%c", &ch);
	if(ch == 'Y' || ch == 'y')
		returnfunc();
	else
		exitapp();
	return 0;
}

int backup(phonebook *p) {
	FILE *fp1 = fopen("record.txt", "r");
	FILE *fp2 = fopen("backup.txt", "a+");
	if(fp1 == NULL || fp2 == NULL) {
		perror("File opened failed:");
		return errno;
	}
	while(fscanf(fp1,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
	&p->mobile_no, p->dob) != EOF) {
		fprintf(fp2,"%s %s %s %s %s %s %0.0lf %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
		p->mobile_no, p->dob);
		fprintf(fp2, "\n");
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}	

int searchrecord(phonebook *p) {
	char fname[35], mname[35], lname[35], address[50], sex[8], mail[100], dob[20], ch;
	double mobile_no;
	int flag = 0, count = 0, choice;	
	FILE *fp = fopen("record.txt", "r");
	if(fp == NULL) {
		perror("File opened failed:");
		return errno;
	}
	printf("Enter the field you wish search the contact on?\n"); 
	printf("1.First Name\n2.Middle Name\n3.Last Name\n4.Mobile No.\n5.Address\n6.Sex\n7.E-mail\n8.DOB\n");
	scanf("%d", &choice);
	switch(choice) {
		case 1:			
			printf("Enter first name: ");
			scanf("%s", fname);
			while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
			&p->mobile_no, p->dob) != EOF) {
				if(strcmp(fname, p->fname) == 0) {
					count++;
					printf("%d\n",count);					
					printf("Name:%s %s %s\nCity:%s\nSex:%s\nE-mail:%s\nMobile No:%0.0lf\nDate of Birth:%s\n", p->fname,    						p->mname, p->lname, p->address, p->sex, p->mail, p->mobile_no, p->dob);  
				}
			}
			flag = 1;
			break;
		case 2:			
			printf("Enter middle name: ");
			scanf("%s", mname);
			while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
			&p->mobile_no, p->dob) != EOF) {
				if(strcmp(mname, p->mname) == 0) {
					count++;
					printf("%d\n",count);
					printf("Name:%s %s %s\nCity:%s\nSex:%s\nE-mail:%s\nMobile No:%0.0lf\nDate of Birth:%s\n", p->fname,   						p->mname, p->lname, p->address, p->sex, p->mail, p->mobile_no, p->dob); 
				}
			}
			flag = 1;
			break;
		case 3:			
			printf("Enter last name: ");
			scanf("%s", lname);
			while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
			&p->mobile_no, p->dob) != EOF) {
				if(strcmp(lname, p->lname) == 0) {
					count++;
					printf("%d\n",count);
					printf("Name:%s %s %s\nCity:%s\nSex:%s\nE-mail:%s\nMobile No:%0.0lf\nDate of Birth:%s\n", p->fname,   						p->mname, p->lname, p->address, p->sex, p->mail, p->mobile_no, p->dob); 
				}
			}
			flag = 1;	
			break;
		case 4:			
			printf("Enter mobile no: ");
			scanf("%lf", &mobile_no);
			while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
			&p->mobile_no, p->dob) != EOF) {
				if(mobile_no == p->mobile_no) {
					count++;
					printf("%d\n",count);
					printf("Name:%s %s %s\nCity:%s\nSex:%s\nE-mail:%s\nMobile No:%0.0lf\nDate of Birth:%s\n", p->fname,   						p->mname, p->lname, p->address, p->sex, p->mail, p->mobile_no, p->dob); 
				}
			}
			flag = 1;
			break;
		case 5:
			printf("Enter Address:");
			scanf("%s", address);
			while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
			&p->mobile_no, p->dob) != EOF) {
				if(strcmp(address, p->address) == 0) {
					count++;
					printf("%d\n",count);
					printf("Name:%s %s %s\nCity:%s\nSex:%s\nE-mail:%s\nMobile No:%0.0lf\nDate of Birth:%s\n", p->fname,   						p->mname, p->lname, p->address, p->sex, p->mail, p->mobile_no, p->dob); 
				}
			}
			flag = 1;
			break;
		case 6:			
			printf("Enter sex:");
			scanf("%s", sex);
			while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
			&p->mobile_no, p->dob) != EOF) {
				if(strcmp(sex, p->sex) == 0) {
					count++;
					printf("%d\n",count);
					printf("Name:%s %s %s\nCity:%s\nSex:%s\nE-mail:%s\nMobile No:%0.0lf\nDate of Birth:%s\n", p->fname,   						p->mname, p->lname, p->address, p->sex, p->mail, p->mobile_no, p->dob); 
				}
			}
			flag = 1;
			break;
		case 7:
			printf("Enter e-mail:");
			scanf("%s", mail);
			while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
			&p->mobile_no, p->dob) != EOF) {
				if(strcmp(mail, p->mail) == 0) {
					count++;
					printf("%d\n",count);
					printf("Name:%s %s %s\nCity:%s\nSex:%s\nE-mail:%s\nMobile No:%0.0lf\nDate of Birth:%s\n", p->fname,   						p->mname, p->lname,p->address, p->sex, p->mail, p->mobile_no, p->dob); 
				}
			}
			flag = 1;
			break;
		case 8:
			printf("Enter date of birth:");
			scanf("%s", dob);
			while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
			&p->mobile_no, p->dob) != EOF) {
				if(strcmp(dob, p->dob) == 0) {
					count++;
					printf("%d\n",count);
					printf("Name:%s %s %s\nCity:%s\nSex:%s\nE-mail:%s\nMobile No:%0.0lf\nDate of Birth:%s\n", p->fname,   						p->mname, p->lname, p->address, p->sex, p->mail, p->mobile_no, p->dob); 
				}
			}
			flag = 1;
			break;
		default: printf("Sorry! Wrong Choice.\n"); 	
				 break;
	}
	if(flag != 1) {
		printf("*******************\n");
		printf("Record not found.\n");
		printf("-------------------\n");	
	}	      	        
	fclose(fp);
	printf("Do you wish to continue? (Y/N)\n");
	scanf("%c", &ch);
	if(ch == 'Y' || ch == 'y')
		returnfunc();
	else
		exitapp();
	return 0;
}

int deleterecord(phonebook *p) {
	int flag = 0;	
	double mobile_no;
	phonebook *x;
	char ch;
	FILE *fp = fopen("record.txt", "a+");
	FILE *fpb = fopen("backup.txt", "a+");
	if(fp == NULL) {
		perror("File opened failed:");
		return errno;
	}
	if(fpb == NULL) {
		perror("File opened failed:");
		return errno;
	}
	printf("Enter mobile no. of the contact whose data you need to delete:\n");
	scanf(" %lf", &mobile_no);
	x = isavailable(p, mobile_no);
	if(x != NULL) {
		printf("Data found..\n");
		printf("%s\n %s\n %s\n %s\n %s\n %s\n %0.0lf\n %s\n", x->fname, x->mname, x->lname, x->address, x->sex, x->mail, 			x->mobile_no, x->dob);
		printf("CONFIRMATION!\n");
		printf("Do you wish to delete this record?(Y/N)\n");
		scanf("%c", &ch);
		if(ch == 'y' || 'Y'){
			x->fname[0] = x->lname[0] = x->mname[0] = x->address[0] = x->sex[0] = x->mail[0] = x->dob[0] = '\0';
			x->mobile_no = -1;
			flag = 1;
		}
		if(flag == 1) {
			backup(p);
			printf("*******************************\n");
			printf("Record Deleted Successfully\n");
			printf("-------------------------------\n");
		}
		else {
			printf("-------------------------------\n");			
			printf("Operation Cancelled\n");
			printf("-------------------------------\n");
		}		
	}
	else {
		printf("*******************\n");
		printf("Data not found.\n");
		printf("-------------------\n");	
	}	
	fclose(fp);
	printf("Do you wish to continue? (Y/N)\n");
	scanf("%c", &ch);
	if(ch == 'Y' || ch == 'y')
		returnfunc();
	else
		exitapp();	
	return 0;
}

phonebook *isavailable(phonebook *p, double mobile_no) {
	FILE *fp = fopen("record.txt", "r");
	if(fp == NULL) {
		perror("File opened failed:");
		return NULL;
	}
	while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
	&p->mobile_no, p->dob) != EOF) {
		if(mobile_no == p->mobile_no)
			return p;
		else
			return NULL;	
	}
	fclose(fp);
}

int groupassign(phonebook *p) {
	int choice;
	char ch;
	printf("Which group would you like to assign to this contact?\n");
	printf("\t1.Family  \t2.Friends  \t3.Collegue/Office Contacts  \n\t4.Emergency  \t5.No group for this contact!\n");
	printf("Enter your choice of operation\n");
	scanf("%d", &choice);
	if (choice == 1) {
		FILE *fp = fopen("family.txt", "a+");
		if(fp == NULL) {
			perror("File opened failed:");
			return errno;
		}
		fprintf(fp,"%s %s %s %s %s %s %0.0lf %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, p->mobile_no, p->dob);
		fprintf(fp, "\n");
		fclose(fp);			
	}		
	else if(choice == 2) {
		FILE *fp = fopen("friends.txt", "a+");
		if(fp == NULL) {
			perror("File opened failed:");
			return errno;
		}
		fprintf(fp,"%s %s %s %s %s %s %0.0lf %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
		p->mobile_no, p->dob);
		fprintf(fp, "\n");
		fclose(fp);	
	}
	else if(choice == 3) {
		FILE *fp = fopen("office.txt", "a+");
		if(fp == NULL) {
			perror("File opened failed:");
			return errno;
		}
		fprintf(fp,"%s %s %s %s %s %s %0.0lf %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
		p->mobile_no, p->dob);
		fprintf(fp, "\n");
		fclose(fp);	
	}
	else if(choice == 4) {
		FILE *fp = fopen("emergency.txt", "a+");
		if(fp == NULL) {
			perror("File opened failed:");
			return errno;
		}
		fprintf(fp,"%s %s %s %s %s %s %0.0lf %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
		p->mobile_no, p->dob);
		fprintf(fp, "\n");
		fclose(fp);	
	}
	else if(choice == 5) {
		printf("No group assigned to this contact\n");
	}
	else
		 printf("Sorry! Wrong Choice.\n"); 	
	printf("Do you wish to continue? (Y/N)\n");
	scanf("%c", &ch);
	if(ch == 'Y' || ch == 'y')
		returnfunc();
	else
		exitapp();
	return 0;
}

void exitapp() {
	system(CLEAR);
	t_display();
	printf("Exiting in 1 second...........>\n");
	sleep(1);	
	exit(0);
}

void returnfunc() {
	printf(" \n Press ENTER to return to Main Menu  ");
	getchar();
	a: 
		if(getchar() == '\n') {
			 struct phonebook p;
			menu(&p);
		}
		else
			goto a;
}

void t_display(void) {
	time_t t;
	time(&t);
	printf("\nDate and time: %s\n", ctime(&t));
}

int adminsignup(char *password, char *temp) {
	FILE *login;
	login = fopen("password.txt", "w");
	if(!strcmp(password, temp)) {
		fwrite(password, 1, sizeof(password), login);
		fclose(login);		
		return 0;
	}
	else {	
		return 1;
	}
}

int adminsignin(char *password) {
	FILE *login;
	char tmp[10];
	int cnt;
	login = fopen("password.txt", "r");
	cnt = fread(tmp, sizeof(char), 10, login);	
	tmp[cnt] = '\0';
	if(strcmp(password, tmp) == 0) {	
		return 0;
	}
	else {	
		return 1;
	}
}
