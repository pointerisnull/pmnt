#include "modbus.h"
#include "../core/crypto.h"

#include <stdlib.h>
#include <string.h>

static const mb_pdu err_pdu = {0xFF, 0xFFFF};

mb_pdu assemble_pdu(byte_t func_code, word_t reg_addr, byte_t *data, size_t size) {
    mb_pdu pdu;
    pdu.func_code = func_code;
    pdu.reg_addr = reg_addr;
    memcpy(&pdu.data, data, size);
    pdu.data_size = size;
    return pdu;
}

mb_pdu gen_pdu(byte_t *data, size_t size) {
    if (size < 3)
        return err_pdu;

    mb_pdu pdu;
    pdu.func_code = data[0];
    pdu.reg_addr = (data[1] << 8) | data[2];
    byte_t *dataptr = &data[3];
    memcpy(&pdu.data, dataptr, size-3);
    pdu.data_size = size-3;
    
    return pdu;
}

size_t compile_pdu(mb_pdu *pdu, byte_t *data) {
    size_t size = pdu->data_size+3;
    if (size < 3)
        return size;

    memcpy(data, pdu->data, pdu->data_size);
    return size;
}

crc16_t gen_crc(byte_t address, mb_pdu *pdu) {
    // Generate byte array
    int size = pdu->data_size+2;
    byte_t array[size];
    array[0] = address;                 // Address
    array[1] = pdu->func_code;          // Function Code
    array[2] = pdu->reg_addr >> 8;      // Register Address (Top Byte)
    array[3] = pdu->reg_addr & 0xFF;    // Register Address (Bottom Byte)
    byte_t *array_offset = &array[4];
    memcpy(array_offset, pdu->data, pdu->data_size);

    // Perform crc16 calculation
    crc16_t result = crc16((byte_t *) &array, size);

    return result;
}

struct mb_frame assemble_frame(byte_t address, mb_pdu *pdu) {
    struct mb_frame frame;
    frame.address = address;
    frame.pdu = *pdu;
    frame.crc = gen_crc(address, pdu);
    
    return frame;
}