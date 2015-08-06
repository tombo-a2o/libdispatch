/*
 * Copyright (c) 2008-2013 Apple Inc. All rights reserved.
 *
 * @APPLE_APACHE_LICENSE_HEADER_START@
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @APPLE_APACHE_LICENSE_HEADER_END@
 */

#include "internal.h"

uint64_t _dispatch_get_nanoseconds(void)
{
	struct timeval now;
	int r = gettimeofday(&now, NULL);
	assert(r == 0);
	assert(sizeof(NSEC_PER_SEC) == 8);
	assert(sizeof(NSEC_PER_USEC) == 8);
	return (uint64_t)now.tv_sec * NSEC_PER_SEC +
			(uint64_t)now.tv_usec * NSEC_PER_USEC;
}

dispatch_time_t dispatch_time(dispatch_time_t inval, int64_t delta)
{
	uint64_t offset;
	if (inval == DISPATCH_TIME_FOREVER) {
		return DISPATCH_TIME_FOREVER;
	}
	if ((int64_t)inval < 0) {
		// wall clock
		if (delta >= 0) {
			offset = (uint64_t)delta;
			if ((int64_t)(inval -= offset) >= 0) {
				return DISPATCH_TIME_FOREVER; // overflow
			}
			return inval;
		} else {
			offset = (uint64_t)-delta;
			if ((int64_t)(inval += offset) >= -1) {
				// -1 is special == DISPATCH_TIME_FOREVER == forever
				return (dispatch_time_t)-2ll; // underflow
			}
			return inval;
		}
	}
	// mach clock
	if (inval == 0) {
		inval = _dispatch_absolute_time();
	}
	if (delta >= 0) {
		offset = _dispatch_time_nano2mach((uint64_t)delta);
		if ((int64_t)(inval += offset) <= 0) {
			return DISPATCH_TIME_FOREVER; // overflow
		}
		return inval;
	} else {
		offset = _dispatch_time_nano2mach((uint64_t)-delta);
		if ((int64_t)(inval -= offset) < 1) {
			return 1; // underflow
		}
		return inval;
	}
}

dispatch_time_t
dispatch_walltime(const struct timespec *inval, int64_t delta)
{
	int64_t nsec;
	if (inval) {
		nsec = inval->tv_sec * 1000000000ll + inval->tv_nsec;
	} else {
		nsec = (int64_t)_dispatch_get_nanoseconds();
	}
	nsec += delta;
	if (nsec <= 1) {
		// -1 is special == DISPATCH_TIME_FOREVER == forever
		return delta >= 0 ? DISPATCH_TIME_FOREVER : (dispatch_time_t)-2ll;
	}
	return (dispatch_time_t)-nsec;
}

uint64_t
_dispatch_timeout(dispatch_time_t when)
{
	dispatch_time_t now;
	if (when == DISPATCH_TIME_FOREVER) {
		return DISPATCH_TIME_FOREVER;
	}
	if (when == 0) {
		return 0;
	}
	if ((int64_t)when < 0) {
		when = (dispatch_time_t)-(int64_t)when;
		now = _dispatch_get_nanoseconds();
		return now >= when ? 0 : when - now;
	}
	now = _dispatch_absolute_time();
	return now >= when ? 0 : _dispatch_time_mach2nano(when - now);
}
