#include "crypto.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

hash64_t str_to_bin(char *str) {
	hash64_t code = (hash64_t) strtol(str, NULL, 16);
	return code;
}