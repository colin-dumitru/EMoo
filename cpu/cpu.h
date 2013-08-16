#ifndef CPU_H
#define CPU_H

#include "mem/register16.h"

class Cpu
{
public:
    Register16 ax;
    Register16 bx;
    Register16 cx;
    Register16 dx;
    Register16 si;
    Register16 di;
    Register16 sp;
    Register16 bp;
    Register16 ip;
    Register16 cs;
    Register16 ds;
    Register16 ss;
    Register16 es;
    Register16 fs;
    Register16 gs;

    Cpu();
};

#endif // CPU_H
