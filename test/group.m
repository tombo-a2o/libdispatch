#include <dispatch/dispatch.h>
#include <stdio.h>
#include <stdlib.h>
#include <Foundation/Foundation.h>

int main(int argc, char* argv[]) {
    dispatch_queue_t queue =
        dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    dispatch_queue_t queue2 =
        dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0);
    dispatch_group_t group = dispatch_group_create();
    dispatch_group_async(group, queue, ^{NSLog(@"blk0");});
    dispatch_group_async(group, queue2, ^{NSLog(@"blk1");});
    dispatch_group_notify(group, queue, ^{NSLog(@"done");});
    dispatch_group_async(group, dispatch_get_main_queue(), ^{NSLog(@"blk2");});
    sleep(3);
    dispatch_group_notify(group, dispatch_get_main_queue(), ^{NSLog(@"done2");});

    dispatch_main();
}
