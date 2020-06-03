//
//  phase2.c
//  project1
//
//  Created by 易弘鹏 on 2019/3/5.
//  Copyright © 2019 易弘鹏. All rights reserved.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "phase2.h"

#define MAXLEN 100

//  rd, rs, rt
int isRType1(char* str){
    if(!strcmp(str, "add") || !strcmp(str, "addu") || !strcmp(str, "and") || !strcmp(str, "nor") ||
       !strcmp(str, "or") || !strcmp(str, "slt") || !strcmp(str, "sltu") || !strcmp(str, "sub") ||
       !strcmp(str, "subu") || !strcmp(str, "xor")){
        return 1;
    }
    return 0;
}

// rs, rt
int isRType2(char* str){
    if(!strcmp(str, "div") || !strcmp(str, "divu") || !strcmp(str, "mult") || !strcmp(str, "multu")){
        return 1;
    }
    return 0;
}

// rs
int isRType3(char* str){
    if(!strcmp(str, "jr") || !strcmp(str, "mthi") || !strcmp(str, "mtlo")){
        return 1;
    }
    return 0;
}

//rd
int isRType4(char* str){
    if(!strcmp(str, "mfhi") || !strcmp(str, "mflo")){
        return 1;
    }
    return 0;
}

// rd, rt, sa
int isRType5(char* str){
    if(!strcmp(str, "sll") || !strcmp(str, "srl")){
        return 1;
    }
    return 0;
}

// rt, rs, immediate
int isIType1(char* str){
    if(!strcmp(str, "addi") || !strcmp(str, "addiu") || !strcmp(str, "andi") || !strcmp(str, "ori") ||
       !strcmp(str, "slti") || !strcmp(str, "sltiu") || !strcmp(str, "xori")){
        return 1;
    }
    return 0;
}

// rs, rt, label
int isIType2(char* str){
    if(!strcmp(str, "beq") || !strcmp(str, "bne")){
        return 1;
    }
    return 0;
}

// rs, label
int isIType3(char* str){
    if(!strcmp(str, "bgez") || !strcmp(str, "bgtz") || !strcmp(str, "blez") || !strcmp(str, "bltz")){
        return 1;
    }
    return 0;
}

// rt, immediate(rs)
int isIType4(char* str){
    if(!strcmp(str, "lb") || !strcmp(str, "lbu") || !strcmp(str, "lw") || !strcmp(str, "sb") ||
       !strcmp(str, "sw")){
        return 1;
    }
    return 0;
}

// rt, immediate
int isIType5(char* str){
    if(!strcmp(str, "lui")){
        return 1;
    }
    return 0;
}

// label
int isJType(char* str){
    if(!strcmp(str, "j") || !strcmp(str, "jal")){
        return 1;
    }
    return 0;
}

int isInstruction(char* str){
    if ((isRType1(str) + isRType2(str) + isRType3(str) + isRType4(str) + isRType5(str) +
        isIType1(str) + isIType2(str) + isIType3(str) + isIType4(str) + isIType5(str) +
         isJType(str)) == 0){
        return 0;
    }
    return 1;
}

int isRegister(char* str){
    if(*str == '$'){
        return 1;
    }
    return 0;
}

// Change decimal to 5-bit binary in 2's complement form.
char* dec2bin5(char* decimal){
    int dec = atoi(decimal);
    int isNegative = 0;
    int alreadyFirst1 = 0;
    char* bin;
    static char binString[6];
    bin = binString;
    if (dec < 0){
        isNegative = 1;
        dec = -dec;
    }
    for (int i = 4; i >= 0; i--){
        bin[i] = dec % 2 + '0';
        dec = dec / 2;
    }
    bin[5] = '\0';
    
    // For negative number, change it to 2's complement.
    if (isNegative){
        for (int i = 4; i >= 0; i--){
            if (bin[i] == '1'){
                if (alreadyFirst1){
                    bin[i] = '0';
                }else{
                    alreadyFirst1 = 1;
                }
            }else{
                if (alreadyFirst1) bin[i] = '1';
            }
        }
    }
    return bin;
}

