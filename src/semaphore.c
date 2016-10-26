#include "internal.h"

dispatch_semaphore_t dispatch_semaphore_create(long value)
{
    printf("*** %s is not implemented.\n", __FUNCTION__);
    return 0;
}

long dispatch_semaphore_wait(dispatch_semaphore_t dsema, dispatch_time_t timeout)
{
    printf("*** %s is not implemented.\n", __FUNCTION__);
    return 0;
}

long dispatch_semaphore_signal(dispatch_semaphore_t dsema)
{
    printf("*** %s is not implemented.\n", __FUNCTION__);
    return 0;
}
