//
//  functions.h
//  project2
//
//  Created by 易弘鹏 on 2019/3/17.
//  Copyright © 2019 易弘鹏. All rights reserved.
//

#ifndef functions_h
#define functions_h

#include <stdio.h>

// run the instruction read in currentLine
void run(void);


// R type, to avoid name conflict, some function name will extend an 'R' at the end
void add(int rd, int rs, int rt);
void addu(int rd, int rs, int rt);
void andR(int rd, int rs, int rt);
void divR(int rs, int rt);
void divu(int rs, int rt);
void jr(int rs);
void mfhi(int rd);
void mflo(int rd);
void mthi(int rs);
void mtlo(int rs);
void mult(int rs, int rt);
void multu(int rs, int rt);
void nor(int rd, int rs, int rt);
void orR(int rd, int rs, int rt);
void sll(int rd, int rt, int sa);
void slt(int rd, int rs, int rt);
void sltu(int rd, int rs, int rt);
void srl(int rd, int rt, int sa);
void sub(int rd, int rs, int rt);
void subu(int rd, int rs, int rt);
void xorR(int rd, int rs, int rt);
void systemCall(void);


// I type
void addi(int rt, int rs, int immediate);
void addiu(int rt, int rs, int immediate);
void andi(int rt, int rs, int immediate);
void beq(int rs, int rt, int label);
void bgez(int rs, int label);
void bgtz(int rs, int label);
void blez(int rs, int label);
void bltz(int rs, int label);
void bne(int rs, int rt, int label);
void lb(int rt, int immediate, int rs);
void lbu(int rt, int immediate, int rs);
void lui(int rt, int immediate);
void lw(int rt, int immediate, int rs);
void ori(int rt, int rs, int immediate);
void sb(int rt, int immediate, int rs);
void slti(int rt, int rs, int immediate);
void sltiu(int rt, int rs, int immediate);
void sw(int rt, int immediate, int rs);
void xori(int rt, int rs, int immediate);


// J type
void j(int target);
void jal(int target);

// Convert 5-bit, 16-bit, 26-bit binary number to decimal number
int bin2dec5(char* bin);
int bin2dec16(char* bin);
int bin2dec26(char* bin);


#endif /* functions_h */
