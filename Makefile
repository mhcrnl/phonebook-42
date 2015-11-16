project: phonebook.o 
	cc phonebook.o -o project
phonebook.o: phonebook.c phonebook.h
	cc -Wall -c phonebook.c

