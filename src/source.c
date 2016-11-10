#include "internal.h"

@implementation DispatchSource @end

#define SOURCE_INTERNAL_TYPE_TIMER 1

const struct dispatch_source_type_s _dispatch_source_type_timer = {
    .isa = NULL, // TODO
    .internal_type = SOURCE_INTERNAL_TYPE_TIMER
};

const struct dispatch_source_type_s _dispatch_source_type_read = {
    .isa = NULL, // TODO
    .internal_type = 0
};

const struct dispatch_source_type_s _dispatch_source_type_write = {
    .isa = NULL, // TODO
    .internal_type = 0
};

uint32_t _dispatch_source_create_internal(uint32_t internal_type, uintptr_t handle, unsigned long mask, dispatch_queue_t queue);

dispatch_source_t dispatch_source_create(dispatch_source_type_t type, uintptr_t handle, unsigned long mask, dispatch_queue_t queue) {
    uint32_t internal_type;
    if(type == DISPATCH_SOURCE_TYPE_TIMER) {
        internal_type = SOURCE_INTERNAL_TYPE_TIMER;
    } else {
        // unimplemented
        assert(0);
    }
    DispatchSource *source = [[DispatchSource alloc] init];
    source->object_id = _dispatch_source_create_internal(internal_type, handle, mask, queue);
    return source;
}

//void dispatch_source_set_timer(dispatch_source_t source, dispatch_time_t start, uint64_t interval, uint64_t leeway)


void _dispatch_call_block(void *block)
{
    void (^b)(void) = block;
    b();
}

void _dispatch_release_block(void *block)
{
    Block_release(block);
}

void _dispatch_source_set_event_handler_internal(dispatch_source_t source, void *context, dispatch_function_t work, dispatch_function_t dtor);

void dispatch_source_set_event_handler_f(dispatch_source_t source, dispatch_function_t handler) {
    _dispatch_source_set_event_handler_internal(source, NULL, handler, NULL);
}

void dispatch_source_set_event_handler(dispatch_source_t source, dispatch_block_t handler) {
    _dispatch_source_set_event_handler_internal(source, _dispatch_Block_copy(handler), _dispatch_call_block, _dispatch_release_block);
}

void _dispatch_source_set_cancel_handler_internal(dispatch_source_t source, void *context, dispatch_function_t work, dispatch_function_t dtor);

void dispatch_source_set_cancel_handler_f(dispatch_source_t source, dispatch_function_t handler) {
    _dispatch_source_set_cancel_handler_internal(source, NULL, handler, NULL);
}
void dispatch_source_set_cancel_handler(dispatch_source_t source, dispatch_block_t handler) {
    _dispatch_source_set_cancel_handler_internal(source, _dispatch_Block_copy(handler), _dispatch_call_block, _dispatch_release_block);
}

long dispatch_source_testcancel(dispatch_source_t source) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
    return 0;
}
uintptr_t dispatch_source_get_handle(dispatch_source_t source) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
    return 0;
}
unsigned long dispatch_source_get_mask(dispatch_source_t source) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
    return 0;
}
unsigned long dispatch_source_get_data(dispatch_source_t source) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
    return 0;
}
