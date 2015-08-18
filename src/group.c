#include "internal.h"

@implementation DispatchGroup @end

uint32_t _dispatch_group_create_internal(void);

dispatch_group_t dispatch_group_create(void) {
    DispatchGroup *group = [[DispatchGroup alloc] init];
    group->group_id = _dispatch_group_create_internal();
    return group;
}

void dispatch_group_async(dispatch_group_t group, dispatch_queue_t queue, dispatch_block_t block) {
    dispatch_group_async_f(group, queue, _dispatch_Block_copy(block), _dispatch_call_block_and_release);
}

void dispatch_group_notify(dispatch_group_t group, dispatch_queue_t queue, dispatch_block_t block) {
    dispatch_group_notify_f(group, queue, _dispatch_Block_copy(block), _dispatch_call_block_and_release);
}


// void dispatch_group_async_f(dispatch_group_t group, dispatch_queue_t queue, void *context, dispatch_function_t work);
// long dispatch_group_wait(dispatch_group_t group, dispatch_time_t timeout);
// void dispatch_group_notify_f(dispatch_group_t group, dispatch_queue_t queue, void *context, dispatch_function_t work);
// void dispatch_group_enter(dispatch_group_t group);
// void dispatch_group_leave(dispatch_group_t group);
