#include <Availability.h>
#include <TargetConditionals.h>
#include <Block.h>
#include <Block_private.h>
#include <sys/cdefs.h>
#include <stdarg.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <assert.h>
#include <emscripten.h>
#include <malloc/malloc.h>

#define __DISPATCH_BUILDING_DISPATCH__
#define __DISPATCH_INDIRECT__
#define OS_OBJECT_HAVE_OBJC_SUPPORT 1
#define OS_OBJECT_USE_OBJC 1

#include <os/object.h>

#include <dispatch/base.h>
#include <dispatch/time.h>
#include <dispatch/object.h>
#include <dispatch/queue.h>
#include <dispatch/source.h>
#include <dispatch/group.h>
#include <dispatch/semaphore.h>
#include <dispatch/once.h>
#include <dispatch/data.h>
#include <dispatch/io.h>

#define _dispatch_Block_invoke(bb) ((dispatch_function_t)((struct Block_layout *)bb)->invoke)

dispatch_block_t _dispatch_Block_copy(dispatch_block_t block);
#define _dispatch_Block_copy(x) ((typeof(x))_dispatch_Block_copy(x))
void _dispatch_call_block_and_release(void *block);

static inline uint64_t _dispatch_time_mach2nano(uint64_t machtime)
{
    return machtime;
}

static inline uint64_t _dispatch_time_nano2mach(uint64_t nsec)
{
    return nsec;
}

static inline uint64_t _dispatch_absolute_time(void)
{
    struct timespec ts;
    int ret;
    ret = clock_gettime(CLOCK_MONOTONIC, &ts);
    assert(!ret);
    return (ts.tv_sec * NSEC_PER_SEC + ts.tv_nsec);
}

@interface DispatchObject : NSObject<OS_dispatch_object> {
    @public
    uint32_t object_id;
    uint32_t suspend_cnt;
    void *_context;
    dispatch_function_t _finalizer;
}
-(void)dealloc;
@end

@interface DispatchQueue : DispatchObject<OS_dispatch_queue> @end

struct dispatch_queue_s {
    id isa;
    uint32_t object_id;
    uint32_t suspend_cnt;
};

@interface DispatchSource : DispatchObject<OS_dispatch_source> @end

struct dispatch_source_s {
    id isa;
    uint32_t object_id;
    uint32_t suspend_cnt;
};

struct dispatch_source_type_s {
    id isa;
    uint32_t internal_type;
};

@interface DispatchGroup : DispatchObject<OS_dispatch_group> @end

struct dispatch_group_s {
    id isa;
    uint32_t object_id;
    uint32_t suspend_cnt;
};

struct dispatch_queue_attr_s {
    id isa;
};

struct dispatch_data_s {
    id isa;
};
