//
//  main.c
//  test
//
//  Created by 易弘鹏 on 2019/9/30.
//  Copyright © 2019 易弘鹏. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define SIZE 20

int main(int argc, char *argv[])
{
    
    // Initialize an array randomly
    srand((int)time(NULL));
    int arr[SIZE];
    for (int i = 0; i < SIZE; i ++) {
        arr[i] = rand() % 100;
    }
    
    // Print out the initial array
    printf("Initial array: \n");
    for (int i = 0; i < SIZE; i ++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
    
    clock_t begin_time = clock();   // start timing
    int temp;
    for (int k = 0; k < SIZE; k ++) {
        // odd
        for (int i = 0; i < SIZE; i = i + 2) {
            if (i != SIZE - 1 && arr[i] > arr[i+1]) {
                temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
            }
        }
        // even
        for (int i = 1; i < SIZE; i = i + 2){
            if (i != SIZE - 1 && arr[i] > arr[i+1]) {
                temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
            }
        }
    }
    clock_t end_time = clock();     // end timming
    
    // Print out the sorted array
    printf("Sorted array: \n");
    for (int i = 0; i < SIZE; i ++) {
        printf("%d\t", arr[i]);
    }
    
    // Report information
    printf("\n\nName: Hongpeng Yi\nStudent ID: 117020343\nAssignment 1, Odd-Even Transposition Sort, sequential implementation.\nRunTime is %lfs, with array size %d.\n", (double)(end_time-begin_time)/CLOCKS_PER_SEC, SIZE);
}
