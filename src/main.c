#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "./misc/bitset.h"
#include "./core/cmd_handler.h"
#include "./core/op_code.h"

int main(int argc, char **argv) {
	bitset_t opts;
	unsigned int port = 0;
		/* 
		 * COMMANDS:			ARGS:
		 *	--help, -h	
		 *	--server, -s		-p (port)
		 *	--list, -l			(tree hash)
		 *	--gen-tree, -g		(title)
		 *	--new, -n			(tree hash) (parent hash) -t (title) -f (tags)
		 *	--pop, -d			(tree hash) (node hash)
		 *	--prune, -p			(tree hash) (node hash)
		 *	--update, -u		(tree hash) (node hash) -t (title) -f (tags)
		 */
	char *flags = "hs:l:g:n:d:p:u:";
	int opt = 0;
	while ((opt = getopt(argc, argv, flags)) != -1) {
        switch (opt) {
            case 'h':
				printf("Help:\n");
                set_bit(&opts, HELP);
				goto opt_escape;
            case 's':
				port = atoi(optarg);
                set_bit(&opts, RUN_SERVER);
				goto opt_escape;
                break;
            case 'l':
				printf("Listing tree %s:\n", optarg);
                set_bit(&opts, LIST);
                break;
            case 'g':
                set_bit(&opts, GEN_TREE);
                break;
            case 'n':
                set_bit(&opts, NEW);
                break;
            case 'd':
                set_bit(&opts, POP);
                break;
            case 'p':
                set_bit(&opts, PRUNE);
                break;
            case 'u':
                set_bit(&opts, UPDATE);
                break;
			case '?': // Unknown option, escape and show help menu
				printf("Unknown option: %c\n", opt);
				opts = 0x0;
                set_bit(&opts, HELP);
				goto opt_escape;
        };
    }

	opt_escape:
	
	// If we are a server, run the server loop. Else, handle client commands.
	if (get_bit(opts, RUN_SERVER))
		host_server(port);


	return 0;
}
