#include "internal.h"

#undef dispatch_once
#undef dispatch_once_f


void dispatch_once(dispatch_once_t *val, dispatch_block_t block)
{
    dispatch_once_f(val, block, _dispatch_Block_invoke(block));
}

void dispatch_once_f(dispatch_once_t *val, void *ctxt, dispatch_function_t func)
{
    if(*val == 0) {
        func(ctxt);
        *val = ~0L;
    }
}
