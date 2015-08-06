#include <dispatch/dispatch.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    __block int i = 100;
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        printf("hoge %d\n", i);
    });
    printf("fuga\n");
    dispatch_main();
}
