#include <Availability.h>
#include <TargetConditionals.h>
#include <Block.h>
#include <Block_private.h>
#include <sys/cdefs.h>
#include <stdarg.h>
#include <stddef.h>
#include <sys/types.h>
#include <assert.h>
#include <emscripten.h>
#include <malloc/malloc.h>

#define __DISPATCH_BUILDING_DISPATCH__
#define __DISPATCH_INDIRECT__

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

struct dispatch_queue_s {
    uint32_t queue_id;
};

