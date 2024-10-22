#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "selinux_internal.h"
#include "policy.h"


int security_check_context(const char * con)
{
	char path[PATH_MAX];

	if (!selinux_mnt) {
		errno = ENOENT;
		return -1;
	}

	snprintf(path, sizeof path, "%s/context", selinux_mnt);
	int fd = open(path, O_RDWR);
	if (fd < 0)
		return -1;

	int ret = write(fd, con, strlen(con) + 1);
	close(fd);
	if (ret < 0)
		return -1;
	return 0;
}

