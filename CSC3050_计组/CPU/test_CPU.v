`timescale 1ns/1ps

// general register
`define gr0  	5'b00000
`define gr1  	5'b00001
`define gr2  	5'b00010
`define gr3 	5'b00011
`define gr4  	5'b00100
`define gr5  	5'b00101
`define gr6  	5'b00110
`define gr7  	5'b00111
`define gr8     5'b01000
`define gr9     5'b01001
`define gr10    5'b01010
`define gr11    5'b01011
`define gr12    5'b01100
`define gr13    5'b01101
`define gr14    5'b01110
`define gr15    5'b01111
`define gr16  	5'b10000
`define gr17  	5'b10001
`define gr18  	5'b10010
`define gr19 	5'b10011
`define gr20  	5'b10100
`define gr21  	5'b10101
`define gr22  	5'b10110
`define gr23  	5'b10111
`define gr24    5'b11000
`define gr25    5'b11001
`define gr26    5'b11010
`define gr27    5'b11011
`define gr28    5'b11100
`define gr29    5'b11101
`define gr30    5'b11110
`define gr31    5'b11111

module CPU_test;

    // Inputs
	reg clock;
	reg [31:0] d_datain;
	reg [31:0] i_datain;
    reg start;

    wire [31:0] d_dataout;

    CPU uut(
        .clock(clock),
        .start(start), 
		.d_datain(d_datain), 
		.i_datain(i_datain),
        .d_dataout(d_dataout)
    );

    initial begin
        // Initialize Inputs
        clock = 0;
        start = 0;
        d_datain = 0;
        i_datain = 0;

    $display("pc  :        instruction             : reg_A  : reg_B  : reg_C  : reg_C1 :d_datain:d_dataout:  gr0   :  gr1   :  gr2   :  gr3   :gr31($ra):mem_write");
    $monitor("%h:%b:%h:%h:%h:%h:%h:%h :%h:%h:%h:%h:%h : %b", 
        uut.pc, i_datain, uut.reg_A, uut.reg_B, uut.reg_C, uut.reg_C1, d_datain, d_dataout, uut.gr[0], uut.gr[1], uut.gr[2], uut.gr[3], uut.gr[31], uut.mem_write);   // print the first line

    /*Test:*/

    #5 start = 1; // posedge, print the second line

    #5 
    // lw test
    d_datain <= 32'h0000_00ab;
    i_datain <= {6'b100011, `gr0, `gr1, 16'h0001};  // lw gr1 1(gr0); gr1 = ab

    #period d_datain <= 32'h0000_3c00; 
    i_datain <= {6'b100011, `gr0, `gr2, 16'h0002};  //lw gr2 2(gr0); gr2 = 3c00

    // add test
    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3, 5'b00000, 6'b100000}; //add gr3 gr1 gr2; gr3 = 3cab

    // sub test
    #period i_datain <= {6'b000000, `gr3, `gr2, `gr3, 5'b00000, 6'b100010}; //sub gr3 gr3 gr2; gr3 = ab

    // addu test
    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3, 5'b00000, 6'b100000}; //addu gr3 gr1 gr2; gr3 = 3cab

    // subu test
    #period i_datain <= {6'b000000, `gr3, `gr2, `gr3, 5'b00000, 6'b100010}; //subu gr3 gr3 gr2; gr3 = ab

    // sw test
    #period i_datain <= {6'b101011, `gr0, `gr1, 16'h0002}; // sw gr1 2(gr0);

    // addi test
    #period i_datain <= {6'b001000, `gr1, `gr3, 16'h3c11}; // addi gr3 gr1 3c11; gr3 = 3cbc;

    // addiu test
    #period i_datain <= {6'b001000, `gr1, `gr3, 16'h3c00}; // addiu gr3 gr1 003c; gr3 = 3cab;

    // and test
    #period i_datain <= {6'b000000, `gr2, `gr3, `gr3, 5'b00000, 6'b100100}; // and gr3 gr2 gr3; gr3 = 3c00;

    // or test
    #period i_datain <= {6'b000000, `gr1, `gr3, `gr3, 5'b00000, 6'b100101}; // or gr3 gr1 gr3; gr3 = 3cab;

    // nor test
    #period i_datain <= {6'b000000, `gr0, `gr0, `gr3, 5'b00000, 6'b100111}; // nor gr3 gr0 gr0; gr3 = ffff_ffff;

    // xor test
    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3, 5'b00000, 6'b100110}; // xor gr3 gr1 gr2; gr3 = 3cab;

    // andi test
    #period i_datain <= {6'b001100, `gr1, `gr3, 16'h3cab}; // andi gr3 gr1 3cab; gr3 = ab;

    // ori test
    #period i_datain <= {6'b001101, `gr2, `gr3, 16'h00ab}; // ori gr3 gr2 00ab; gr3 = 3cab;

    // beq test
    #period i_datain <= {6'b000100, `gr1, `gr2, 16'h0002}; // beq gr1 gr2 0002; pc = pc + 4

    // beq test
    #period i_datain <= {6'b000100, `gr1, `gr1, 16'h0002}; // beq gr1 gr1 0002; pc = pc + 12

    // bne test
    #period i_datain <= {6'b000101, `gr1, `gr2, 16'h0002}; // bne gr1 gr2 0002; pc = pc + 12

    // slt test
    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3, 5'b00000, 6'b101010}; // slt gr3 gr1 gr2; gr3 = 1

    // j test
    #period i_datain <= {6'b000010, 26'h000_0100}; // pc = 400

    // jal test
    #period i_datain <= {6'b000011, 26'h000_0200}; // pc = 800; $ra = 400

    // jr test
    #period i_datain <= {6'b000000, `gr31, 5'b00000, 5'b00000, 5'b00000, 6'b001000}; // jr $ra; pc = 400;



    




    #period
    $finish;
    end

parameter period = 10;
always #5 clock = ~clock;
endmodule