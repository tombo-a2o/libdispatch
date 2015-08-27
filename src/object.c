#include "internal.h"

@implementation DispatchObject
-(void)dealloc {
    if(_finalizer) {
        _finalizer(_context);
    }
    [super dealloc];
}
@end

void dispatch_retain(dispatch_object_t object) {
    [object retain];
}

void dispatch_release(dispatch_object_t object) {
    [object release];
}

extern void _dispatch_source_suspend(dispatch_object_t source);

void dispatch_suspend(dispatch_object_t object) {
    if([object isKindOfClass:[DispatchSource class]]) {
        _dispatch_source_suspend(object);
    }
}

extern void _dispatch_source_resume(dispatch_object_t source);

void dispatch_resume(dispatch_object_t object) {
    if([object isKindOfClass:[DispatchSource class]]) {
        _dispatch_source_resume(object);
    }
}

void dispatch_set_context(dispatch_object_t object, void *context) {
    DispatchObject *obj = (DispatchObject*)object;
    obj->_context = context;
}

void dispatch_set_finalizer_f(dispatch_object_t object, dispatch_function_t finalizer) {
    DispatchObject *obj = (DispatchObject*)object;
    obj->_finalizer = finalizer;
}
