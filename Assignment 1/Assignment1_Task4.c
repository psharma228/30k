#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int TABLE_SIZE  = 100;
int MAX_BUFFER = 60;
int collisions = 0;
int totalPerson = 0;

typedef struct person_record person_record;
typedef struct person_record{
	
    char person_Id[20];
    char deposition_id[20];
    char surname[20];
    char forename[20];
    char age[20];
    char personType[20];
    char gender[20];
    char nationality[20];
    char religion[20];
    char occupation[20];
    person_record *next;
}person_record;

typedef struct person person;
typedef struct person
{
    char name[60];
    char p_id[20];
    char d_id[20];
    char Age[20];
    char type[20];
    person* next;
}person;

typedef struct table{

    char surname[60];
    person* head;

}table;


int hash(char *s)
{
    int hash = 0;
    while (*s) 
	{
    hash = (hash + *s)% TABLE_SIZE;
    s++;
    }
    return hash ;
}

int hash2(char *s){
     int hash = 0;
    while(*s){
        hash = hash + *s;
        s++;
    }
    hash = 11 - (hash % 11);
    return hash;
}

/*
void initalize_table(list *hash_table)
{
    for (int i=0; i<TABLE_SIZE; i++)
	{
	strcpy(hash_table[i].name, "");
   	hash_table[i].frequency = 0;
    }
    
}
*/

int next_field(FILE *f, char *buff, int max){
    int i = 0, end = 0, temp = 0;

    for (;;){
        buff[i] = fgetc(f); 																// get next character
        
        if (buff[i] == '"') {
            temp = !temp;
            buff[i] = fgetc(f);
        }

        if (buff[i] == ',' && !temp) 
            break;
   
        if (feof(f) || buff[i] == '\n'){
            end = 1;
            break;
        }
        if (i < max - 1)
            ++i;
    }
    buff[i] = 0; 
    return end; 
}

void get_Info(FILE *f, struct person_record *p){
    char buffer[MAX_BUFFER];
    
    next_field(f, buffer, MAX_BUFFER);
    strcpy(p->person_Id, buffer);
    
    next_field(f, buffer, MAX_BUFFER);
    strcpy(p->deposition_id, buffer);
    
	next_field(f, buffer, MAX_BUFFER);
    strcpy(p->surname, buffer);
    
	next_field(f, buffer, MAX_BUFFER);
    strcpy(p->forename, buffer);
    
	next_field(f, buffer, MAX_BUFFER);
    strcpy(p->age,buffer);
    
	next_field(f, buffer, MAX_BUFFER);
    strcpy(p->forename, buffer);
    
	next_field(f, buffer, MAX_BUFFER);
    strcpy(p->gender, buffer);
    
	next_field(f, buffer, MAX_BUFFER);
    strcpy(p->nationality, buffer);

	next_field(f, buffer, MAX_BUFFER);
    strcpy(p->religion, buffer);

	next_field(f, buffer, MAX_BUFFER);
	strcpy(p->occupation, buffer);

}


int update_table(struct person_record *p, table *t)											 		// To find number of collisions
{    
    int collisions = 0;
    int index = hash(p->surname);

    if (strcmp(t[index].surname, p->surname) == 0 || t[index].head == NULL)
	{
	
    if(t[index].head == NULL){
            strcpy(t[index].surname, p->surname);											//use linked list
            person *temp= (person*)malloc(sizeof(person));
            t[index].head = temp;
            strcpy(temp->name, p->forename);
            strcpy(temp->p_id, p->person_Id);
            strcpy(temp->d_id, p->deposition_id);
            strcpy(temp->Age, p->age);
            strcpy(temp->type, p->personType);
            temp->next = NULL;
        }
    else 																				 			
	{ 																				 	    
            person *ptr =  t[index].head;												// find the last node 
            while (ptr->next != NULL){
                ptr = ptr->next;
            }
            person *temp= (person*)malloc(sizeof(person));
            ptr->next = temp;
            strcpy(temp->name, p->forename);
            strcpy(temp->p_id, p->person_Id);
            strcpy(temp->d_id, p->deposition_id);
            strcpy(temp->Age, p->age);
            strcpy(temp->type, p->personType);
            temp->next = NULL;
        }													 
    }
        
	else { 																			//Loop to find a free cell or a cell with the same key
        while (t[index].head != NULL){ 
        
            if ((index + hash2(p->surname)) < TABLE_SIZE)
                index += hash2(p->surname);
            else
                index = (index + hash2(p->surname)) - TABLE_SIZE;
            collisions++;
        }
        strcpy(t[index].surname, p->surname);
        person *temp= (person*)malloc(sizeof(person));
        t[index].head = temp;
        strcpy(temp->name, p->surname);
        temp->next = NULL;
    }

    return collisions;
}

