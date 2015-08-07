#include "internal.h"

@implementation DispatchQueue @end

void dispatch_async(dispatch_queue_t queue, void (^block)(void)) {
    dispatch_async_f(queue, _dispatch_Block_copy(block), _dispatch_call_block_and_release);
}

void dispatch_sync(dispatch_queue_t queue, dispatch_block_t block) {
    dispatch_sync_f(queue, _dispatch_Block_copy(block), _dispatch_call_block_and_release);
}

extern struct objc_class OBJC_CLASS_$_NSObject;

struct dispatch_queue_s _dispatch_main_q = {
    .isa = &OBJC_CLASS_$_NSObject, // TODO
    .queue_id = 0,
};
struct dispatch_queue_s background_queue = {
    .isa = &OBJC_CLASS_$_NSObject, // TODO
    .queue_id = 1,
};

extern uint32_t _dispatch_get_current_queue_id(void);

dispatch_queue_t dispatch_get_current_queue(void) {
    uint32_t queue_id = _dispatch_get_current_queue_id();
    switch(queue_id) {
    case 0:
        return (dispatch_queue_t)&_dispatch_main_q;
        break;
    case 1:
        return (dispatch_queue_t)&background_queue;
        break;
    default:
        assert(0);
    }
}

dispatch_queue_t dispatch_get_global_queue(dispatch_queue_priority_t priority, unsigned long flags) {
    assert(flags == 0);
    switch(priority) {
    case DISPATCH_QUEUE_PRIORITY_HIGH:
    case DISPATCH_QUEUE_PRIORITY_DEFAULT:
    case DISPATCH_QUEUE_PRIORITY_LOW:
    case DISPATCH_QUEUE_PRIORITY_BACKGROUND:
        return (dispatch_queue_t)&background_queue;
    default:
        assert(0);
    }
}
uint32_t _dispatch_queue_create_internal(const char *label);

dispatch_queue_t dispatch_queue_create(const char *label, dispatch_queue_attr_t attr) {
    // ignore attr
    DispatchQueue *queue = [[DispatchQueue alloc] init];
    queue->queue_id = _dispatch_queue_create_internal(label);
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
    return dispatch_queue_get_specific(dispatch_get_current_queue(), key);
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
