#include <iostream>
#include <vector>

#define ll long long int
using namespace std;

int aluop = 2;
ll inst;

enum reg {
    zero, at, v0, v1, a0, a1, a2, a3,  // 0-7
    t0, t1, t2, t3, t4, t5, t6, t7,   // 8-15
    s0, s1, s2, s3, s4, s5, s6, s7,   // 16-23
    t8, t9, k0, k1, gp, sp, fp, ra    // 24-31
};

char type;
ll r[32] = {0};  // Register file initialized to zero
int PC = 0;
int op, rs, rt, rd, shamt, func, address, jumpadd;
int ctrlinput;
int memory[128] = {0};  // Simulated memory

void fetch() {
    inst = (memory[PC] << 24) | (memory[PC + 1] << 16) | (memory[PC + 2] << 8) | memory[PC + 3];
    op = (inst >> 26) & 0x3F;
        cout << "Fetched instruction: " << hex << inst << " at PC: " << dec << PC << endl;

    PC += 4;  // Move to the next instruction
}

void decode() {
    cout << "Decoding instruction: " << hex << inst << endl;
    cout << "Opcode: " << op << endl;

    if (op == 0) { // R-type
        type = 'r';
        rs = (inst >> 21) & 0x1F;
        rt = (inst >> 16) & 0x1F;
        rd = (inst >> 11) & 0x1F;
        shamt = (inst >> 6) & 0x1F;
        func = inst & 0x3F;
        
        cout << "R-type -> rs: " << rs << ", rt: " << rt << ", rd: " << rd << ", func: " << func << endl;
    } else { // I-type
        type = 'i';
        rs = (inst >> 21) & 0x1F;
        rt = (inst >> 16) & 0x1F;
        address = inst & 0xFFFF;
        
        cout << "I-type -> rs: " << rs << ", rt: " << rt << ", address: " << address << endl;
    }

    cout << "Control Signal: " << ctrlinput << endl;
}


int alu() {   
    cout << "Executing ALU operation, ctrlinput: " << ctrlinput << endl;

    if (type == 'r') {
        cout << "Before ALU: r[rs] = " << r[rs] << ", r[rt] = " << r[rt] << endl;
        
        if (ctrlinput == 2) { // ADD
            r[rd] = r[rs] + r[rt];
        } else if (ctrlinput == 3) { // SUB
            r[rd] = r[rs] - r[rt];
        } else if (ctrlinput == 0) { // AND
            r[rd] = r[rs] & r[rt];
        } else if (ctrlinput == 1) { // OR
            r[rd] = r[rs] | r[rt];
        }

        cout << "After ALU: r[rd] = " << r[rd] << endl;
    }
}

void execute() {
    fetch();
    decode();
    alu();
}

int main() {
    r[1] = 10;  
r[5] = 20;
r[8] = 30;
int memory[128] = {  
0b00000000,

};



    while (PC < 32) { // Run a small test program
        execute();
        cout<<memory[s0]<<"\n";
    }

    return 0;
}
