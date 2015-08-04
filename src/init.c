#include "internal.h"

#undef _dispatch_Block_copy
dispatch_block_t _dispatch_Block_copy(dispatch_block_t db)
{
    dispatch_block_t rval;
    
    assert(db);
    rval = Block_copy(db);
    assert(rval);

    return rval;
}

void _dispatch_call_block_and_release(void *block)
{
    void (^b)(void) = block;
    b();
    Block_release(b);
}
