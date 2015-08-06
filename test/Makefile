CC=emcc
CFLAGS=-lBlocksRuntime -ldispatch -fblocks -s NATIVE_LIBDISPATCH=1

timer.js:	timer.c

async.js:	async.c

once.js:	once.c

%.js: %.c
	$(CC) $(CFLAGS) -o $@ $<
