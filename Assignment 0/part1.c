//	Pulkit Sharma
//	19323659
//	21/09/2019
// 	Assignment 0 of LAB1&2

#include<stdio.h>

int main() {
   
   char name[30];
   int age;

    scanf("%s", name);
    scanf("%d", &age);

    printf("Name >> %s\n", name);
    printf("Age >> %d\n", age);

    printf("Hello %s ,(%d)\n", name,age);

    return 0;
}