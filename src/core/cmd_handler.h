#ifndef CMD_H
#define CMD_H

#include "../misc/typedefs.h"

cmdcode_t get_cmd(char *arg);
void handle_cmd(int cmd);


#endif
