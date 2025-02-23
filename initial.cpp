#include<iostream>
#define ll long long int
#include <vector>
using namespace std;

int aluop=2;

enum reg {
    zero,  at,  v0,  v1,  a0,  a1,  a2,  a3,  // 0-7
    t0,    t1,  t2,  t3,  t4,  t5,  t6,  t7,  // 8-15
    s0,    s1,  s2,  s3,  s4,  s5,  s6,  s7,  // 16-23
    t8,    t9,  k0,  k1,  gp,  sp,  fp,  ra   // 24-31
};
char type;
ll r[32];

int PC;
int op,rs,rt,rd,shamt,func,address,jumpadd;
char type;
//vector<ll> memory;
int memory[128];

int fetch()
{
    int inst = (memory[PC] << 24) | (memory[PC + 1] << 16) | (memory[PC + 2] << 8) | memory[PC + 3];
    op = (inst >> 26) & 0x3F;
    if(op==0)
    {
        type='r';
        rs=(inst >> 21) & 0x1F;
        rt=(inst >> 16) & 0x1F;
        rd=(inst >> 11) & 0x1F;
        shamt=(inst >> 6) & 0x1F;
        func=inst & 0x3F;

    }
    else
    {
        type='i';
        rs=(inst >> 21) & 0x1F;
        rt=(inst >> 16) & 0x1F;
        address=(inst)& 0xFFFF;
    }


    PC=PC+4;
}
void decode()
{
    if(type=='r') //find the function and send to alu
    {
        if (func == 32) { // ADD
        aluop=2;
            
            
        } else if (func == 34) { // SUB
        aluop=3;
            
        }
    }

    else if(type=='i')
    {


    }
}
int alu() //do the operation
{

}



