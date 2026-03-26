#ifndef CRYPTO_H
#define CRYPTO_H

#include "../misc/typedefs.h"

hash64_t str_to_bin(char *str);
char *bin_to_str(hash64_t bin);

#endif