/*
void printHashTable(list *hash_table, int size){
    for(int i=0; i<size; i++){
        printf("[%d] %s %d \n", i, hash_table[i].name, hash_table[i].frequency);
    }
}
*/

void search(table *t) {
    char s[MAX_BUFFER];
    int index;
    
    printf("\nEnter surname to get full name or type 'quit' to escape \n");
    while (1) {
    	printf("--> ");
        gets(s);
        if (strcmp(s, "quit") == 0)	break;
        index = hash(s);
        if (t[index].head != NULL){
            printf("%s ", t[index].surname);
            person *curr = t[index].head;
            while(curr != NULL){
                printf("%s\t", curr->name);
                printf("%s\t", curr->p_id);
                printf("%s\t", curr->d_id);
                printf("%s\t", curr->Age);
                printf("%s\t", curr->type);
                curr = curr->next;
            }
            printf("\n");
        } 
        else
            printf("%s is not in the hash table\n", s);
    }
}

void free_table(table *t, int s){
    person *ptr, *next;

        for(int i=0; i<s; i++){ 
            if(t[i].head != NULL){
            ptr = t[i].head;
            while(ptr != NULL){
                next = ptr->next;
                free(ptr);
                ptr = next;
            }
        }
        t[i].head = NULL;
    
}

}
/*
void print_stats(list *hash_table, int size, int collisions, int terms)
{
    int temp = 0;
    for (int i=0; i<TABLE_SIZE; i++)
	{
        if (hash_table[i].frequency != 0)
            temp ++;
	}
    printf("\nCapacity			-> %d\n", size);
    printf("Num terms			-> %d\n", terms);
   // printf("Number of unique Values 	-> %d\n", temp);				// to print unique values
    printf("Collisions			-> %d\n", collisions);
    printf("Load				-> %.3f\n", ((double)temp / (double)TABLE_SIZE) );
}
*/

int main()	{
    
    struct person_record person;
	// initialize Hash Table
    table Table[TABLE_SIZE];
    for (int i=0; i<TABLE_SIZE; i++){
    strcpy(Table[i].surname, "");
    Table[i].head = NULL;
	}
	
	FILE *f;
	f = fopen("truncated.csv", "r");
	
	if(!f)	{ 
		printf("error 404: csv file not found\n"); 
		return EXIT_FAILURE; 
	}
	else
		printf("csv file loaded!\n"); 

    while (!feof(f)){
        get_Info(f, &person);
        collisions = collisions + update_table(&person, Table);
        totalPerson++;
        }


	/* print hash table
    for(int i=0; i<size; i++){
        printf("Surname: %s ", Table[i].surname);
        
        Person *ptr = Table[i].head;
        while(ptr != NULL){
            printf("Forename: %s ", ptr->name);
            ptr = ptr->next;
        }
        printf("\n");
    }
    }*/
    
    // check occupied cell
    int occupied = 0;
    for (int i=0; i<TABLE_SIZE; i++){
        if (Table[i].head != NULL)
            occupied++;
    }

	// print stats
    printf("\nCapacity	: %d\n", TABLE_SIZE);
    printf("Num Terms	: %d\n", totalPerson);
    printf("Occupied	: %d\n", occupied);
    printf("Collisions	: %d\n", collisions);
    printf("Load		: %.3f%%", ((float)occupied/(float)TABLE_SIZE) );
    
    search(Table);

    fclose(f);
    free_table(Table, TABLE_SIZE); // free allocated memory to Table
    return 0;
}
