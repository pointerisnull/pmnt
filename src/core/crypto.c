#include "crypto.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

hash64_t str_to_bin(char *str) {
	hash64_t code = (hash64_t) strtol(str, NULL, 16);
	return code;
}

crc16_t crc16(byte_t *data, size_t length) {
	const crc16_t POLY = 0x8005;
	const crc16_t INITIAL_VALUE = 0xFFFF;

    crc16_t crc = INITIAL_VALUE;
    for (size_t i = 0; i < length; ++i) {
        uint8_t index = (uint8_t)(crc ^ data[i]);
        crc = (uint16_t)((crc >> 8) ^ crc_table[index]);
    }
    return crc;
}

crc16_t validate_crc(byte_t *data, size_t length, crc16_t crc) {
	const crc16_t SHIFTMASK = 0x00FF;

    for(int i = 0; i < length; i++) {
        crc16_t table_value = crc_table[((crc >> 8) ^ *(byte_t*)data++) & SHIFTMASK];
        crc = (crc << 8) ^ table_value;
    }
	return crc;
}