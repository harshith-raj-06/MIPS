#include <iostream>
#define ll long long int
using namespace std;

enum reg {
    zero,  at,  v0,  v1,  a0,  a1,  a2,  a3,  // 0-7
    t0,    t1,  t2,  t3,  t4,  t5,  t6,  t7,  // 8-15
    s0,    s1,  s2,  s3,  s4,  s5,  s6,  s7,  // 16-23
    t8,    t9,  k0,  k1,  gp,  sp,  fp,  ra   // 24-31
};

ll r[32];       // Register File
int PC = 0;     // Program Counter
int memory[128]; // Memory Array

// Instruction Fields
int op, rs, rt, rd, shamt, func, address;
char type;

// Fetch Function
void fetch() {
    int inst = (memory[PC] << 24) | (memory[PC + 1] << 16) | (memory[PC + 2] << 8) | memory[PC + 3];
    op = (inst >> 26) & 0x3F;
    
    if (op == 0) { // R-Type Instruction
        type = 'r';
        rs = (inst >> 21) & 0x1F;
        rt = (inst >> 16) & 0x1F;
        rd = (inst >> 11) & 0x1F;
        shamt = (inst >> 6) & 0x1F;
        func = inst & 0x3F;
    } else { // I-Type Instruction
        type = 'i';
        rs = (inst >> 21) & 0x1F;
        rt = (inst >> 16) & 0x1F;
        address = inst & 0xFFFF;
    }

    PC += 4;
}

// Decode Function
void decode() {
    if (type == 'r') {
        if (func == 32) { // ADD
            r[rd] = r[rs] + r[rt];
            cout << "ADD: r[" << rd << "] = r[" << rs << "] + r[" << rt << "]" << endl;
        } else if (func == 34) { // SUB
            r[rd] = r[rs] - r[rt];
            cout << "SUB: r[" << rd << "] = r[" << rs << "] - r[" << rt << "]" << endl;
        }
    } else if (type == 'i') {
        if (op == 35) { // LW (Load Word)
            r[rt] = memory[r[rs] + address];
            cout << "LW: r[" << rt << "] = memory[r[" << rs << "] + " << address << "]" << endl;
        } else if (op == 43) { // SW (Store Word)
            memory[r[rs] + address] = r[rt];
            cout << "SW: memory[r[" << rs << "] + " << address << "] = r[" << rt << "]" << endl;
        }
    }
}

int main() {
    // Example: Setting up a simple ADD instruction
    r[t0] = 10;
    r[t1] = 20;
    
    // Simulated instruction for ADD $t2, $t0, $t1 (0x00095020)
    memory[0] = 0x00; // First 8 bits
    memory[1] = 0x09; // Next 8 bits
    memory[2] = 0x50; // Next 8 bits
    memory[3] = 0x20; // Last 8 bits
    
    fetch();
    decode();

    cout << "Result in t2: " << r[t2] << endl; // Expected Output: 30

    return 0;
}
