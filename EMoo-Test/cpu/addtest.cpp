#include "addtest.h"
#include "machine.h"

AddTest::AddTest()
{
}

void AddTest::opAddRmbRb() {
    machine.reset();

    uint8_t memory[] = {
        0x00, 0xCC,  //add ah cl
        0x00, 0x00, //add DS:[BX + SI] al
        0x00, 0x82, 0x01, 0x00, //add DS:[BP + SI + disp16] al
        0x00, 0x0E, 0x04, 0x00, //add DS:[disp16] cl
        0x36, 0x00, 0x52, 0x03, //add SS:[BP + SI + disp8] dl
        0x05, 0x10, 0x12, 0x17, 0x20
    };
    machine.ram.write(0, memory, sizeof(memory)/sizeof(*memory));

    machine.cpu.ip.data = 0x00;
    machine.cpu.cs.data = 0x00;
    machine.cpu.ax.data = 0x01;
    machine.cpu.bx.data = 0x02;
    machine.cpu.cx.data = 0x07;
    machine.cpu.dx.data = 0x10;
    machine.cpu.ss.data = 0x00;
    machine.cpu.ds.data = 0x01;
    machine.cpu.bp.data = 0x01;
    machine.cpu.si.data = 0x01;

    //ax = 0x0701
    machine.step();
    QCOMPARE(machine.cpu.ax.data, (uint16_t)0x0701);
    QCOMPARE(HIGH(machine.cpu.ax.data), (uint8_t)0x07);
    QCOMPARE(LOW(machine.cpu.ax.data), (uint8_t)0x01);

    //[19] = 0x18
    machine.step();
    QCOMPARE(machine.ram.buffer[19], (uint8_t)0x18);

    //[19] = 0x20
    machine.step();
    QCOMPARE(machine.ram.buffer[19], (uint8_t)0x19);

    //[20] = 0x27
    machine.step();
    QCOMPARE(machine.ram.buffer[20], (uint8_t)0x27);

    //[5] = 0x92
    machine.step();
    QCOMPARE(machine.ram.buffer[5], (uint8_t)0x92);
}

void AddTest::opAddRmwRw() {
    machine.reset();

    uint8_t memory[] = {
        0x01, 0xCC,  //add sp cx
        0x01, 0x00, //add DS:[BX + SI] ax
        0x01, 0x82, 0x01, 0x00, //add DS:[BP + SI + disp16] ax
        0x01, 0x0E, 0x04, 0x00, //add DS:[disp16] cx
        0x36, 0x01, 0x52, 0x03, //add SS:[BP + SI + disp8] dx
        0x05, 0x10, 0x12, 0x17, 0x20
    };
    machine.ram.write(0, memory, sizeof(memory)/sizeof(*memory));

    machine.cpu.ax.data = 0x01;
    machine.cpu.bx.data = 0x02;
    machine.cpu.cx.data = 0x07;
    machine.cpu.sp.data = 0x10;
    machine.cpu.ss.data = 0x00;
    machine.cpu.ds.data = 0x01;
    machine.cpu.bp.data = 0x01;
    machine.cpu.si.data = 0x01;

    //ax = 0x0701
    machine.step();
    QCOMPARE(machine.cpu.sp.data, (uint16_t)0x0017);

    //[19] = 0x18
    machine.step();
    QCOMPARE(machine.ram.buffer[19], (uint8_t)0x18);

    //[19] = 0x20
    machine.step();
    QCOMPARE(machine.ram.buffer[19], (uint8_t)0x19);

    //[20] = 0x27
    machine.step();
    QCOMPARE(machine.ram.buffer[20], (uint8_t)0x27);

    //[5] = 0x92
    machine.step();
    QCOMPARE(machine.ram.buffer[5], (uint8_t)0x92);
}

void AddTest::opAddRbRmb() {
    //.data:0x00000000	02cc        add    cl,ah
    //.data:0x00000002	0200        add    al,BYTE PTR [bx+si]
    //.data:0x00000004	02820100	add    al,BYTE PTR [bp+si+0x1]
    //.data:0x00000008	020e0400	add    cl,BYTE PTR ds:0x4
    //.data:0x0000000c	36025203	add    dl,BYTE PTR ss:[bp+si+0x3]

    machine.reset();

    uint8_t memory[] = {
        0x02, 0xCC,
        0x02, 0x00,
        0x02, 0x82, 0x01, 0x00,
        0x02, 0x0E, 0x04, 0x00,
        0x36, 0x02, 0x52, 0x03,
        0x05, 0x10, 0x12, 0x17, 0x20
    };
    machine.ram.write(0, memory, sizeof(memory)/sizeof(*memory));

    machine.cpu.ax.data = 0x0100;
    machine.cpu.bx.data = 0x02;
    machine.cpu.cx.data = 0x07;
    machine.cpu.dx.data = 0x00;
    machine.cpu.sp.data = 0x10;
    machine.cpu.ss.data = 0x00;
    machine.cpu.ds.data = 0x01;
    machine.cpu.bp.data = 0x01;
    machine.cpu.si.data = 0x01;

    machine.step();
    QCOMPARE(machine.cpu.cx.data, (uint16_t)0x08);

    machine.step();
    QCOMPARE(machine.cpu.ax.data, (uint16_t)0x0117);

    machine.step();
    QCOMPARE(machine.cpu.ax.data, (uint16_t)0x012E);

    machine.step();
    QCOMPARE(machine.cpu.cx.data, (uint16_t)0x28);

    machine.step();
    QCOMPARE(machine.cpu.dx.data, (uint16_t)0x82);
}

void AddTest::opAddRwRmw() {
    //.data:0x00000000	03cc        add    cx,sp
    //.data:0x00000002	0300        add    ax,WORD PTR [bx+si]
    //.data:0x00000004	03820100	add    ax,WORD PTR [bp+si+0x1]
    //.data:0x00000008	030e0400	add    cx,WORD PTR ds:0x4
    //.data:0x0000000c	36035203	add    dx,WORD PTR ss:[bp+si+0x3]
    machine.reset();

    uint8_t memory[] = {
        0x03, 0xCC,
        0x03, 0x00,
        0x03, 0x82, 0x01, 0x00,
        0x03, 0x0E, 0x04, 0x00,
        0x36, 0x03, 0x52, 0x03,
        0x05, 0x10, 0x12, 0x17, 0x20
    };
    machine.ram.write(0, memory, sizeof(memory)/sizeof(*memory));

    machine.cpu.ax.data = 0x01;
    machine.cpu.bx.data = 0x02;
    machine.cpu.cx.data = 0x07;
    machine.cpu.dx.data = 0x00;
    machine.cpu.sp.data = 0x10;
    machine.cpu.ss.data = 0x00;
    machine.cpu.ds.data = 0x01;
    machine.cpu.bp.data = 0x01;
    machine.cpu.si.data = 0x01;

    machine.step();
    QCOMPARE(machine.cpu.cx.data, (uint16_t)0x17);

    machine.step();
    QCOMPARE(machine.cpu.ax.data, (uint16_t)0x2018);

    machine.step();
    QCOMPARE(machine.cpu.ax.data, (uint16_t)0x402F);

    machine.step();
    QCOMPARE(machine.cpu.cx.data, (uint16_t)0x37);

    machine.step();
    QCOMPARE(machine.cpu.dx.data, (uint16_t)0x0182);
}
