//
//  main.c
//  project1
//
//  Created by 易弘鹏 on 2019/3/4.
//  Copyright © 2019 易弘鹏. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "labelTable.h"

labelTable phase1 (char * filename);
labelTable phase2 (char * filename, labelTable table);


int compare_files(FILE* fp1, FILE* fp2)
{
    char char1 = fgetc(fp1);
    char char2 = fgetc(fp2);

    while(char1 != EOF && char2 != EOF){
        if(char1 != char2){
            return -1;
        }
        char1 = fgetc(fp1);
        char2 = fgetc(fp2);
    }
    while(char1 != EOF && (char1 == ' ' || char1 == '\n') ){
        char1 = fgetc(fp1);
    }
    while(char2 != EOF && (char2 == ' ' || char2 == '\n')){
        char2 = fgetc(fp2);
    }
    if(char1 == EOF && char2 == EOF){
        return 0;
    }
    return -1;
}
int main (int argc, char * argv[])
{
    if(argc < 4)
    {
        printf("Please enter an input file, an output file, and expected output file \n");
    }
    labelTable table;
    table = phase1 (argv[1]);
    (void)phase2(argv[1], table);

    FILE* fp1;
    FILE* fp2;
    fp1 = fopen(argv[3], "r");
    fp2 = fopen(argv[2], "r");

    if(fp1 == NULL || fp2 == NULL){
        printf("Error: Files are not open correctly \n");
    }

    int res = compare_files(fp1, fp2);

    if(res == 0){
        printf("ALL PASSED! CONGRATS :) \n");
    }else{
        printf("YOU DID SOMETHING WRONG :( \n");
    }

    fclose(fp1);
    fclose(fp2);

    return 0;
}
