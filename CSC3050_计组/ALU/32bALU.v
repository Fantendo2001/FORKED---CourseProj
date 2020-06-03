module alu(a,b,immediate,opcode,c,HI,LO,zero,overflow,neg);

output signed[31:0] c, HI, LO;
output zero;
output overflow;
output neg;

input signed[31:0] a,b;
input[4:0] opcode;
input [15:0] immediate;

reg[32:0] reg_C;
reg of;
reg zf;
reg nf;
reg[31:0] reg_A, reg_B, imm;
reg[63:0] HILO;
reg[15:0] root;
reg[4:0] i;


parameter  sla = 5'b00000,  // sla  -- 0
srai = 5'b00001,            // srai -- 1
add = 5'b00010,             // add  -- 2
sub = 5'b00011,             // sub  -- 3
mult = 5'b00100,            // mult -- 4
div = 5'b00101,             // div  -- 5
addi = 5'b00110,            // addi -- 6
addu = 5'b00111,            // addu -- 7
subu = 5'b01000,            // subu -- 8
multu = 5'b01001,           // multu-- 9
divu = 5'b01010,            // divu -- 10
addiu = 5'b01011,           // addiu-- 11
sqrt = 5'b01100,            // sqrt -- 12

// To prevent conflict with key word, the logic instructions begin with '_'
_and = 5'b01101,            // _and -- 13
_or = 5'b01110,             // _or  -- 14
_nor = 5'b01111,            // _nor -- 15
_xor = 5'b10000,            // _xor -- 16
_xnor = 5'b10001,           // _xnor-- 17

andi = 5'b10010,            // andi -- 18
ori = 5'b10011,             // ori  -- 19
slt = 5'b10100,             // slt  -- 20
slti = 5'b10101;            // slti -- 21



always @(a,b,opcode)
begin

reg_A = a;
reg_B = b;
reg_C = 0;
of = 0;
zf = 0;
nf = 0;
HILO = 0;
i = 15;

case(opcode)

sla: // arith left shift
begin
    reg_C={reg_A[30:0],1'b0};
    zf = !reg_C[31:0];
end

srai: // arith right shift
begin
    reg_C={reg_A[31:1]};
    reg_A=reg_C;
    zf = !reg_C[31:0];
end

add: // add
begin
    reg_C = reg_A + reg_B;
    // overflow detection
    if (!reg_A[31] && !reg_B[31] && reg_C[31]) of = 1; // adding two +ve operands, overflow when result sign is 1
    else if (reg_A[31] && reg_B[31] && !reg_C[31]) of = 1; // adding two -ve operands, overflow when result sign is 0
    else of = 0;
    zf = !reg_C[31:0];
    nf = reg_C[31];
end

addu: // addu
begin
    reg_C = reg_A + reg_B;
    zf = !reg_C[31:0];
end

addi: // addi
begin
    imm = {{16{immediate[15]}}, immediate};     // sign-extended immediate
    reg_C = reg_A + imm;
    if (!reg_A[31] && !imm[31] && reg_C[31]) of = 1; // adding two +ve operands, overflow when result sign is 1
    else if (reg_A[31] && imm[31] && !reg_C[31]) of = 1; // adding two -ve operands, overflow when result sign is 0
    else of = 0;
    reg_A = reg_C;
    zf = !reg_C[31:0];
    nf = reg_C[31];
end

addiu: // addiu
begin
    imm = {16'b0000_0000_0000_0000, immediate};     // zero-extended immediate
    reg_C = reg_A + imm;
    reg_A = reg_C;
    zf = !reg_C[31:0];
end

sub: // sub
begin 
    reg_C = reg_A - reg_B;
    // overflow detection
    if (!reg_A[31] & reg_B[31] & reg_C[31]) of = 1; // subtracting -ve from +ve operand, overflow when result sign is 1
    else if (reg_A[31] & !reg_B[31] & !reg_C[31]) of = 1; // subtracting +ve from -ve operand, overflow when result sign is 0
    else of = 0;
    zf = !reg_C[31:0];
    nf = reg_C[31];
end


subu: // subu
begin
    reg_C = reg_A - reg_B;
    if (reg_A < reg_B) nf = 1;
    zf = !reg_C[31:0];
end

mult: // mult
begin 
    HILO = $signed(reg_A) * $signed(reg_B);
    zf = !HILO;
    nf = HILO[63];
end


multu: // multu
begin
    HILO = reg_A * reg_B;
    zf = !HILO;
end

div: // div
begin
    HILO[31:0] = $signed(reg_A) / $signed(reg_B);     // LO: quotient
    HILO[63:32] = $signed(reg_A) % $signed(reg_B);    // HI: remainder
    nf = HILO[31];  // depends on the sign of quotient
end

divu: // divu
begin
    HILO[31:0] = reg_A / reg_B;     // LO: quotient
    HILO[63:32] = reg_A % reg_B;    // HI: remainder
end


_and: // _and
begin
    reg_C = reg_A & reg_B;
    zf = !reg_C[31:0];
end

_or: // _or
begin
    reg_C = reg_A | reg_B;
    zf = !reg_C[31:0];
end

_nor: // _nor
begin
    reg_C = ~(reg_A | reg_B);
    zf = !reg_C[31:0];
end

_xor: // _xor
begin
    reg_C = (reg_A & ~reg_B) | (~reg_A & reg_B);
    zf = !reg_C[31:0];
end

_xnor: // _xnor
begin
    reg_C = ~((reg_A & ~reg_B) | (~reg_A & reg_B));
    zf = !reg_C[31:0];
end

andi: // andi
begin
    imm = {16'b0000_0000_0000_0000, immediate};     // zero-extended immediate
    reg_C = reg_A & imm;
    reg_A = reg_C;
    zf = !reg_C[31:0];
end

ori: // ori
begin
    imm = {16'b0000_0000_0000_0000, immediate};     // zero-extended immediate
    reg_C = reg_A | imm;
    reg_A = reg_C;
    zf = !reg_C[31:0];
end

slt: // slt
begin 
    if ($signed(reg_A) < $signed(reg_B)) reg_C = 1;
    else reg_C = 0;
    zf = !reg_C[31:0];
end

slti: // slti
begin 
    imm = {{16{immediate[15]}}, immediate};     // sign-extended immediate
    if ($signed(reg_A) < $signed(imm)) reg_C = 1;
    else reg_C = 0;
    zf = !reg_C[31:0];
end


// For 'sqrt', I fail to implement it since verilog doesn't allow variable index.
// However, I still leave this block of C-style code here to show my effort :)
// ------------------------------------------------------------------------------
// sqrt: 
// begin
//     for (i = 15; i >= 0; i = i - 1) begin
//         reg_C = reg_C * 2 + 1;
//         if ((reg_C ** 2) > reg_A[31:i*2]) reg_C[0] = 0;
//         else reg_C[0] = 1;
//     end 
//     zf = !reg_C[31:0];
// end

endcase
end

assign c = reg_C[31:0];
assign zero = zf;  // zero flag -- becomes 1 when output is 0
assign overflow = of;
assign neg = nf;
assign LO = HILO[31:0];
assign HI = HILO[63:32];

endmodule
