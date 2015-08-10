#include <dispatch/dispatch.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    __block int i = 100;
    dispatch_async(dispatch_get_main_queue(), ^{
        printf("hoge %d\n", i);
    });
    printf("fuga\n");
    dispatch_main();
}
