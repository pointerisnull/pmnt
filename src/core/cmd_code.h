#ifndef CMD_CODE_H
#define CMD_CODE_H

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

enum CMDCODE {
	RUN_SERVER	= 0x0,
	HELP		= 0x1,
	LIST		= 0x2,
	GEN_TREE	= 0x3,
	NEW			= 0x4,
	POP			= 0x5,
	PRUNE		= 0x6,
	UPDATE		= 0x7
	
};

#endif
