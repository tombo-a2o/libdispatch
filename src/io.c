#include "internal.h"

void dispatch_read(dispatch_fd_t fd, size_t length, dispatch_queue_t queue, void (^handler)(dispatch_data_t data, int error)) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
}

void dispatch_write(dispatch_fd_t fd, dispatch_data_t data, dispatch_queue_t queue, void (^handler)(dispatch_data_t data, int error)) {  
    printf("*** %s is not implemented.\n", __FUNCTION__);
}

dispatch_io_t dispatch_io_create(dispatch_io_type_t type, dispatch_fd_t fd, dispatch_queue_t queue, void (^cleanup_handler)(int error)) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
    return 0;
}

dispatch_io_t dispatch_io_create_with_path(dispatch_io_type_t type, const char *path, int oflag,
    mode_t mode, dispatch_queue_t queue, void (^cleanup_handler)(int error)) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
    return 0;
}

dispatch_io_t dispatch_io_create_with_io(dispatch_io_type_t type,
	dispatch_io_t io, dispatch_queue_t queue, void (^cleanup_handler)(int error)) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
    return 0;
}
    
void dispatch_io_read(dispatch_io_t channel, off_t offset, size_t length, dispatch_queue_t queue, dispatch_io_handler_t io_handler) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
}

void dispatch_io_write(dispatch_io_t channel, off_t offset, dispatch_data_t data, dispatch_queue_t queue, dispatch_io_handler_t io_handler) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
}

void dispatch_io_close(dispatch_io_t channel, dispatch_io_close_flags_t flags) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
}

void dispatch_io_barrier(dispatch_io_t channel, dispatch_block_t barrier) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
}

dispatch_fd_t dispatch_io_get_descriptor(dispatch_io_t channel) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
    return 0;
}

void dispatch_io_set_high_water(dispatch_io_t channel, size_t high_water) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
}

void dispatch_io_set_low_water(dispatch_io_t channel, size_t low_water) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
}

void dispatch_io_set_interval(dispatch_io_t channel, uint64_t interval, dispatch_io_interval_flags_t flags) {
    printf("*** %s is not implemented.\n", __FUNCTION__);
}
