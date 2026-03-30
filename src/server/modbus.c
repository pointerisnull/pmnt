#include "modbus.h"
#include "../core/crypto.h"

#include <stdlib.h>
#include <string.h>

mb_pdu gen_pdu(byte_t func_code, byte_t *data, size_t size) {
    mb_pdu pdu;
    pdu.function_code = func_code;
    memcpy(&pdu.data, data, size);
    pdu.data_size = size;
    return pdu;
}

crc16_t gen_crc(byte_t address, mb_pdu *pdu) {
    // Generate byte array
    int size = pdu->data_size+2;
    byte_t array[size];
    array[0] = address;                 // Address
    array[1] = pdu->function_code;      // Function Code
    byte_t *array_offset = &array[2];
    memcpy(array_offset, pdu->data, pdu->data_size);

    // Perform crc16 calculation
    crc16_t result = crc16((byte_t *) &array, size);

    return result;
}