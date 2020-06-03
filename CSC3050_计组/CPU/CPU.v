`timescale 1ns / 1ps

module CPU(

    input wire clock,
    input wire start,
    input [31:0] i_datain,  // Instruction as input
    input wire [31:0] d_datain, // The data should be loaded from data memory as input
    output wire [31:0] d_dataout    // The data should be stored into data memory.
    );

    reg [31:0]gr[31:0]; // 32 registers
    reg [15:0]pc = 32'h0000_0000; // address of pc

    reg [31:0]reg_A;    // SrcA
    reg [31:0]reg_B;    // SrcB
    reg [31:0]reg_C;    // ALUResult
    reg [31:0]reg_C1;   // Result
    reg [31:0]write_data;   // WD for data memory
    reg mem_write;  // WE for data memeory

    reg [5:0]opcode;
    reg [5:0]functcode;

always @(start)
    begin
        gr[0] = 32'h0000_0000;
    end

always @(posedge clock)
	begin

        //******************** Control Unit **********************//

        opcode = i_datain[31:26];
        functcode = i_datain[5:0]; // For R-type use

        // *************** Control Unit -- ALUSrc ****************//

        // ---------- reg_A: Always ---------
        reg_A = gr[i_datain[25:21]]; // reg_A = reg[rs] 


        // ------------- reg_B --------------

        // ***** 16-bit immediate sign-extended
        // lw, sw, addi
        if (opcode == 6'b100011 || opcode == 6'b101011 || opcode == 6'b001000)
            begin
                reg_B = {{16{i_datain[15]}}, i_datain[15:0]}; // reg_B = immediate, sign-extended
            end

        // ***** 16-bit immediate zero-extended
        // addiu, andi, ori
        else if (opcode == 6'b001001 || opcode == 6'b001100 || opcode == 6'b001101)
            begin 
                reg_B = {16'b0000_0000_0000_0000, i_datain[15:0]};
            end
        
        // ***** reg[rt]
        // R-type: add, sub, addu, subu, and, or, nor, xor, slt
        // Branch: beq, bne
        else if (opcode == 6'b000000 || opcode == 6'b000100 || opcode == 6'b000101)
            begin
                reg_B = gr[i_datain[20:16]]; // reg_B = reg[rt]
            end



        // ******************* Output to Data Memeory = *****************//

        write_data = gr[i_datain[20:16]]; // d_dataout = reg[rt]
        
        // ******************* Control Unit -- MemWrite *****************//

        // sw
        if (opcode == 6'b101011)
            mem_write = 1;
        // Ohter instructions also work but the data is unused.
        else  
            mem_write = 0;




        //******************* Control Unit -- ALUControl *****************//

        // lw, sw, addi, addiu
        if (opcode == 6'b100011 || opcode == 6'b101011 || opcode == 6'b001000 ||
            opcode == 6'b001001)
            begin
                reg_C = reg_A + reg_B;  // reg_C = reg[rs] + immediate
            end

        // andi
        else if (opcode == 6'b001100)
            reg_C = reg_A & reg_B;

        // ori
        else if (opcode == 6'b001101)
            reg_C = reg_A | reg_B;

        // beq, bne
        else if (opcode == 6'b000100 || opcode == 6'b000101)
            reg_C = reg_A - reg_B;


        // R-type
        else if (opcode == 6'b000000)
            begin

                // add, addu
                if (functcode == 6'b100000 || functcode == 6'b100001)
                    reg_C = reg_A + reg_B; // reg_C = reg[rs] + reg[rt]

                // sub, subu
                else if (functcode == 6'b100010 || functcode == 6'b100011)
                    reg_C = reg_A - reg_B; // reg_C = reg[rs] - reg[rt]

                // and
                else if (functcode == 6'b100100)
                    reg_C = reg_A & reg_B;

                // or
                else if (functcode == 6'b100101)
                    reg_C = reg_A | reg_B;

                // nor
                else if (functcode == 6'b100111)
                    reg_C = ~(reg_A | reg_B);

                // xor
                else if (functcode == 6'b100110)
                    reg_C = (~reg_A & reg_B) | (reg_A & ~reg_B);

                // slt
                else if (functcode == 6'b101010)
                    begin
                        if ($signed(reg_A) < $signed(reg_B)) 
                            reg_C = 1;
                        else 
                            reg_C = 0;
                    end

            end // R-Type




        //******************** Control Unit -- MemtoReg ********************//
        
        // lw, read data from memeory
        if (opcode == 6'b100011)
            begin
                reg_C1 = d_datain[31:0];   // reg_C1 = data from memory 
            end

        // add, sw, sub, addu, subu, and, or, nor, xor, addi, addiu, slt, beq, bne
        else
            begin
                reg_C1 = reg_C;
            end
        



        //********************* Control Unit -- RegWrite *******************//

        // RegWrite = 1:
        // R-type, lw, addi, addiu, andi, ori
        if (opcode == 6'b000000 || opcode == 6'b100011 || opcode == 6'b001000 ||
            opcode == 6'b001001 || opcode == 6'b001100 || opcode == 6'b001101)

            begin

                // ***************** Control Unit -- RegDst *****************//

                // --------reg[rt] as destination--------
                // I-type: lw, addi, addiu, andi, ori
                if (opcode == 6'b100011 || opcode == 6'b001000 || opcode == 6'b001001 ||
                    opcode == 6'b001100 || opcode == 6'b001101)
                    begin
                        gr[i_datain[20:16]] = reg_C1;      
                    end

                // --------reg[rd] as destination--------
                // R-type
                else if (opcode == 6'b000000)
                    begin
                        // add, sub, addu, subu, and, or, nor, xor, slt
                        if (functcode == 6'b100000 || functcode == 6'b100010 ||
                            functcode == 6'b100001 || functcode == 6'b100011 ||
                            functcode == 6'b100100 || functcode == 6'b100101 ||
                            functcode == 6'b100111 || functcode == 6'b100110 ||
                            functcode == 6'b101010)
                            begin
                                gr[i_datain[15:11]] = reg_C1; 
                            end

                    end // R-type
            
            end // RegWrite = 1



        //******************* Control Unit -- Branch and Jump *****************//

        pc <= pc + 32'h0000_0004;

        // branch
        if ((opcode == 6'b000100 && reg_C == 0) ||      // beq
            (opcode == 6'b000101 && reg_C != 0))        // bne
            begin
                pc <= pc + 4 + ({{16{i_datain[15]}}, i_datain[15:0]}) * 4;
            end
        
        // jr
        else if (opcode == 6'b000000 && functcode == 6'b001000)
            pc <= reg_A;

        // j
        else if (opcode == 6'b000010)
            pc <= {pc[31:28], i_datain[25:0], 2'b00};

        // jal
        else if (opcode == 6'b000011)
            begin
                gr[31] = pc;
                pc <= {pc[31:28], i_datain[25:0], 2'b00};
            end

            


    end // posedge clock


assign d_dataout = write_data;


endmodule
                
