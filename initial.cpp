#include<iostream>
#define ll long long int
#include <vector>
using namespace std;
        int regdst;
        int alusrc;
        int memreg;
        int regwr;
        int memrd;
        int memwr;
        int branch;
        int aluop1;
        int aluop0;
        int jmp;
        int aluop;

int aluop=2;
enum reg {
    zero,  at,  v0,  v1,  a0,  a1,  a2,  a3,  // 0-7
    t0,    t1,  t2,  t3,  t4,  t5,  t6,  t7,  // 8-15
    s0,    s1,  s2,  s3,  s4,  s5,  s6,  s7,  // 16-23
    t8,    t9,  k0,  k1,  gp,  sp,  fp,  ra   // 24-31
};
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
    
//

   
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
    else if(op==0b000010)
    {
        type='j';
        jumpadd=(inst & 0x3FFFFFF)<<2;
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
else if(type=='j')
    {
        PC=jumpadd;
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
                r[rd]=r[rs] | r[rt];
            }
            else if(ctrlinput==4) {
                //r[rd] = (r[rs] < r[rt]) ? 1 : 0;      
            }
        }
        else if (type=='i') {
            if(ctrlinput==2) {
                PC=PC+4*address;        //write data when?,this is wrong pc shudnt change we shud just access the location and write or read data
                
            }
        }
}


int ctrlcircuit()
{
    if(op==000000)
    {
        regdst=1;
        alusrc=0;
        memreg=0;
        regwr=1;
        memrd=0;
        memwr=0;
        branch=0;
        aluop1=1;
        aluop0=0;
        jmp=0;
        aluop=0b10;

    }
    else if(op==100011)
    {
        regdst=0;
        alusrc=1;
        memreg=1;
        regwr=1;
        memrd=1;
        memwr=0;
        branch=0;
        aluop1=0;
        aluop0=0;
        aluop=0b00;
        jmp=0;
    }
    else if(op==101011)
    {
        regdst=2;
        alusrc=1;
        memreg=2;
        regwr=0;
        memrd=0;
        memwr=1;
        branch=0;
        aluop1=0;
        aluop0=0;
        jmp=0;
        aluop=0b00;
    }
    else if(op==000100)
    {
        regdst=2;
        alusrc=0;
        memreg=2;
        regwr=0;
        memrd=0;
        memwr=0;
        branch=1;
        aluop1=0;
        aluop0=1;
        jmp=0;
        aluop=0b01;
    }
    else if(op==000010)
    {
        regdst=2;
        alusrc=2;
        memreg=2;
        regwr=0;
        memrd=0;
        memwr=0;
        branch=2;
        aluop1=2;
        aluop0=2;
        jmp=1;
        aluop=0b11;
    }
}

int ctrlinput()
{
    
}
