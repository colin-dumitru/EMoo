#ifndef PPI_H
#define PPI_H

#include "common.h"

/**
 * @brief Programmable Peripheral Interface
 */
class PPI
{
    /*
     *option flags - port 0x61
     *
        bit 7	(1= IRQ 0 reset )
        bit 6-4    reserved
        bit 3 = 1  channel check enable
        bit 2 = 1  parity check enable
        bit 1 = 1  speaker data enable
        bit 0 = 1  timer 2 gate to speaker enable
    */
    static uint8_t controllRegister;
    /*
     *option flags - port 0x62
     *
        bit 7 = 1  clear keyboard
        bit 6 = 0  hold keyboard clock low
        bit 5 = 0  I/O check enable
        bit 4 = 0  RAM parity check enable
        bit 3 = 0  read low switches
        bit 2	    reserved, often used as turbo switch
        bit 1 = 1  speaker data enable
        bit 0 = 1  timer 2 gate to speaker enable
    */
    static uint8_t controllRegister2;
    /*
     *command register - port 0x63
     *
        bit 7-6 = 00  1 diskette drive
         = 01  2 diskette drives
         = 10  3 diskette drives
         = 11  4 diskette drives
        bit 5-4 = 00  reserved
         = 01  40*25 color (mono mode)
         = 10  80*25 color (mono mode)
         = 11  MDA 80*25
        bit 3-2 = 00  256K (using 256K chips)
         = 01  512K (using 256K chips)
         = 10  576K (using 256K chips)
         = 11  640K (using 256K chips)
        bit 3-2 = 00  64K  (using 64K chips)
         = 01  128K (using 64K chips)
         = 10  192K (using 64K chips)
         = 11  256K (using 64K chips)
        bit 1-0       reserved
    */
    static uint8_t commandRegister;

public:
    PPI();

    static uint8_t read61(uint16_t port);
    static void write61(uint16_t port, uint8_t value);

    static uint8_t read62(uint16_t port);
    static void write62(uint16_t port, uint8_t value);

    static uint8_t read63(uint16_t port);
    static void write63(uint16_t port, uint8_t value);
};

#endif // PPI_H
