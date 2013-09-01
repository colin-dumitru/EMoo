#include "addtest.h"
#include "machine.h"

AddTest::AddTest()
{
}

void AddTest::opAddRmbRb() {

    uint8_t memory[] = {
        0x00, 0xCC,  //add ah cl
        0x00, 0x00, //add DS:[BX + SI] al
        0x00, 0x82, 0x01, 0x00, //add DS:[BP + SI + disp16] al
        0x00, 0x0E, 0x04, 0x00, //add DS:[disp16] cl
        0x36, 0x00, 0x52, 0x03, //add SS:[BP + SI + disp8] dl
        0x05, 0x10, 0x12, 0x17, 0x20
    };
    machine.ram.write(0, memory, sizeof(memory)/sizeof(*memory));

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