// Change decimal to 16-bit binary in 2's complement form.
char* dec2bin16(char* decimal){
    int dec = atoi(decimal);
    int isNegative = 0;
    int alreadyFirst1 = 0;
    char* bin;
    static char binString16[17];
    bin = binString16;
    if (dec < 0){
        isNegative = 1;
        dec = -dec;
    }
    for (int i = 15; i >= 0; i--){
        bin[i] = dec % 2 + '0';
        dec = dec / 2;
    }
    bin[16] = '\0';
    if (isNegative){
        for (int i = 15; i >= 0; i--){
            if (bin[i] == '1'){
                if (alreadyFirst1){
                    bin[i] = '0';
                }else{
                    alreadyFirst1 = 1;
                }
            }else{
                if (alreadyFirst1) bin[i] = '1';
            }
        }
    }
    return bin;
}

// Change decimal to 26-bit binary in 2's complement form.
char* dec2bin26(char* decimal){
    int dec = atoi(decimal);
    int isNegative = 0;
    int alreadyFirst1 = 0;
    char* bin;
    static char binString26[27];
    bin = binString26;
    if (dec < 0){
        isNegative = 1;
        dec = -dec;
    }
    for (int i = 25; i >= 0; i--){
        bin[i] = dec % 2 + '0';
        dec = dec / 2;
    }
    bin[26] = '\0';
    if (isNegative){
        for (int i = 25; i >= 0; i--){
            if (bin[i] == '1'){
                if (alreadyFirst1){
                    bin[i] = '0';
                }else{
                    alreadyFirst1 = 1;
                }
            }else{
                if (alreadyFirst1) bin[i] = '1';
            }
        }
    }
    return bin;
}

char* reg2bin5(char* reg){
    
    char* regNum;
    
    if(!strcmp(reg, "$zero")) {regNum = "00000";}
    else if(!strcmp(reg, "$at")) {regNum = "00001";}
    else if(!strcmp(reg, "$v0")) {regNum = "00010";}
    else if(!strcmp(reg, "$v1")) {regNum = "00011";}
    else if(!strcmp(reg, "$a0")) {regNum = "00100";}
    else if(!strcmp(reg, "$a1")) {regNum = "00101";}
    else if(!strcmp(reg, "$a2")) {regNum = "00110";}
    else if(!strcmp(reg, "$a3")) {regNum = "00111";}
    else if(!strcmp(reg, "$t0")) {regNum = "01000";}
    else if(!strcmp(reg, "$t1")) {regNum = "01001";}
    else if(!strcmp(reg, "$t2")) {regNum = "01010";}
    else if(!strcmp(reg, "$t3")) {regNum = "01011";}
    else if(!strcmp(reg, "$t4")) {regNum = "01100";}
    else if(!strcmp(reg, "$t5")) {regNum = "01101";}
    else if(!strcmp(reg, "$t6")) {regNum = "01110";}
    else if(!strcmp(reg, "$t7")) {regNum = "01111";}
    else if(!strcmp(reg, "$s0")) {regNum = "10000";}
    else if(!strcmp(reg, "$s1")) {regNum = "10001";}
    else if(!strcmp(reg, "$s2")) {regNum = "10010";}
    else if(!strcmp(reg, "$s3")) {regNum = "10011";}
    else if(!strcmp(reg, "$s4")) {regNum = "10100";}
    else if(!strcmp(reg, "$s5")) {regNum = "10101";}
    else if(!strcmp(reg, "$s6")) {regNum = "10110";}
    else if(!strcmp(reg, "$s7")) {regNum = "10111";}
    else if(!strcmp(reg, "$t8")) {regNum = "11000";}
    else if(!strcmp(reg, "$t9")) {regNum = "11001";}
    else if(!strcmp(reg, "$k0")) {regNum = "11010";}
    else if(!strcmp(reg, "$k1")) {regNum = "11011";}
    else if(!strcmp(reg, "$gp")) {regNum = "11100";}
    else if(!strcmp(reg, "$sp")) {regNum = "11101";}
    else if(!strcmp(reg, "$fp")) {regNum = "11110";}
    else {regNum = "11111";}
    
    return regNum;
}

