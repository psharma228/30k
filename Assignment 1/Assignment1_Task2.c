#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int TABLE_SIZE  = 100;
int MAX_BUFFER = 60;

typedef struct list
{
    char name[50];
    int frequency;
}list;

int hash2(char *s){
  int hash = 0;
    int count =1;
    int n;
    while (*s) {
        hash = (((hash + *s) * count))% TABLE_SIZE ;
        s++;
        count*=3;
    } 
    return hash;
}

void initalize_table(list *hash_table)
{
    for (int i=0; i<TABLE_SIZE; i++)
	{
	strcpy(hash_table[i].name, "");
   	hash_table[i].frequency = 0;
    }
    
}

int update_table(char *s, list *hash_table)											 		// To find number of collisions
{    
    int collisions = 0;
    int index = hash2(s);

    if (hash_table[index].frequency == 0)
	{     																					 // Check cell is either empty or is the same name 
    strcpy(hash_table[index].name, s);	
    hash_table[index].frequency+= 1; 														// update frequency by 1
    }
    else if (strcmp(hash_table[index].name, s) == 0 )
    	hash_table[index].frequency += 1;
    else 
	{ 																				 	    // if collision occurs 
       while ( hash_table[index].frequency != 0 )	
	   { 																					//find new cell
          if(strcmp(hash_table[index].name, s) == 0 )	
          	break;																			//if it reaches max value
          if (index >= (TABLE_SIZE-1))
       	    index = 0;
          else index++;
     	}
        collisions++;
        strcpy(hash_table[index].name, s);
        hash_table[index].frequency +=1;													 // update frequency by 1
    }
    return collisions;
}


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

/*
void printHashTable(list *hash_table, int size){
    for(int i=0; i<size; i++){
        printf("[%d] %s %d \n", i, hash_table[i].name, hash_table[i].frequency);
    }
}
*/

void search(list *hash_table) {
    char input[MAX_BUFFER];
    int index;
    
    printf("\nEnter name to check frequency or 'quit' to exit \n");
    while (1) {
        gets(input);
        if (strcmp(input, "quit") == 0)
            break;
        index = hash2(input);
        if (hash_table[index].frequency != 0)
            if (strcmp(hash_table[index].name, input) == 0)
                printf(":: %s %d\n", hash_table[index].name, hash_table[index].frequency);
            else{ 
                while(strcmp(hash_table[index].name,input) != 0) {
                    if (hash_table[index].frequency == 0)
                        break;
                    if (index >= (TABLE_SIZE-1))
                        index = 0;
                    else
                        index++;
                }
                printf(":: %s %d\n", hash_table[index].name, hash_table[index].frequency);
            }
        else
            printf("%s is not in the hash table\n", input);
    }
}

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


int main() {
    FILE *f;
    char input[MAX_BUFFER];
    char buffer[MAX_BUFFER];
    int return_val;
    int collisions = 0, terms=0, index=0;
    list hash_table[TABLE_SIZE];

    initalize_table(hash_table);

    f = fopen("names.csv", "r");
    if (f) {
    	printf("CSV loaded....!!!!\n");
        while (!feof(f))
		{
           	return_val = next_field(f, buffer, MAX_BUFFER);
           if (return_val == 1){
             collisions = collisions + update_table(buffer, hash_table);
             terms++;
            }
        }
    }
    else
        printf("Error File not found\n");
	
    print_stats(hash_table, TABLE_SIZE, collisions, terms);
   // printHashTable(hash_table, MAX_BUFFER);
    search(hash_table);
    fclose(f);
    return 0;
    
}
