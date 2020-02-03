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
    count++;
}

void quickSort(int *array, int first, int last){

    int temp;
    int left = first;
    int right = last;
    int pivot = first;

   if(first<last){
      while(left<right){
        while(array[left]<=array[pivot] && left<last && comparisons++){				//left index to the right if value is less than the pivot
            left++;
        }
    
        while(array[right]>array[pivot] && comparisons++){							//right index to the left if value is greater than the pivot
            right--;
        }
        
        if(left<right && array[right] != array[left]){								//swap
            swap(array, left, right);
        }
    }
    
    if(array[right] != array[pivot]){												//swap the pivot
        swap(array, pivot, right);
    }
    quickSort(array,first,right-1);
    quickSort(array,right+1,last);

   }
    else return;
}
/*
void print(int array[]){

    printf("\n");
    for(int k = 0; k < SIZE; k++){
        printf("%d", array[k]);
        printf(" ");
    }
    printf("\n");

}
*/
int check_unique(int array[], int temp, int total){
    for(int i =0; i < total; i++){
        if(array[i] == temp){
            return 0;
        }
    }
    return 1;
}

char check_sorted(int array[]){
	int len=sizeof(array)/sizeof(int);
    for(int i = 0; i < (len); i++){
        if(array[i+1] < array[i]){
            return 'N';
        }
    }
    return 'Y';
}


int main (){

    int sample[] = {16,87,68,8,90,28,13,74,37,29};
    int unique_arr[SIZE];
    int random_arr[SIZE];
    int asc_arr[SIZE];
    int dsc_arr[SIZE];
    int dup_arr[SIZE];
    int random,num;
    int left = 0;
    int right = (SIZE-1);

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
    quickSort(sample, left, 9);
    printf("--------------------------------------------------\n");
    printf("\nTEST  : Sample of 10 Values\n");
    printf("SORTED: %c\n", check_sorted(sample));
    printf("SWAPS : %d\n", count);
    printf("COMPS : %d\n", comparisons);
    printf("---------------------------------------------------\n");
    
    count = 0;
    comparisons = 0;
    quickSort(unique_arr, left, right);
    printf("\nTEST  : Unique random 10000 values\n");
    printf("SORTED: %c\n", check_sorted(unique_arr));
    printf("SWAPS : %d\n", count);
    printf("COMPS : %d\n", comparisons);
	printf("----------------------------------------------------\n");
    
	count = 0;
    comparisons = 0;
    quickSort(random_arr, left, right);
    printf("\nTEST  : Random 10000 values\n");
    printf("SORTED: %c\n", check_sorted(random_arr));
    printf("SWAPS : %d\n", count);
    printf("COMPS : %d\n", comparisons);
	printf("----------------------------------------------------\n");
    
	count = 0;
    comparisons = 0;
    quickSort(asc_arr, left, right);
    printf("\nTEST  : Ascending sorted list of 10000 values\n");
    printf("SORTED: %c\n", check_sorted(asc_arr));
    printf("SWAPS : %d\n", count);
    printf("COMPS : %d\n", comparisons);
	printf("----------------------------------------------------\n");
	
    count = 0;
    comparisons = 0;
    quickSort(dsc_arr, left, right);
    printf("\nTEST  : Descending sorted list of 10000 values\n");
    printf("SORTED: %c\n", check_sorted(dsc_arr));
    printf("SWAPS : %d\n", count);
    printf("COMPS : %d\n", comparisons);
    printf("----------------------------------------------------\n");

    count = 0;
    comparisons = 0;
    quickSort(dup_arr, left, right);
    printf("\nTEST  : Uniform list of 10000 values\n");
    printf("SORTED: %c\n", check_sorted(dup_arr));
    printf("SWAPS : %d\n", count);
    printf("COMPS : %d\n", comparisons);
    printf("----------------------------------------------------\n");

}