labelTable phase2(char * filename, labelTable table){
    
    FILE* fp;
    FILE* output;
    
    char line[MAXLEN];
    char* abandoned = " :\t\n#,()";  // What we ignore in a line of instructions.
    char* Instruction[3];  // Container of the instruction we get.
    
    fp = fopen(filename, "r");
    output = fopen("output.txt", "w");
    
    while (!feof(fp)){
        fgets(line, MAXLEN, fp);

        // Check whether it is a blank line.
        char copy[100];
        char *tok = strtok(strcpy(copy, line), " \n\t\r");
        if (tok == NULL) continue;
        
        char* token = strtok(line, abandoned);
        if (!isInstruction(token)){
            token = strtok(NULL, abandoned);
        } // Here we have gotten instruction we will do.
        
        if (isRType1(token)){
            for (int i = 0; i < 3; i++){
                Instruction[i] = strtok(NULL, abandoned);
            }
            char* opcode = "000000";
            char* sa = "00000";
            char* function;
            if (!strcmp(token, "add")){function = "100000";}
            else if(!strcmp(token, "addu")){function = "100001";}
            else if(!strcmp(token, "and")){function = "100100";}
            else if(!strcmp(token, "nor")){function = "100111";}
            else if(!strcmp(token, "or")){function = "100101";}
            else if(!strcmp(token, "slt")){function = "101010";}
            else if(!strcmp(token, "sltu")){function = "101011";}
            else if(!strcmp(token, "sub")){function = "100010";}
            else if(!strcmp(token, "subu")){function = "100011";}
            else {function = "100110";}
            writeR(output, opcode, reg2bin5(Instruction[1]), reg2bin5(Instruction[2]), reg2bin5(Instruction[0]), sa, function);
        }
        
        else if (isRType2(token)){
            for (int i = 0; i < 2; i++){
                Instruction[i] = strtok(NULL, abandoned);
            }
            char* opcode = "000000";
            char* sa = "00000";
            char* rd = "00000";
            char* function;
            if (!strcmp(token, "div")){function = "011010";}
            else if(!strcmp(token, "divu")){function = "011011";}
            else if(!strcmp(token, "mult")){function = "011000";}
            else {function = "011001";}
            writeR(output, opcode, reg2bin5(Instruction[0]), reg2bin5(Instruction[1]), rd, sa, function);
        }
        
        else if (isRType3(token)){
            Instruction[0] = strtok(NULL, abandoned);
            char* opcode = "000000";
            char* sa = "00000";
            char* rt = "00000";
            char* rd = "00000";
            char* function;
            if (!strcmp(token, "jr")){function = "001000";}
            else if(!strcmp(token, "mthi")){function = "010001";}
            else {function = "010011";}
            writeR(output, opcode, reg2bin5(Instruction[0]), rt, rd, sa, function);
            
        }
        
        else if (isRType4(token)){
            Instruction[0] = strtok(NULL, abandoned);
            char* opcode = "000000";
            char* sa = "00000";
            char* rt = "00000";
            char* rs = "00000";
            char* function;
            if (!strcmp(token, "mfhi")){function = "010000";}
            else {function = "010010";}
            writeR(output, opcode, rs, rt, reg2bin5(Instruction[0]), sa, function);
        }

        else if (isRType5(token)){
            for (int i = 0; i < 3; i++){
                Instruction[i] = strtok(NULL, abandoned);
            }
            char* opcode = "000000";
            char* rs = "00000";
            char* function;
            if (!strcmp(token, "sll")){function = "000000";}
            else {function = "000010";}
            writeR(output, opcode, rs, reg2bin5(Instruction[1]), reg2bin5(Instruction[0]), dec2bin5(Instruction[2]), function);
        }

        else if (isIType1(token)){
            for (int i = 0; i < 3; i++){
                Instruction[i] = strtok(NULL, abandoned);
            }
            char* opcode;
            if (!strcmp(token, "addi")){opcode = "001000";}
            else if (!strcmp(token, "addiu")){opcode = "001001";}
            else if (!strcmp(token, "andi")){opcode = "001100";}
            else if (!strcmp(token, "ori")){opcode = "001101";}
            else if (!strcmp(token, "slti")){opcode = "001010";}
            else if (!strcmp(token, "sltiu")){opcode = "001011";}
            else {opcode = "001110";}
            writeI(output, opcode, reg2bin5(Instruction[1]), reg2bin5(Instruction[0]), dec2bin16(Instruction[2]));
        }

        else if (isIType2(token)){
            for (int i = 0; i < 3; i++){
                Instruction[i] = strtok(NULL, abandoned);
            }
            char* opcode;
            if (!strcmp(token, "beq")){opcode = "000100";}
            else {opcode = "000101";}
            writeI(output, opcode, reg2bin5(Instruction[0]), reg2bin5(Instruction[1]),
                   dec2bin16(getAddress(Instruction[2], table)));
        }

        else if (isIType3(token)){
            for (int i = 0; i < 2; i++){
                Instruction[i] = strtok(NULL, abandoned);
            }
            char* rt;
            char* opcode;
            if (!strcmp(token, "bgez")){rt = "00001"; opcode = "000001";}
            else if (!strcmp(token, "bgtz")){rt = "00000"; opcode = "000111";}
            else if (!strcmp(token, "blez")){rt = "00000"; opcode = "000110";}
            else {rt = "00000"; opcode = "000001";}
            writeI(output, opcode, reg2bin5(Instruction[0]), rt,
                   dec2bin16(getAddress(Instruction[1], table)));
        }

        else if (isIType4(token)){
            for (int i = 0; i < 3; i++){
                Instruction[i] = strtok(NULL, abandoned);
            }
            char* opcode;
            if (!strcmp(token, "lb")){opcode = "100000";}
            else if (!strcmp(token, "lbu")){opcode = "100100";}
            else if (!strcmp(token, "lw")){opcode = "100011";}
            else if (!strcmp(token, "sb")){opcode = "101000";}
            else {opcode = "101011";}
            writeI(output, opcode, reg2bin5(Instruction[2]), reg2bin5(Instruction[0]), dec2bin16(Instruction[1]));
        }

        else if (isIType5(token)){
            for (int i = 0; i < 2; i++){
                Instruction[i] = strtok(NULL, abandoned);
            }
            char* opcode = "001111";
            char* rs = "00000";
            writeI(output, opcode, rs, reg2bin5(Instruction[0]), dec2bin16(Instruction[1]));
        }

        else if (isJType(token)){
            Instruction[0] = strtok(NULL, abandoned);
        char* opcode;
        if (!strcmp(token, "j")){opcode = "000010";}
        else {opcode = "000011";}
        writeJ(output, opcode, dec2bin26(getAddress(Instruction[0], table)));
    }
    }
    
    fclose(fp);
    fclose(output);
    return table;
}

// Write R type of instruction into output file in the form of machine code.
void writeR(FILE* file, char* opcode, char* rs, char* rt, char* rd, char* sa, char* function){
    fprintf(file, "%s%s%s%s%s%s\n", opcode, rs, rt, rd, sa, function);
    }

// Write I type of instruction into output file in the form of machine code.
void writeI(FILE* file, char* opcode, char* rs, char* rt, char* immediate){
    fprintf(file, "%s%s%s%s\n", opcode, rs, rt, immediate);
}

// Write J type of instruction into output file in the form of machine code.
void writeJ(FILE* file, char* opcode, char* target){
    fprintf(file, "%s%s\n", opcode, target);
}
