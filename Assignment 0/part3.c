//	Pulkit Sharma
//	19323659
//	21/09/2019
// 	Assignment 0 of LAB1&2
#include <stdio.h>

int next_field(FILE *csv, char *buffer, int max_length);

int main() {

    FILE *csvfile;
    csvfile = fopen("/Users/spulk/Desktop/pokemon.csv", "r");
    
	char storage[2000];     
    char *buffer = storage;
    int num = 0,new_entry = -1;        
    
    if(csvfile == NULL)
	{  
        printf("file not found");
    }
    
    while(feof(csvfile)!=1){
    	
        new_entry = next_field(csvfile, buffer, 2000);
        if(new_entry == 1)
		{        
            printf("%s \n\n", buffer);
            num++;
        }
        else if(new_entry == 0)
		{     
            printf("%s \n", buffer);
        }
    }

        puts("EOF reached");
        printf ("Total records %d\n", num);
        
    fclose(csvfile);
    return 0;
}



int next_field(FILE *csv, char *buffer, int max_length){
    char current = fgetc(csv);
    int i = 0,val;
    
    while(current != '\n' && current != EOF && current != ',' )
	{	
		buffer[i] = current;
        current = fgetc(csv);
        i++;	
	}
    
    if(current == '\n' || current == EOF)
	{   
        buffer[i] = '\0';
        val = 1;
    }
    else if(current == ',')
	{    
        buffer[i] = '\0';
        val = 0;
    }
    return val;

}
