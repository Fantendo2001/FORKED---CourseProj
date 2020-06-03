//
//  labelTable.h
//  project1
//
//  Created by 易弘鹏 on 2019/3/5.
//  Copyright © 2019 易弘鹏. All rights reserved.
//

#ifndef labelTable_h
#define labelTable_h

#include <stdio.h>

// The container of a single info of tags.
typedef struct labelInformation
{
    char *label;
    int address;
    
}labelInfo;

// The container of all tag information.
typedef labelInfo *labelTable;

// Get the char* type of address of the label inputed through labelTable.
char* getAddress(char* label, labelTable table);


#endif /* labelTable_h */
