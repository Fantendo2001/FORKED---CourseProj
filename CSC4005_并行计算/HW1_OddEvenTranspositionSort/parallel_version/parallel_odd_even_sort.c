//
//  odd_even_sort.c
//  test
//
//  Created by 易弘鹏 on 2019/10/6.
//  Copyright © 2019 易弘鹏. All rights reserved.
//
#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

# define SIZE 20

int main(int argc, char* argv[]) {
    
    /* Obtain number of tasks and task ID */
    MPI_Init(&argc, &argv);
    int taskid,     /* task ID - also used as seed number */
    numtasks,   /* number of tasks */
    len;        /* length of hostname (no. of chars) */
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    char hostname[MPI_MAX_PROCESSOR_NAME];
    MPI_Get_processor_name(hostname, &len);
//    printf("MPI task %2d has started on %s [total number of processors %d]\n",
//           taskid, hostname, numtasks);
    
    int subarray_size;
    if (SIZE % numtasks == 0){
        subarray_size = SIZE / numtasks;
    } else {
        subarray_size = SIZE / numtasks + 1;
    }
    int subarray[subarray_size];
    int array_size = subarray_size * numtasks;
    int array[array_size];
    
    clock_t begin_time;
    if (taskid == 0) {
        srand((int)time(NULL));
        // To let the initial array be ditributed evenly,
        // append some INT_MAX at the end of the array.
        for (int i = 0; i < array_size; i ++) {
            if (i < SIZE) {
                array[i] = rand() % 10000;
            } else {
                array[i] = INT_MAX;
            }
        }
        // print out the initial array
        printf("Initial array: \n");
        for (int i = 0; i < SIZE; i ++) {
            printf("%d\t", array[i]);
        }
        printf("\n");
        begin_time = clock();
    }
    
    
    // scatter the initial array to every subarray
    MPI_Scatter(array, subarray_size, MPI_INT, subarray, subarray_size, MPI_INT, 0, MPI_COMM_WORLD);
    
    // prepare buffers
    int left_recev_buff;
    int left_send_buff;
    int right_recev_buff;
    int right_send_buff;
    int temp;
    
    // start iteration
    for (int i = 0; i < SIZE; i ++) {
        
        // odd
        for (int j = 0; j < subarray_size; j = j + 2){
            if (j != subarray_size - 1 && subarray[j] > subarray[j+1]) {
                temp = subarray[j];
                subarray[j] = subarray[j+1];
                subarray[j+1] = temp;
            }
        }
        
        // even
        for (int j = 1; j < subarray_size; j = j + 2){
            if (j != subarray_size - 1 && subarray[j] > subarray[j+1]) {
                temp = subarray[j];
                subarray[j] = subarray[j+1];
                subarray[j+1] = temp;
            }
        }
        
        // fill the send buffers
        left_send_buff = subarray[0];
        right_send_buff = subarray[subarray_size-1];
        
        // send to the left subarray
        if (taskid != 0){
            int sl = MPI_Send(&left_send_buff, 1, MPI_INT, taskid - 1, i, MPI_COMM_WORLD);
        }
        
        // send to the right subarray
        if (taskid < numtasks - 1){
            int sr = MPI_Send(&right_send_buff, 1, MPI_INT, taskid + 1, i, MPI_COMM_WORLD);
        }
        
        MPI_Status status1;
        MPI_Status status2;
        
        // receive from the left subarray
        if (taskid != 0){
            int rl = MPI_Recv(&left_recev_buff, 1, MPI_INT, taskid - 1, i, MPI_COMM_WORLD, &status1);
            if (left_recev_buff > left_send_buff) subarray[0] = left_recev_buff;
        }
        
        // receive from the right subarray
        if (taskid < numtasks - 1){
            int rr = MPI_Recv(&right_recev_buff, 1, MPI_INT, taskid + 1, i, MPI_COMM_WORLD, &status2);
            if (right_recev_buff < right_send_buff) subarray[subarray_size-1] = right_recev_buff;
        }
    }
    
    MPI_Gather(subarray, subarray_size, MPI_INT, array, subarray_size, MPI_INT, 0, MPI_COMM_WORLD);
    if (taskid == 0){
        clock_t end_time = clock();
        printf("Sorted array:\n");
        for (int i = 0; i < SIZE; i ++) {
            printf("%d\t", array[i]);
        }
        printf("\n");
        printf("\nName: Hongpeng Yi\nStudent ID: 117020343\nAssignment 1, Odd-Even Transposition Sort, MPI implementation.\nRunTime is %lfs, with array size %d.\n", (double)(end_time-begin_time)/CLOCKS_PER_SEC, SIZE);
    }
    
    MPI_Finalize();
    
    return 0;
}
    
        

        
    
