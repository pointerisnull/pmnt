#include "crypto.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

hash64_t str_to_bin(char *str) {
	hash64_t code = (hash64_t) strtol(str, NULL, 16);
	return code;
}

crc16_t crc16(byte_t *data, size_t length) {
	crc16_t crc = 0xFFFF;

    for (size_t i = 0; i < length; i++) {
        int table_index = (byte_t)(crc ^ data[i]);
        crc = (crc >> 8) ^ crc_table[table_index];
    }

    return crc;
}

bool validate_crc(byte_t *data, size_t length, crc16_t crc) {
    crc16_t data_crc = crc16(data, length);
    if (crc == data_crc)
        return true;
    return false;
}