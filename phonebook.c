
/*****************************************************************************
 * Copyright (C) Sneha.A.Shinde   shindesa14.comp@coep.ac.in
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

/*PHONEBOOK*/

/*This is a phonebook application which allows the user to store personal information in a very organised manner*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include "phonebook.h"

#define CLEAR "clear"

int main() {
	struct phonebook p;
	menu(&p);
	return 0;
}

/*This function displays the MENU of the phonebook*/

void menu(phonebook *p) {
	system(CLEAR);
	int choice, i;
	for(i = 0; i < 80; i++)
		printf("=");
	printf("\n\n\t\t\t\t  MENU\t\t\n");
	for(i = 0; i < 80; i++)
		printf("=");
	printf("\n");
	printf("\t\t\t1.Add New Record  \n\t\t\t2.List Records  \n\t\t\t3.Modify a Record  \n\t\t\t4.Search a Record  \n\t\t\t5.Delete a Record  \n\t\t\t6.Exit\n");
	for(i = 0; i < 80; i++)
		printf("=");
	printf("\n");
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
		case 6: printf("Application closed.\n");
			for(i = 0; i < 80; i++)
				printf("-");
				printf("\n");
			exitapp();
		default: printf("Sorry! Wrong Choice.\n"); 	
			 break;
	}
}

/*This function helps in adding a new record in the phonebook*/

