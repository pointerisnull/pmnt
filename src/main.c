#include <stdio.h>
#include <string.h>
#include "./core/cmd_handler.h"
#include "./core/crypto.h"

int main(int argc, char **argv) {
	if (argc > 1) {
		size_t len = strlen(argv[1]);
		printf("String Input: %s\n", argv[1]);
		printf("CRC16: %x\n", crc16((byte_t *) argv[1], len));
	}


	return 0;
}
