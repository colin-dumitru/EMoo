#include "porthandler.h"

PortHandler::PortHandler()
{
    for (int i = 0; i < PORT_RANGE; i++) {
        readHandlers[i] = &dummyReader;
        writeHandlers[i] = &dummyWriter;
    }
}

void PortHandler::registerReader(uint16_t port, uint8_t (*handler)(uint16_t)) {
    readHandlers[port] = handler;
}

void PortHandler::registerWriter(uint16_t port, void (*handler)(uint16_t, uint8_t)) {
    writeHandlers[port] = handler;
}

uint8_t PortHandler::in8(uint16_t port){
    return readHandlers[port](port);
}

uint16_t PortHandler::in16(uint16_t port) {
    return readHandlers[port](port)
            | (readHandlers[port + 1](port + 1) << 8);
}

void PortHandler::out8(uint16_t port, uint8_t value) {
    writeHandlers[port](port, value);
}

void PortHandler::out16(uint16_t port, uint16_t value) {
    writeHandlers[port](port, (uint8_t)value);
    writeHandlers[port + 1](port + 1, value >> 8);
}

void PortHandler::dummyWriter(uint16_t port, uint8_t value) {
    ERR("unsupported IO write: %x:%x", port, value);
}

uint8_t PortHandler::dummyReader(uint16_t port) {
    ERR("unsupported IO read : %x", port);
    return 0;
}
