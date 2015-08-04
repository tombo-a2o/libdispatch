CC=emcc
CFLAGS=-lBlocksRuntime -ldispatch -fblocks -s NATIVE_LIBDISPATCH=1

async.js:	async.c

once.js:	once.c

%.js: %.c
	$(CC) $(CFLAGS) -o $@ $<
