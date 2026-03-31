#ifndef OP_CODE_H
#define OP_CODE_H

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

enum OPCODE {
	HELP,
	RUN_SERVER,
	LIST,
	GEN_TREE,
	NEW,
	POP,
	PRUNE,
	UPDATE	  
};

#endif
