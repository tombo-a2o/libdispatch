CC=a2o
CFLAGS=-s NATIVE_LIBDISPATCH=1 -fobjc-arc -D__IPHONE_OS_VERSION_MIN_REQUIRED=70000

all:	async.js async.ll async.txt

async.js:	async.m

%.txt: %.m
	$(CC) -E $(CFLAGS) -o $@ $<

%.ll: %.m
	$(CC) -emit-llvm -S $(CFLAGS) -o $@ $<

%.js: %.m
	$(CC) $(CFLAGS) -o $@ $<
