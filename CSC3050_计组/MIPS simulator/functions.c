//
//  functions.c
//  project2
//
//  Created by 易弘鹏 on 2019/3/17.
//  Copyright © 2019 易弘鹏. All rights reserved.
//

#include "functions.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>


extern char** registers;
extern char* currentLine;       // using global variable
extern FILE* fp;



// ----------- run the instruction read in currentLine -----------
void run(void){
    
    char* opcode = (char*)malloc(6 * sizeof(char));     // Using opcode to identify the instruction
    if (opcode == NULL){
        printf("Fail to allocate memory. Try again!");
    }
    strncpy(opcode, currentLine, 6);
    
    
// --------------- R type instructions ---------------
    if (!strcmp(opcode, "000000")){
        
        // allocate memory to store the value of rs, rt, rd, sa, function
        char* rs = (char*)malloc(5 * sizeof(char));
        char* rt = (char*)malloc(5 * sizeof(char));
        char* rd = (char*)malloc(5 * sizeof(char));
        char* sa = (char*)malloc(5 * sizeof(char));
        char* function = (char*)malloc(6 * sizeof(char));
        if (rs == NULL || rt == NULL || rd == NULL || sa == NULL || function == NULL){
            printf("Fail to allocate memory. Try again!");
        }
        
        // copy the code of rs, rt, rd, sa and function from the currentLine
        strncpy(rs, currentLine + 6, 5);
        strncpy(rt, currentLine + 11, 5);
        strncpy(rd, currentLine + 16, 5);
        strncpy(sa, currentLine + 21, 5);
        strncpy(function, currentLine + 26, 6);
        
        // Identify the particular instruction and call the corresponding function to simulate execution
        if (!strcmp(function, "100000")) {add(bin2dec5(rd), bin2dec5(rs), bin2dec5(rt));}
        else if (!strcmp(function, "100001")) {addu(bin2dec5(rd), bin2dec5(rs), bin2dec5(rt));}
        else if (!strcmp(function, "001000")) {jr(bin2dec5(rs));}
        else if (!strcmp(function, "000000")) {sll(bin2dec5(rd), bin2dec5(rt), bin2dec5(sa));}
        else if (!strcmp(function, "101010")) {slt(bin2dec5(rd), bin2dec5(rs), bin2dec5(rt));}
        else if (!strcmp(function, "101011")) {sltu(bin2dec5(rd), bin2dec5(rs), bin2dec5(rt));}
        else if (!strcmp(function, "000010")) {srl(bin2dec5(rd), bin2dec5(rt), bin2dec5(sa));}
        else if (!strcmp(function, "100010")) {sub(bin2dec5(rd), bin2dec5(rs), bin2dec5(rt));}
        else if (!strcmp(function, "001100")) {systemCall();}
        
        free(rs);
        free(rt);
        free(rd);
        free(sa);
        free(function);
        
        
// ---------------- J type instructions ---------------
    }else if (!strcmp(opcode, "000010") || !strcmp(opcode, "000011")){

        char* target = (char*)malloc(26 * sizeof(char));
        strncpy(target, currentLine + 6, 26);
        if (!strcmp(opcode, "000010")) {j(bin2dec26(target));}
        else {jal(bin2dec26(target));}

        free(target);
        
        
// --------------- I type instructions ---------------
    }else{
        
        char* rs = (char*)malloc(5 * sizeof(char));
        char* rt = (char*)malloc(5 * sizeof(char));
        char* immediate = (char*)malloc(16 * sizeof(char));
        if (rs == NULL || rt == NULL || immediate == NULL){
            printf("Fail to allocate memory. Try again!");
        }
        
        strncpy(rs, currentLine + 6, 5);        // copy the rs from the line
        strncpy(rt, currentLine + 11, 5);
        strncpy(immediate, currentLine + 16, 16);
        
        if (!strcmp(opcode, "001000")) {addi(bin2dec5(rt), bin2dec5(rs), bin2dec16(immediate));}
        else if (!strcmp(opcode, "001001")) {addiu(bin2dec5(rt), bin2dec5(rs), bin2dec16(immediate));}
        else if (!strcmp(opcode, "000100")) {beq(bin2dec5(rs), bin2dec5(rt), bin2dec16(immediate));}
        else if (!strcmp(opcode, "000001")) {
            if (!strcmp(rt, "00001")) {bgez(bin2dec5(rs), bin2dec16(immediate));}
            else {bltz(bin2dec5(rs), bin2dec16(immediate));}
        }
        else if (!strcmp(opcode, "000111")) {bgtz(bin2dec5(rs), bin2dec16(immediate));}
        else if (!strcmp(opcode, "000110")) {blez(bin2dec5(rs), bin2dec16(immediate));}
        else if (!strcmp(opcode, "000101")) {bne(bin2dec5(rs), bin2dec5(rt), bin2dec16(immediate));}
        else if (!strcmp(opcode, "001010")) {slti(bin2dec5(rt), bin2dec5(rs), bin2dec16(immediate));}
        else if (!strcmp(opcode, "001011")) {sltiu(bin2dec5(rt), bin2dec5(rs), bin2dec16(immediate));}
        else if (!strcmp(opcode, "100011")) {lw((bin2dec5(rt)), bin2dec16(immediate), bin2dec5(rs));}
        else if (!strcmp(opcode, "101011")) {sw((bin2dec5(rt)), bin2dec16(immediate), bin2dec5(rs));}
        
        free(rs);
        free(rt);
        free(immediate);
    }
    
    free(opcode);
    
}



