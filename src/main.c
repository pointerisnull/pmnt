#include <stdio.h>
#include <string.h>
#include "./core/cmd_handler.h"
#include "./core/crypto.h"

int main(int argc, char **argv) {
	if (argc > 1) {
		size_t len = strlen(argv[1]);
		printf("String Input: %s\tBytes: %d\n", argv[1], len);
		crc16_t crc = crc16((byte_t *) argv[1], len);
		printf("CRC16: %x\n", crc);


		*argv[1] = 0xFF; // Corrupt a byte
		if (validate_crc((byte_t *)argv[1], len, crc))
			printf("CRC Validated!\n");
		else
			printf("CRC values do not match, data must be corrupt!\n");
	}


	return 0;
}