int addrecord(phonebook *p) {
	char ch[3];
	int i;
	FILE *fp = fopen("record.txt", "a");
	if(fp == NULL) {
		perror("Database File opened failed:");
		return errno;
	}
	printf("Enter New Data for the record\n");
	for(i = 0; i < 80; i++)
		printf("=");
	printf("\n");
	/*As soon as the input of a new record is taken from the user, it is written on the file*/ 
	printf("Enter first name: ");
	scanf("%s", p->fname);
        fprintf(fp, "%s ", p->fname);
        printf("Enter middle name: ");
        scanf("%s", p->mname);
        fprintf(fp, "%s ", p->mname);
        printf("Enter last name: ");
	scanf("%s", p->lname);
        fprintf(fp, "%s ", p->lname);
        printf("Enter Address:");
	scanf("%s",p->address);
	fprintf(fp, "%s ", p->address);
        printf("Enter sex:");
	scanf("%s", p->sex);
        fprintf(fp, "%s ", p->sex);
        printf("Enter e-mail:");
	scanf("%s", p->mail);
        fprintf(fp, "%s ", p->mail);
	printf("Enter mobile no: ");
	scanf("%lf", &p->mobile_no); 
	fprintf(fp, "%lf\t", p->mobile_no);
	printf("Enter Date of Birth:");
	scanf("%s", p->dob);
        fprintf(fp, "%s ", p->dob);
	fprintf(fp, "\n");
	system(CLEAR);
	groupassign(p);
	fclose(fp);
	system(CLEAR);
	for(i = 0; i < 80; i++)
			printf("*");
	printf("\n\t\t\t\tRecord saved successfully.\t\t\n");
	for(i = 0; i < 80; i++)
			printf("*");
	printf("\n");
	printf("Do you wish to continue? (Y/N)\n");
	scanf("%s", ch);
	if(strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
		returnfunc();
	else
		exitapp();
	return 0;
}

/*This function lists all the records in the phonebook according to various categories*/

int listrecord(phonebook *p) {
	int count = 0, choice, i;
	char ch[3];
	printf("Which contacts do you wish to see?\n");
	for(i = 0; i < 80; i++)
			printf("-");
	printf("\n1.Family  \n2.Friends  \n3.Collegue/Office Contacts  \n4.Emergency  \n5.All\n");
	for(i = 0; i < 80; i++)
			printf("-");
	printf("\n");
	printf("Enter your choice of operation\n");
	scanf("%d", &choice);
	system(CLEAR);
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
	scanf("%s", ch);
	if(strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
		returnfunc();	
	else
		exitapp();
	return 0;
}

/*This function modifies a particular record stored in the phonebook*/

int modifyrecord(phonebook *p) {
	int flag = 0, choice, x = 0, i;
	char fname[30], lname[30], ch[3];
	FILE *fp = fopen("record.txt", "a+");
	if(fp == NULL) {
		perror("File opened failed:");
		return errno;
	}
	printf("Enter first name and last name of the contact whose data you need to modify:\n");
	scanf(" %s%s", fname, lname);
	while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
	&p->mobile_no, p->dob) != EOF) {
		if(strcmp(p->fname, fname) == 0 && strcmp(p->lname, lname) == 0)
			x = 1;
	}
	if(x == 1) {
		printf("Data found..\n");
		printf("%s\n %s\n %s\n %s\n %s\n %s\n %0.0lf\n %s\n", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 			p->mobile_no, p->dob);
		printf("Enter New Data to modify the record\n");
		for(i = 0; i < 80; i++)
			printf("=");
		printf("\n");
		printf("Which field do you wish to modify for the specified contact?\n"); 
		for(i = 0; i < 80; i++)
			printf("-");
		printf("\n");
		printf("1.First Name\n2.Middle Name\n3.Last Name\n4.Mobile No.\n5.Address\n6.Sex\n7.E-mail\n8.DOB\n");
		for(i = 0; i < 80; i++)
			printf("-");
		printf("\n");
		printf("Enter your choice of operation:\n");
		scanf("%d", &choice);
		switch(choice) {
			case 1:			
				printf("Enter first name: ");
				scanf("%s", p->fname);
				break;
			case 2:			
				printf("Enter middle name: ");
				scanf("%s", p->mname);
				break;
			case 3:			
				printf("Enter last name: ");
				scanf("%s", p->lname);
				break;
			case 4:			
				printf("Enter mobile no: ");
				scanf("%lf", &p->mobile_no);
				break;
			case 5:
				printf("Enter Address:");
				scanf("%s",p->address);
				break;
			case 6:			
				printf("Enter sex:");
				scanf("%s", p->sex);
				break;
			case 7:
				printf("Enter e-mail:");
				scanf("%s", p->mail);
				break;
			case 8:
				printf("Enter date of birth:");
				scanf("%s", p->dob);
				break;
		}
		printf("CONFIRMATION!\n");
		printf("Do you wish to modify this record?(Y/N)\n");
		scanf("%s", ch);
		if(strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0) {
			fprintf(fp, "\n");
              		fprintf(fp,"%s %s %s %s %s %s %0.0lf %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
			p->mobile_no, p->dob);
			fprintf(fp, "\n");
			flag = 1;
			if(flag == 1) {
				for(i = 0; i < 80; i++)
					printf("*");
				printf("\n");
				printf("Record Updated Successfully.\n");
				for(i = 0; i < 80; i++)
					printf("*");
				printf("\n");
			}
			else {
				for(i = 0; i < 80; i++)
					printf("-");
				printf("\n");
				printf("Data not found.\n");
				for(i = 0; i < 80; i++)
					printf("-");
				printf("\n");	
			}
		}
		else
			returnfunc();
	}
	else {
		for(i = 0; i < 80; i++)
			printf("-");
		printf("\n");
		printf("Data not found.\n");
		for(i = 0; i < 80; i++)
			printf("-");
		printf("\n");	
	}	
	fclose(fp);
	printf("Do you wish to continue? (Y/N)\n");
	scanf("%s", ch);
	if(strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
		returnfunc();
	else
		exitapp();
	return 0;
}

/*This function searches and displays a particular record stored in the phonebook according to the user's needs*/	

int searchrecord(phonebook *p) {
	char fname[35], mname[35], lname[35], address[50], sex[8], mail[100], dob[20], ch[3];
	double mobile_no;
	int flag = 0, count = 0, choice, i;	
	FILE *fp = fopen("record.txt", "r");
	if(fp == NULL) {
		perror("File opened failed:");
		return errno;
	}
	printf("Enter the field you wish search the contact on?\n"); 
	for(i = 0; i < 80; i++)
		printf("-");
	printf("\n");
	printf("1.First Name\n2.Middle Name\n3.Last Name\n4.Mobile No.\n5.Address\n6.Sex\n7.E-mail\n8.DOB\n");
	for(i = 0; i < 80; i++)
		printf("-");
	printf("\n");
	printf("Enter your choice of operation:\n");
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
		for(i = 0; i < 80; i++)
			printf("-");
		printf("\n");
		printf("Record not found.\n");
		for(i = 0; i < 80; i++)
			printf("-");
		printf("\n");	
	}	      	        
	fclose(fp);
	printf("Do you wish to continue? (Y/N)\n");
	scanf("%s", ch);
	if(strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
		returnfunc();
	else
		exitapp();
	return 0;
}

/*This function deletes a particular record stored in the phonebook*/

int deleterecord(phonebook *p) {
	int flag = 0, x = 0, i;
	char fname[30], lname[30], ch[3];
	FILE *fp = fopen("record.txt", "a+");
	if(fp == NULL) {
		perror("File opened failed:");
		return errno;
	}
	printf("Enter first name and last name of the contact whose data you need to delete:\n");
	scanf(" %s%s", fname, lname);
	while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n %s", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
	&p->mobile_no, p->dob) != EOF) {
		if(strcmp(p->fname, fname) == 0 && strcmp(p->lname, lname) == 0)
			x = 1;
	}
	if(x == 1) {
		printf("Data found..\n");
		printf("%s\n %s\n %s\n %s\n %s\n %s\n %0.0lf\n %s\n", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 			p->mobile_no, p->dob);
		printf("CONFIRMATION!\n");
		printf("Do you wish to delete this record?(Y/N)\n");
		scanf("%s", ch);
		if(strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0) {
			p->fname[0] = p->lname[0] = p->mname[0] = p->address[0] = p->sex[0] = p->mail[0] = p->dob[0] = '\0';
			p->mobile_no = -1;
			flag = 1;
		}
		if(flag == 1) {
			for(i = 0; i < 80; i++)
				printf("*");
			printf("\n");
			printf("Record Deleted Successfully\n");
			for(i = 0; i < 80; i++)
				printf("*");
			printf("\n");
		}
		else {
			for(i = 0; i < 80; i++)
				printf("*");
			printf("\n");			
			printf("Operation Cancelled\n");
			for(i = 0; i < 80; i++)
				printf("-");
			printf("\n");
		}		
	}
	else {
		for(i = 0; i < 80; i++)
			printf("-");
		printf("\n");
		printf("Data not found.\n");
		for(i = 0; i < 80; i++)
			printf("-");
		printf("\n");	
	}	
	fclose(fp);
	printf("Do you wish to continue? (Y/N)\n");
	scanf("%s", ch);
	if(strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
		returnfunc();
	else
		exitapp();	
	return 0;
}

/*This function helps in assigning a specified group to a particular record*/

int groupassign(phonebook *p) {
	int choice, i;
	char ch[3];
	printf("Which group would you like to assign to this contact?\n");
	for(i = 0; i < 80; i++)
		printf("-");
	printf("\n");
	printf("\t1.Family  \t2.Friends  \t3.Collegue/Office Contacts  \n\t4.Emergency  \t5.No group for this contact!\n");
	for(i = 0; i < 80; i++)
		printf("-");
	printf("\n");
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
	scanf("%s", ch);
	if(strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
		returnfunc();
	else
		exitapp();
	return 0;
}

/*This function is responsible for exiting from the application*/

void exitapp() {
	system(CLEAR);
	exit(0);
}

/*This function helps in returning to the MAIN MENU after completing a particular task*/

void returnfunc() {
	system(CLEAR);
	struct phonebook p;
	menu(&p);
}

