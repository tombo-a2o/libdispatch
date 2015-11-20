#include "internal.h"
#include <emscripten/trace.h>

@implementation DispatchQueue @end

void dispatch_async(dispatch_queue_t queue, void (^block)(void)) {
    dispatch_async_f(queue, _dispatch_Block_copy(block), _dispatch_call_block_and_release);
}

void dispatch_sync(dispatch_queue_t queue, dispatch_block_t block) {
    dispatch_sync_f(queue, _dispatch_Block_copy(block), _dispatch_call_block_and_release);
}

void _dispatch_apply_block_call(void *block, size_t i) {
    void (^b)(size_t) = block;
    b(i);
}

void dispatch_apply(size_t iterations, dispatch_queue_t queue, void (^block)(size_t)) {
    Block_copy(block);
    dispatch_apply_f(iterations, queue, block, _dispatch_apply_block_call);
    Block_release(block);
}

extern struct objc_class OBJC_CLASS_$_DispatchQueue;

struct dispatch_queue_s _dispatch_main_q = {
    .isa = &OBJC_CLASS_$_DispatchQueue, // TODO
    .object_id = 0,
};
struct dispatch_queue_s background_queue = {
    .isa = &OBJC_CLASS_$_DispatchQueue, // TODO
    .object_id = 1,
};

#define QUEUE_MAX 1024
static dispatch_queue_t _queue_table[QUEUE_MAX] = {&_dispatch_main_q, &background_queue};

extern uint32_t _dispatch_get_current_queue_id(void);

dispatch_queue_t dispatch_get_current_queue(void) {
    uint32_t queue_id = _dispatch_get_current_queue_id();
    return _queue_table[queue_id];
}

dispatch_queue_t dispatch_get_global_queue(dispatch_queue_priority_t priority, unsigned long flags) {
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
    queue->object_id = _dispatch_queue_create_internal(label);
    _queue_table[queue->object_id] = queue;
    return queue;
}

extern void _dispatch_em_handle_queue(void);
static void _dispatch_em_handle_queue_with_autoreleasepool(void) {
    emscripten_trace_record_frame_start();
    @autoreleasepool {
        _dispatch_em_handle_queue();
    }
    emscripten_trace_record_frame_end();
#if defined(__EMSCRIPTEN_TRACING__)
    static unsigned int frames = 0;
    if(frames % 100 == 0) {
        emscripten_trace_report_memory_layout();
    }
    frames++;
#endif
}

void dispatch_main(void) {
    emscripten_set_main_loop(_dispatch_em_handle_queue_with_autoreleasepool, 0, true);
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

void dispatch_barrier_sync(dispatch_queue_t queue, void (^block)(void)) {
    dispatch_barrier_sync_f(queue, _dispatch_Block_copy(block), _dispatch_call_block_and_release);
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
