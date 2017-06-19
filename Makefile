SOURCES = $(wildcard src/*.c)
PRIVATE_HEADERS = $(wildcard src/*.h)
PUBLIC_HEADERS = $(wildcard include/**/*.h)
HEADERS = $(PUBLIC_HEADERS) $(PRIVATE_HEADERS)
MODULE_MAP = module.modulemap

BUILD ?= build/debug

STATIC_LIB = $(BUILD)/libdispatch.a
LIB = $(BUILD)/libdispatch.bc
OBJS = $(patsubst src/%, $(BUILD)/%, $(patsubst %.c,%.o,$(SOURCES)))

CC = emcc
CXX = em++
LINK = emar
CFLAGS = -O0 -I./include -I./private-include -I./src -fblocks -x objective-c -D__IPHONE_OS_VERSION_MIN_REQUIRED=70000 $(OPT_CFLAGS)

.SUFFIXES: .c .o

all: $(STATIC_LIB)

vpath %.c src

$(BUILD)/%.o: %.c $(HEADERS)
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
	cp $(MODULE_MAP) $(EMSCRIPTEN)/system/local/include/dispatch/

.PHONY: all clean install
