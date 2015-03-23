How to build on emscripten

autoreconf -i
emconfigure ./configure
make -f Makefile.dummy install

Foundation and CoreFoundation need only dispatch_once, so you don't need to build all files, which will fail.
