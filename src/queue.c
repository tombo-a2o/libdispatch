#include "internal.h"
#include <emscripten.h>

void dispatch_async(dispatch_queue_t queue, void (^block)(void)) {
    dispatch_async_f(queue, _dispatch_Block_copy(block), _dispatch_call_block_and_release);
}

void dispatch_sync(dispatch_queue_t queue, dispatch_block_t block) {
    dispatch_sync_f(queue, _dispatch_Block_copy(block), _dispatch_call_block_and_release);
}

dispatch_queue_t dispatch_get_global_queue(dispatch_queue_priority_t priority, unsigned long flags) {
    dispatch_queue_t queue;
    switch(priority) {
    case DISPATCH_QUEUE_PRIORITY_HIGH:
        queue = 2;
        break;
    case DISPATCH_QUEUE_PRIORITY_DEFAULT:
        queue = 4;
        break;
    case DISPATCH_QUEUE_PRIORITY_LOW:
        queue = 6;
        break;
    case DISPATCH_QUEUE_PRIORITY_BACKGROUND:
        queue = 8;
        break;
    default:
        assert(0);
    }
    queue += flags != 0 ? 1 : 0;
    return queue;
}

extern void _dispatch_em_handle_queue(void);

void dispatch_main(void) {
    emscripten_set_main_loop(_dispatch_em_handle_queue, 0, true);
}

void dispatch_after(dispatch_time_t when, dispatch_queue_t queue, dispatch_block_t block) {
    if (when == DISPATCH_TIME_FOREVER) {
        return;
    }
    dispatch_after_f(when, queue, _dispatch_Block_copy(block), _dispatch_call_block_and_release);
}

void dispatch_barrier_async(dispatch_queue_t queue, void (^block)(void)) {
    dispatch_barrier_async_f(queue, _dispatch_Block_copy(block), _dispatch_call_block_and_release);
}

void * dispatch_get_specific(const void *key) {
    dispatch_queue_get_specific(dispatch_get_current_queue(), key);
}
        
// Implemented by js native
// dispatch_async_f
// dispatch_sync_f
// dispatch_get_current_queue
// dispatch_queue_create
// dispatch_queue_get_label
// dispatch_set_target_queue
// dispatch_after_f
// dispatch_barrier_async_f
// dispatch_get_specific
// dispatch_set_specific
