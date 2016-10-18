#include "internal.h"

struct dispatch_data_s _dispatch_data_empty;

dispatch_data_t dispatch_data_create(const void *buffer, size_t size, dispatch_queue_t queue, dispatch_block_t destructor) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
    return 0;
}

size_t dispatch_data_get_size(dispatch_data_t data) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
    return 0;
}

dispatch_data_t dispatch_data_create_map(dispatch_data_t data, const void **buffer_ptr, size_t *size_ptr) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
    return 0;
}

dispatch_data_t dispatch_data_create_concat(dispatch_data_t data1, dispatch_data_t data2) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
    return 0;
}

dispatch_data_t dispatch_data_create_subrange(dispatch_data_t data, size_t offset, size_t length) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
    return 0;
}

bool dispatch_data_apply(dispatch_data_t data, dispatch_data_applier_t applier) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
    return 0;
}

dispatch_data_t dispatch_data_copy_region(dispatch_data_t data, size_t location, size_t *offset_ptr) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
    return 0;
}
