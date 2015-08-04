#include <dispatch/dispatch.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int i;
    static dispatch_once_t x;
    for(i = 0; i < 5; i++) {
        dispatch_once(&x, ^{
           printf("Hello dispatch\n");
        });
    }
}
