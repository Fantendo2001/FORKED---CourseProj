//
//  main.c
//  project2
//
//  Created by 易弘鹏 on 2019/3/14.
//  Copyright © 2019 易弘鹏. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <string.h>

char* currentLine; // container to store code and '\n'
char** registers; // container of registers
char* registerHI;
char* registerLO;
FILE* fp;

int main(int argc, const char * argv[]) {

    fp = fopen(argv[1],"r");

// Container to store code and '\n'
    currentLine = (char*)malloc(33 * sizeof(char));
// Container of registers, so that register[x] can represent the register with register number x.
    registers = (char**)malloc(32 * sizeof(char*));
// Container of HI, LO register,
    registerHI = (char*)malloc(32 * sizeof(char));
    registerLO = (char*)malloc(32 * sizeof(char));
    
// Check whether the allocation is successful.
    if (currentLine == NULL || registers == NULL || registerHI == NULL || registerLO == NULL){
        printf("Fail to allocate memory. Try again!");
    }
    
// Allocate memory for every register.
    for (int i = 0; i < 32; i ++){
        registers[i] = (char*)malloc(32 * sizeof(char)); // every register has 4 byte data
    }
    strcpy(registers[0], "0");       // initialize the value of $zero

// Continue reading line by line and run the instrucions for every line.
    while (!feof(fp)){
        fgets(currentLine, 34, fp); // Read to the end of the line(include '\n')
        run();
    }

    
    free(currentLine);
    free(registers);
    free(registerHI);
    free(registerLO);
    
    fclose(fp);
    
    return 0;
    
}

