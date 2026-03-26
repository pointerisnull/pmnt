#include "cmd_handler.h"
#include "cmd_code.h"

#include <string.h>
#include <stdlib.h>

cmdcode_t get_cmd(char *arg) {
	cmdcode_t code = strtol(arg, NULL, 16);
	return code;

}
