#include <dispatch/dispatch.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        printf("hoge\n");
    });
    printf("fuga\n");
    dispatch_main();
}
