#include<iostream>
#define ll long long int
#include <vector>
using namespace std;

int aluop = 2;
ll inst;

enum reg {
    zero,  at,  v0,  v1,  a0,  a1,  a2,  a3,
    t0,    t1,  t2,  t3,  t4,  t5,  t6,  t7,
    s0,    s1,  s2,  s3,  s4,  s5,  s6,  s7,
    t8,    t9,  k0,  k1,  gp,  sp,  fp,  ra
};

char type;
ll r[32];
int PC = 0;
int op, rs, rt, rd, shamt, func, address, jumpadd;
int memory[128];

int fetch() {
    inst = (memory[PC] << 24) | (memory[PC + 1] << 16) | (memory[PC + 2] << 8) | memory[PC + 3];
    op = (inst >> 26) & 0x3F;
    return inst;
}

void decode() {
    if (op == 0) { // R-type instruction
        type = 'r';
        rs = (inst >> 21) & 0x1F;
        rt = (inst >> 16) & 0x1F;
        rd = (inst >> 11) & 0x1F;
        shamt = (inst >> 6) & 0x1F;
        func = inst & 0x3F;

        // Determine ALU operation
        if (func == 32) { // ADD
            aluop = 2;
        } else if (func == 34) { // SUB
            aluop = 3;
        }
    } else if (op == 2 || op == 3) { // J-type instruction
        type = 'j';
        jumpadd = inst & 0x3FFFFFF;
    } else { // I-type instruction
        type = 'i';
        rs = (inst >> 21) & 0x1F;
        rt = (inst >> 16) & 0x1F;
        address = inst & 0xFFFF;

        // Determine ALU operation for I-type
        if (op == 8) { // ADDI
            aluop = 2;
        } else if (op == 35) { // LW
            aluop = 4;
        } else if (op == 43) { // SW
            aluop = 5;
        }
    }
}

int alu() { // Execute ALU operation
    switch (aluop) {
        case 2: // ADD
            r[rd] = r[rs] + r[rt];
            break;
        case 3: // SUB
            r[rd] = r[rs] - r[rt];
            break;
        case 4: // LW
            r[rt] = memory[r[rs] + address];
            break;
        case 5: // SW
            memory[r[rs] + address] = r[rt];
            break;
        default:
            cout << "Invalid ALU operation" << endl;
            return -1;
    }
    return 0;
}

int main() {
    // Example: Initialize memory with an instruction (mock example)
    memory[0] = 0x20080005; // ADDI $t0, $zero, 5 (assuming little-endian order in memory)
    fetch();
    decode();
    alu();
    cout << "Register t0 value: " << r[t0] << endl;
    return 0;
}
llrintlgcvtfryxycdbrtvxeyrdb