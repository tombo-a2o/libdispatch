SOURCES = $(wildcard src/*.c)
PRIVATE_HEADERS = $(wildcard private-include/*.h)
PUBLIC_HEADERS = $(wildcard include/**/*.h)
HEADERS = $(PUBLIC_HEADERS) $(PRIVATE_HEADERS)

BUILD = build

STATIC_LIB = $(BUILD)/libdispatch.a
LIB = $(BUILD)/libdispatch.bc
OBJS = $(patsubst src/%, $(BUILD)/%, $(patsubst %.c,%.o,$(SOURCES)))

CC = emcc
CXX = em++
LINK = emar
CFLAGS = -O0 -I./include -I./private-include -I./src -fblocks -x objective-c -fobjc-runtime=ios

.SUFFIXES: .c .o

all: $(STATIC_LIB)

vpath %.c src

$(BUILD)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

$(LIB): $(HEADERS) $(OBJS)
	llvm-link -o $@ $(OBJS)

$(STATIC_LIB): $(LIB)
	rm -f $@
	$(LINK) rcs $@ $<

clean:
	rm -f $(LIB) $(STATIC_LIB) $(OBJS)

install: $(STATIC_LIB)
	cp $(STATIC_LIB) $(EMSCRIPTEN)/system/local/lib/
	mkdir -p $(EMSCRIPTEN)/system/local/include/dispatch
	cp $(PUBLIC_HEADERS) $(EMSCRIPTEN)/system/local/include/dispatch/

.PHONY: all clean install
