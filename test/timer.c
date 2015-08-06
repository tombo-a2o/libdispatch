#include <dispatch/dispatch.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    dispatch_source_t timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0));
    __block int i = 0;
    dispatch_source_set_event_handler(timer, ^{
        printf("%d\n", i);
        i++;
        //printf("%d\n", timer);
        if (i == 10) dispatch_source_cancel(timer);
    });
    dispatch_source_set_cancel_handler(timer, ^{
        dispatch_release(timer);
        printf("end\n");
        exit(0);
    });
    dispatch_time_t start = dispatch_time(DISPATCH_TIME_NOW, NSEC_PER_SEC*2);
    uint64_t interval = NSEC_PER_SEC/5;
    dispatch_source_set_timer(timer, start, interval, 0);
    printf("start\n");
    dispatch_resume(timer);
    dispatch_main();
}
