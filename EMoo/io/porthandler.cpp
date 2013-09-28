#include "porthandler.h"

PortHandler::PortHandler()
{
}

uint8_t PortHandler::in8(uint16_t port){
    printf("%x\n", port);
}

uint8_t PortHandler::in16(uint16_t port) {

}

void PortHandler::out8(uint16_t port, uint8_t value) {

}

void PortHandler::out16(uint16_t port, uint8_t value) {

}
