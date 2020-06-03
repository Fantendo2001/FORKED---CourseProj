//
//  phase1.c
//  project1
//
//  Created by 易弘鹏 on 2019/3/5.
//  Copyright © 2019 易弘鹏. All rights reserved.
//

#include "phase1.h"
#include "labelTable.h"
#include <string.h>

#define MAXLEN 100
#define MAXTAGS 100

labelTable phase1(char* filename){
    
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Fail to open the file.");
    }
    
    labelTable chart;
    static labelInfo infoCollection[100];
    chart = infoCollection;
    
    static char line[MAXLEN];
    char label[MAXTAGS][MAXLEN];
    int numOfLine = 0;
    int numOfLabel = 0;

    // Read the input file.
    while (!feof(fp)){
        
        fgets(line, MAXLEN, fp);
        
        // Check whether is a blank line.
        char copy[100];
        char *tok = strtok(strcpy(copy, line), " \n\t\r");
        if (tok == NULL) continue;
        
        // Get the information of label and store it in labelTable.
        for (int i = 0; i < MAXLEN; i++){
            if (line[i] == ':'){
                for (int j = 0; j < i; j++){
                    label[numOfLabel][j] = line[j];
                }
                label[numOfLabel][i] = '\0';
                chart[numOfLabel].address = numOfLine;
                chart[numOfLabel].label = label[numOfLabel];
                numOfLabel ++;
                break;
            }
        }
        numOfLine ++;
    }
    
    fclose(fp);
    
    
    return chart;
}


    

