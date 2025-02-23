#include <iostream>
#define ll long long int
#include <vector>
using namespace std;

int aluop = 2;
ll inst;

enum reg {
    zero, at, v0, v1, a0, a1, a2, a3,  // 0-7
    t0, t1, t2, t3, t4, t5, t6, t7,    // 8-15
    s0, s1, s2, s3, s4, s5, s6, s7,    // 16-23
    t8, t9, k0, k1, gp, sp, fp, ra     // 24-31
};

char type;
ll r[32] = {0}; // Register array initialized to 0

int PC = 0;
int op, rs, rt, rd, shamt, func, address, jumpadd;
int ctrlinput;
int memory[128] = {0}; // Simulated memory

void fetch() {
    inst = (memory[PC] << 24) | (memory[PC + 1] << 16) | (memory[PC + 2] << 8) | memory[PC + 3];
    op = (inst >> 26) & 0x3F;
}

void decode() {
    if (op == 0) {  // R-type instruction
        type = 'r';
        rs = (inst >> 21) & 0x1F;
        rt = (inst >> 16) & 0x1F;
        rd = (inst >> 11) & 0x1F;
        shamt = (inst >> 6) & 0x1F;
        func = inst & 0x3F;

        if (func == 32) {  // ADD
            ctrlinput = 2;
        } else if (func == 34) {  // SUB
            ctrlinput = 3;
        } else if (func == 0b100100) {  // AND
            ctrlinput = 0;
        } else if (func == 0b100101) {  // OR
            ctrlinput = 1;
        } else if (func == 0b101010) {  // SLT
            ctrlinput = 4;
        }

    } else {  // I-type instruction
        type = 'i';
        rs = (inst >> 21) & 0x1F;
        rt = (inst >> 16) & 0x1F;
        address = inst & 0xFFFF;

        if (op == 0b100011) {  // LW
            ctrlinput = 5;
        } else if (op == 0b101011) {  // SW
            ctrlinput = 6;
        } else if (op == 0b000100) {  // BEQ
            ctrlinput = 7;
        }
    }
}

void execute() {   
    if (type == 'r') {
        if (ctrlinput == 2) {  // ADD
            r[rd] = r[rs] + r[rt];
        } else if (ctrlinput == 3) {  // SUB
            r[rd] = r[rs] - r[rt];
        } else if (ctrlinput == 0) {  // AND
            r[rd] = r[rs] & r[rt];
        } else if (ctrlinput == 1) {  // OR
            r[rd] = r[rs] | r[rt];
        } else if (ctrlinput == 4) {  // SLT
            r[rd] = (r[rs] < r[rt]) ? 1 : 0;
        }
    } else if (type == 'i') {
        if (ctrlinput == 5) {  // LW
            r[rt] = memory[(r[rs] + address) / 4];
        } else if (ctrlinput == 6) {  // SW
            memory[(r[rs] + address) / 4] = r[rt];
        } else if (ctrlinput == 7) {  // BEQ
            if (r[rs] == r[rt]) {
                PC += (address << 2);
            }
        }
    }
    
    // Increment PC unless it's a jump or branch instruction
    if (op != 0b000010 && op != 0b000100) {
        PC += 4;
    }
}

int main() {
    // Sample test: Load an instruction in memory
    memory[0] = 0x00;  // First byte
    memory[1] = 0x20;  // Second byte
    memory[2] = 0x80;  // Third byte
    memory[3] = 0x20;  // Fourth byte (this forms the instruction)

    fetch();
    decode();
    execute();

    // Debug output
    cout << "PC: " << PC << endl;
    cout << "Register rd: " << r[rd] << endl;
    return 0;
}
