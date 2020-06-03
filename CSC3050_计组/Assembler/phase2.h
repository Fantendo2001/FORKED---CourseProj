//
//  phase2.h
//  project1
//
//  Created by 易弘鹏 on 2019/3/5.
//  Copyright © 2019 易弘鹏. All rights reserved.
//

#ifndef phase2_h
#define phase2_h

#include <stdio.h>
#include "labelTable.h"
#include "phase1.h"

labelTable phase2 (char * filename, labelTable table);

// According to the different type and format of instruction,
// we divided into 11 types in total.
// THe function bellow is used to identify the type of instruction.
int isRType1(char* str);
int isRType2(char* str);
int isRType3(char* str);
int isRType4(char* str);
int isRType5(char* str);

int isIType1(char* str);
int isIType2(char* str);
int isIType3(char* str);
int isIType4(char* str);
int isIType5(char* str);

int isJType(char* str);

// To grab the key word of instruction like 'add', 'sw', etc.
int isInstruction(char* str);

// Convert decimal into binary with different number of bits,
// used for interprete things like label or immediate into binary.
char* dec2bin5(char* decimal);
char* dec2bin16(char* decimal);
char* dec2bin26(char* decimal);

// Convert register symbol into binary code.
char* reg2bin5(char* reg);

// Write 3 types of instruction into output file in the form of machine code.
void writeR(FILE* file, char* opcode, char*rs, char* rt, char* rd, char* sa, char* function);
void writeI(FILE* file, char* opcode, char* rs, char* rt, char* immediate);
void writeJ(FILE* file, char* opcode, char* target);

#endif /* phase2_h */
