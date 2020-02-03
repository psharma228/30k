#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10000

int count = 0;
int comparisons = 0;

void swap(int arr[],int a,int b){
    int temp = arr[a]; 
    arr[a] = arr[b]; 
    arr[b] = temp; 
}

void insertionSort(int arr[]){

    for(int i=0; i<SIZE-1;i++){
        for(int j = i+1; j>0;j--){
            comparisons++; 
            if(arr[j-1] > arr[j] ){
                swap(arr,j,j-1);
                count++; 
            } else {
                break; 
            }
        }
    }
}
void print(int array[]){

    printf("\n");
    for(int k = 0; k < SIZE; k++){
        printf("%d", array[k]);
        printf(" ");
    }
    printf("\n");

}

int check_unique(int array[], int temp, int total){
    for(int i =0; i < total; i++){
        if(array[i] == temp){
            return 0;
        }
    }
    return 1;
}

char check_sorted(int array[]){

    for(int i = 0; i < (SIZE-1); i++){
        if(array[i+1] < array[i]){
            return 'N';
        }
    }
    return 'Y';

}

int main (){

    int sample[SIZE] = {16,87,68,8,90,28,13,74,37,29};
    int unique_arr[SIZE];
    int random_arr[SIZE];
    int asc_arr[SIZE];
    int dsc_arr[SIZE];
    int dup_arr[SIZE];
    int random,num;

    for(int i =0; i <SIZE; i++){										//Initalize Unique Array with 10000 values
        random = rand();
        while(check_unique(unique_arr, random, i) == 0){
            random = rand();
        }
        unique_arr[i] = rand();
    }

    for(int i =0; i <SIZE; i++){										//Initalize Random Array with 10000 values
        random_arr[i] = rand();
    }

    for(int i =0; i <SIZE; i++){										//Initalize Ascending Array with 10000 values
        asc_arr[i] = (i + 1);
    }

    num = SIZE;
    for(int i =0; i <SIZE; i++){										//Initalize Descending Array with 10000 values
        dsc_arr[i] = num;
        num--;
    }

    for(int i =0; i <SIZE; i++){										//Initalize Duplicate Array with 10000 values
        dup_arr[i] = 3;
    }

	count = 0;
    comparisons = 0;
    insertionSort(sample);
    printf("--------------------------------------------------\n");
    printf("\nTEST  : Sample of 10 Values\n");
    printf("SORTED: %c\n", check_sorted(sample));
    printf("SWAPS : %d\n", count);
    printf("COMPS : %d\n", comparisons);
    printf("---------------------------------------------------\n");
    
    count = 0;
    comparisons = 0;
    insertionSort(unique_arr);
    printf("\nTEST  : Unique random values\n");
    printf("SORTED: %c\n", check_sorted(unique_arr));
    printf("SWAPS : %d\n", count);
    printf("COMPS : %d\n", comparisons);
	printf("----------------------------------------------------\n");
    
	count = 0;
    comparisons = 0;
    insertionSort(random_arr);
    printf("\nTEST  : Random values\n");
    printf("SORTED: %c\n", check_sorted(random_arr));
    printf("SWAPS : %d\n", count);
    printf("COMPS : %d\n", comparisons);
	printf("----------------------------------------------------\n");
    
	count = 0;
    comparisons = 0;
    insertionSort(asc_arr);
    printf("\nTEST  : Ascending sorted list\n");
    printf("SORTED: %c\n", check_sorted(asc_arr));
    printf("SWAPS : %d\n", count);
    printf("COMPS : %d\n", comparisons);
	printf("----------------------------------------------------\n");
	
    count = 0;
    comparisons = 0;
    insertionSort(dsc_arr);
    printf("\nTEST  : Descending sorted list\n");
    printf("SORTED: %c\n", check_sorted(dsc_arr));
    printf("SWAPS : %d\n", count);
    printf("COMPS : %d\n", comparisons);
    printf("----------------------------------------------------\n");

    count = 0;
    comparisons = 0;
    insertionSort(dup_arr);
    printf("\nTEST  : Uniform list\n");
    printf("SORTED: %c\n", check_sorted(dup_arr));
    printf("SWAPS : %d\n", count);
    printf("COMPS : %d\n", comparisons);
    printf("----------------------------------------------------\n");

}