/* --------------------------------
    R type function implementation.
   -------------------------------- */

void add(int rd, int rs, int rt){
    if (rt == 0){           // In the case using $zero, it just copy the value of register[rs] to register[rd]
        sprintf(registers[rd], "%s", registers[rs]);
    }else{
        int sum = atoi(registers[rs]) + atoi(registers[rt]);    // compute the result of addition
        sprintf(registers[rd], "%d", sum);      // copy the result into register as a string
    }
}


void addu(int rd, int rs, int rt){
    if (rt == 0){           // In the case using $zero, it just copy the value of register[rs] to register[rd]
        sprintf(registers[rd], "%s", registers[rs]);
    }else{
        int sum = atoi(registers[rs]) + atoi(registers[rt]);    // compute the result of addition
        sprintf(registers[rd], "%d", sum);      // copy the result into register as a string
    }
}


void sll(int rd, int rt, int sa){
    int result = atoi(registers[rt]) * pow(2, sa);
    sprintf(registers[rd], "%d", result);
}


void slt(int rd, int rs, int rt){
    if (atoi(registers[rs]) < atoi(registers[rt])){
        sprintf(registers[rd], "%d", 1);
    }else{
        sprintf(registers[rd], "%d", 0);
    }
}


void sltu(int rd, int rs, int rt){
    if (atoi(registers[rs]) < atoi(registers[rt])){
        sprintf(registers[rd], "%d", 1);
    }else{
        sprintf(registers[rd], "%d", 0);
    }
}


void srl(int rd, int rt, int sa){
    int result = atoi(registers[rt]) / pow(2, sa);
    sprintf(registers[rd], "%d", result);
}


void sub(int rd, int rs, int rt){
    if (rt == 0){           // In the case using $zero, it just copy the value of register[rs] to register[rd]
        sprintf(registers[rd], "%s", registers[rs]);
    }else{
        int difference = atoi(registers[rs]) - atoi(registers[rt]);
        sprintf(registers[rd], "%d", difference);
    }
}


void jr(int rs){
    int nextLinePosition = atoi(registers[31]);     // Get the position stored in $ra for fp
    fseek(fp, nextLinePosition, SEEK_SET);      // Go to the position of the next line of function call
}


void systemCall(void){
    
    int v0 = atoi(registers[2]);    // Get the value of $v0
    
    if (v0 == 1){
        printf("%d\n", atoi(registers[4]));
    }
    
    else if (v0 == 4){
        char* ptr;      // prepare for the strtol of the next line
        long addr = strtol(registers[4], &ptr, 16);      // extract the hexadecimal from the register
        char* p = (char*)addr;    // Convert the hexadecimal back to the pointer towards  the memory.
        printf("%s\n", p);
    }
    
    else if (v0 == 5){
        scanf("%s", registers[2]);  // read a integer and save it in $v0
    }
    
    else if (v0 == 8){
        char* ptr;      // prepare for the strtol of the next line
        long addr = strtol(registers[4], &ptr, 16);      // extract the hexadecimal from the register
        char* p = (char*)addr;    // Convert the hexadecimal back to the pointer towards  the memory.
        char buffer[20];    // buffer to store the user-input data
        scanf("%s", buffer);
        strncpy(p, buffer, atoi(registers[5]) - 1); // read a given number(a1) of char
    }
    
    else if (v0 == 9){
        char* memory = (char*)malloc(atoi(registers[4]) * sizeof(char));//Allocate a memory with $a0 bytes.
        sprintf(registers[2], "%p", memory);  // Store the pointer towards the memory in $v0
    }
    
    else if (v0 == 10){
        exit(0);    // terminate the running
    }
    
    else if (v0 == 11){
        printf("%c\n", registers[4][0]);    // print char in $a0
    }
    
    else if (v0 == 12){
        scanf("%c", registers[2]);  // read char and save it in $v0
    }
}


// Functions that havn't been supported yet.
void andR(int rd, int rs, int rt);
void divR(int rs, int rt);
void divu(int rs, int rt);
void mfhi(int rd);
void mflo(int rd);
void mthi(int rs);
void mtlo(int rs);
void mult(int rs, int rt);
void multu(int rs, int rt);
void nor(int rd, int rs, int rt);
void orR(int rd, int rs, int rt);
void subu(int rd, int rs, int rt);
void xorR(int rd, int rs, int rt);




