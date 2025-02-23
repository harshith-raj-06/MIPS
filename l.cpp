#include<iostream>
#define ll long long int
#include <vector>
using namespace std;

int aluop=2;
ll inst;

enum reg {
    zero,  at,  v0,  v1,  a0,  a1,  a2,  a3,  // 0-7
    t0,    t1,  t2,  t3,  t4,  t5,  t6,  t7,  // 8-15
    s0,    s1,  s2,  s3,  s4,  s5,  s6,  s7,  // 16-23
    t8,    t9,  k0,  k1,  gp,  sp,  fp,  ra   // 24-31
};
char type;
ll r[32];

int PC;
int inst,op,rs,rt,rd,shamt,func,address,jumpadd;
char type;
int ctrlinput;
//vector<ll> memory;
int memory[128]={0};

int fetch()
{
    inst = (memory[PC] << 24) | (memory[PC + 1] << 16) | (memory[PC + 2] << 8) | memory[PC + 3];
    op = (inst >> 26) & 0x3F;
    


   
}
void decode()
{
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
    if(type=='r') //find the function and send to alu
    {
        if (func == 32) 
        { // ADD
        ctrlinput=2;
            
            
        } else if (func == 34) { // SUB
        ctrlinput=3;

            
        }
        else if(func==0b000100)
        {
            ctrlinput=3;
        }
        else if(func==0b100100)
        {
            ctrlinput=1;
        }
        else if(func==0b100101)
        {
            ctrlinput=0;
        }
        else if(func==0b101010)
        {
            ctrlinput=4;
        }

        //load==opcode(100011),store(101011),branchequivalent(000100),and(function ==100100),or(100101),setonlessthan(101010),jump(000010)

    }

    else if(type=='i')
    {
         if(op==0b100011)
        {
            ctrlinput=2;
        }
        else if(op==0b101011)
        {
            ctrlinput=2;
        }

    }
}
int alu() //do the operation
{   
        if(type=='r') {
            if(ctrlinput==2) {
                r[rd]=r[rs]+r[rt];
            }
            else if(ctrlinput==3) {
                r[rd]=r[rs]-r[rt];
            }
            else if(ctrlinput==0) {
                r[rd]=r[rs]&r[rt];
            }
            else if(ctrlinput==1) {
                r[rd]=r[rs]|r[rt];
            }
            else if(ctrlinput==4) {
                //r[rd] = (r[rs] < r[rt]) ? 1 : 0;      
            }
        }
        else if (type=='i') {
            if(ctrlinput==2) {
                PC=PC+4*address;
            }
        }
}


