//
//  labelTable.c
//  project1
//
//  Created by 易弘鹏 on 2019/3/5.
//  Copyright © 2019 易弘鹏. All rights reserved.
//
#include <string.h>
#include "labelTable.h"

#define MAXTAGS 100

char* getAddress(char* label, labelTable table){
    char static string[50];  // Container used to store the string of address.
    for (int i = 0; i < MAXTAGS; i++){
        if (table[i].label == NULL){
            break;
        }
        if (!strcmp(table[i].label, label)){
            int n = table[i].address;
            sprintf(string, "%d", n);
            }
        }
    return string;
}
