#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Game{
    char Title[60],Platform[60];
    char Score[60],ReleaseYear[60];
}Game;

int next_field(FILE *csv, char *temp){
    int i=0;
    int count=0;
    char ch;
    do{
        ch = fgetc(csv);

        if(i==59){
            temp[i]=='\0';
            i = 0;

            while(ch!=','){
                ch = fgetc(csv);
            }
            return 1;
        }
        if(ch=='"'){
            count = 1 - count;
            ch = fgetc(csv);
        }
        if(ch==','){
            if(count){
                temp[i] = ch;
                i++;
            }
            else{
                temp[i] = '\0';
                i=0;
                return 1;
            }
        }
        else if(ch=='\n'){
            temp[i] = '\0';
            i=0;
            return 2;
        }
        else {
            temp[i] = ch;
            i++;
        }
    } while(ch!=EOF);
    return 0;
}


void fetchgame(struct Game *games, char *temp, int index){				
    int n = index;
    if (n == 0){
        strcpy(games->Title, temp);
        return;
    }
    else if (n == 1){
        strcpy(games->Platform, temp);
        return;
    }
    else if (n == 2){
        strcpy(games->Score, temp);
        return;
    }
    else if (n == 3){
        strcpy(games->ReleaseYear, temp);
        return;
    }
}

void swap(Game *check1, Game *check2){
    Game temp;
   
    strcpy(temp.Title, check1->Title);
    strcpy(temp.Platform, check1->Platform);
    strcpy(temp.Score, check1->Score);
    strcpy(temp.ReleaseYear, check1->ReleaseYear);
    strcpy(check1->Title, check2->Title);
    strcpy(check1->Platform, check2->Platform);
    strcpy(check1->Score, check2->Score);
    strcpy(check1->ReleaseYear, check2->ReleaseYear);
    strcpy(check2->Title, temp.Title);
    strcpy(check2->Platform, temp.Platform);
    strcpy(check2->Score, temp.Score);
    strcpy(check2->ReleaseYear, temp.ReleaseYear);
}

//Quick sort with first element as pivot
void quick_sort(Game *array, int first, int last){
    int left = first;
    int right = last;
    int pivot = first;
    int temp;
    
    
    if(first<last){
      while(left<right){
        
        while(atoi(array[left].Score) >= atoi(array[pivot].Score) && left<last){
            left++;
        }
        while(atoi(array[right].Score) < atoi(array[pivot].Score)){
            right--;
        }
        if(left<right){
            swap(&array[left], &array[right]);
        }
    }
    
    swap(&array[pivot], &array[right]);
    
    quick_sort(array,first,right-1);
    quick_sort(array,right+1,last);

   }
    else return;
}

void printlist(Game *list){
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("%-60s", "Title");
    printf("%-40s", "Platform");
    printf("%-20s", "Score");
    printf("%-25s\n", "Release Year");


    int counter = 0;
    int i=0;
    char prevname[60];

    while (counter != 10){
        if(strcmp(prevname, list[i].Title)){
            printf("%-60s", list[i].Title);
            printf("%-40s", list[i].Platform);
            printf("%-20s", list[i].Score);
            printf("%-25s\n", list[i].ReleaseYear);
            counter++;
        }
        strcpy(prevname, list[i].Title);
        i++;
    }
    printf("-----------------------------------------------------------------------------------------------------\n");
}

int main(){
    char temp[60];
    FILE *csvFile;
    csvFile = fopen("ign.csv", "r");
    int length;
    length = 18626;

    Game *IGNGames;
    IGNGames = calloc(length, sizeof(Game));

    //Rewind the file 
    rewind(csvFile);

    //Status variable indicates , \n or EOF
    int status = 1;
    int j = 0;
    int index=0;
    while(status && j<length){

        //Comma encountered
        if(status == 1){
            fetchgame(&IGNGames[j], temp, index);
            index++;
        }
        //Endline Encountered
        else if (status == 2){
            fetchgame(&IGNGames[j], temp, index);
            index = 0;
            j++;
        }
        status = next_field(csvFile, temp);
    }
    //Close the file
    fclose(csvFile); 
    //Sort the games by score
    quick_sort(IGNGames, 0, length-1);
    //Print the top 10 games
    printlist(IGNGames);
}
