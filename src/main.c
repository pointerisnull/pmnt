#include <stdio.h>
#include "./core/cmd_handler.h"
#include "./core/crypto.h"

int main(int argc, char **argv) {
	printf("Hello World\n");
	
	if (argc > 1) {
		uint64_t code = str_to_bin(argv[1]);
		printf("Hex input: %s\n", argv[1]);
		printf("Result: %llx\n", code);
	}


	return 0;
}