/* --------------------------------
    I type function implementation.
   -------------------------------- */

void addi(int rt, int rs, int immediate){
    if (isalpha(registers[rs][0])){         // identify what kind of data is in the register
        int sum = (int)registers[rs][0] + immediate;  // do charcter addition when it is char in register
        sprintf(registers[rt], "%c", sum);
    }else{
        int sum = atoi(registers[rs]) + immediate; // do numeirical addition if it is int in register
        sprintf(registers[rt], "%d", sum);
    }
}


void addiu(int rt, int rs, int immediate){
    if (isalpha(registers[rs][0])){         // identify what kind of data is in the register
        int sum = (int)registers[rs][0] + immediate;  // do charcter addition when it is char in register
        sprintf(registers[rt], "%c", sum);
    }else{
        int sum = atoi(registers[rs]) + immediate; // do numeirical addition if it is int in register
        sprintf(registers[rt], "%d", sum);
    }
}


void beq(int rs, int rt, int label){
    if (atoi(registers[rs]) == atoi(registers[rt])){
        fseek(fp, 33 * label, SEEK_SET);    // Set the file pointer on target line.
    }
}


void bgez(int rs, int label){
    if (atoi(registers[rs]) >= 0){
        fseek(fp, 33 * label, SEEK_SET);    // Set the file pointer on target line.
    }
}


void bgtz(int rs, int label){
    if (atoi(registers[rs]) > 0){
        fseek(fp, 33 * label, SEEK_SET);    // Set the file pointer on target line.
    }
}


void blez(int rs, int label){
    if (atoi(registers[rs]) <= 0){
        fseek(fp, 33 * label, SEEK_SET);    // Set the file pointer on target line.
    }
}


void bltz(int rs, int label){
    if (atoi(registers[rs]) < 0){
        fseek(fp, 33 * label, SEEK_SET);    // Set the file pointer on target line.
    }
}


void bne(int rs, int rt, int label){
    if (atoi(registers[rs]) != atoi(registers[rt])){
        fseek(fp, 33 * label, SEEK_SET);    // Set the file pointer on target line.
    }
}


void lw(int rt, int immediate, int rs){
    char* ptr;      // prepare for the strtol of the next line
    long addr = strtol(registers[rs], &ptr, 16);      // extract the hexadecimal from the register
    char* p = (char*)addr;    // Convert the hexadecimal back to the pointer towards  the memory.
    strcpy(registers[rt], p);
}


void slti(int rt, int rs, int immediate){
    if (atoi(registers[rs]) < immediate){
        sprintf(registers[rt], "%d", 1);
    }else{
        sprintf(registers[rt], "%d", 0);
    }
}


void sltiu(int rt, int rs, int immediate){
    if (atoi(registers[rs]) < immediate){
        sprintf(registers[rt], "%d", 1);
    }else{
        sprintf(registers[rt], "%d", 0);
    }
}


void sw(int rt, int immediate, int rs){
    char* ptr;      // prepare for the strtol of the next line
    long addr = strtol(registers[rs], &ptr, 16);      // extract the hexadecimal from the register
    char* p = (char*)addr;    // Convert the hexadecimal back to the pointer towards  the memory.
    strcpy(p, registers[rt]);
}


// Functions that havn't been supported yet.
void andi(int rt, int rs, int immediate);
void lb(int rt, int immediate, int rs);
void lbu(int rt, int immediate, int rs);
void lui(int rt, int immediate);
void ori(int rt, int rs, int immediate);
void sb(int rt, int immediate, int rs);
void xori(int rt, int rs, int immediate);




/* --------------------------------
    J type function implementation.
   -------------------------------- */

void j(int target){
    fseek(fp, 33 * target, SEEK_SET);   // Go to the target line.
}


void jal(int target){
    int nextLinePosition = (int)ftell(fp);      // Get the current position of file pointer
    sprintf(registers[31], "%d", nextLinePosition);     // Save the position in $sa
    j(target);      // Go to the target line.
}



/* --------------------------------
    Binary to decimal implementation.
   -------------------------------- */

int bin2dec5(char* bin){
    int dec = 0;
    for (int i = 0; i < 5; i ++){   // Add up the value(decimal) digit by digit from right to left
        if (bin[4 - i] == '1'){
            dec += pow(2, i);
        }
    }
    return dec;
}


int bin2dec16(char* bin){
    int dec = 0;
    for (int i = 0; i < 15; i ++){
        if (bin[15 - i] == '1'){
            dec += pow(2, i);
        }
    }
    if (bin[0] == '1'){
        dec -= pow(2, 15);
    }
    return dec;
}


int bin2dec26(char* bin){
    int dec = 0;
    for (int i = 0; i < 25; i ++){
        if (bin[25 - i] == '1'){
            dec += pow(2, i);
        }
    }
    if (bin[0] == '1'){
        dec -= pow(2, 25);
    }
    return dec;
}

