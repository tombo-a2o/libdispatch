CC=a2o
CFLAGS=-s NATIVE_LIBDISPATCH=1 -fobjc-arc -D__IPHONE_OS_VERSION_MIN_REQUIRED=70000

all:	group.js group.ll group.txt group

group.js:	group.m
async.js:	async.m

%: %.m
	clang -fobjc-arc -framework Foundation -fobjc-runtime=macosx -o $@ $<

%.txt: %.m
	$(CC) -E $(CFLAGS) -o $@ $<

%.ll: %.m
	$(CC) -emit-llvm -S $(CFLAGS) -o $@ $<

%.js: %.m
	$(CC) $(CFLAGS) -o $@ $<
