CC=emcc
CFLAGS=-lBlocksRuntime -ldispatch -fblocks

async.js:	async.c

once.js:	once.c

%.js: %.c
	$(CC) $(CFLAGS) -o $@ $<
