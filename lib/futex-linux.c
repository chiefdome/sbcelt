// Copyright (C) 2012 The SBCELT Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE-file.

#include <linux/futex.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <unistd.h>

#include "futex.h"

int futex_available() {
	return 1;
}

int futex_wake(int *futex) {
	return syscall(SYS_futex, futex, FUTEX_WAKE, 1, NULL, NULL, 0);
}

int futex_wait(int *futex, int val, struct timespec *ts) {
	int err = syscall(SYS_futex, futex, FUTEX_WAIT, val, ts, NULL, 0);
	if (err == EWOULDBLOCK) {
		return 0;
	}
	return err;
}
