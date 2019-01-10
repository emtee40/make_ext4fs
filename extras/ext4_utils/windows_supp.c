/*
   Windows support for make_ext4fs
   Partly based on Cygwin source code.

   Copyright 1998, 1999, 2000, 2001 Red Hat, Inc.

   Written by Corinna Vinschen <corinna.vinschen@cityweb.de>

   This file is part of Cygwin.

   This software is a copyrighted work licensed under the terms of the
   Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
   details. */

#define _FILE_OFFSET_BITS 64
#define _LARGEFILE64_SOURCE 1

#include "windows_supp.h"

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <io.h>
#include <dos.h>
#include <wchar.h>

#include <windows.h>

int
scandir(const char *dir,
	struct dirent ***namelist,
	int (*select) (const struct dirent *),
	int (*compar) (const struct dirent **, const struct dirent **))
{
	DIR *dirp;
	struct dirent *ent, *etmp, **nl = NULL, **ntmp;
	int count = 0;
	int allocated = 0;

	if (!(dirp = opendir(dir)))
		return -1;

	int prior_errno = errno;
	_set_errno(0);

	while ((ent = readdir(dirp))) {
		if (!select || select(ent)) {

			/* Ignore error from readdir/select. See POSIX specs. */
			_set_errno(0);

			if (count == allocated) {
				if (allocated == 0)
					allocated = 10;
				else
					allocated *= 2;

				ntmp = (struct dirent **)realloc(
					nl, allocated * sizeof *nl);
				if (!ntmp) {
					_set_errno(ENOMEM);
					break;
				}
				nl = ntmp;
			}

			if (!(etmp = (struct dirent *)malloc(sizeof *ent))) {
				_set_errno(ENOMEM);
				break;
			}
			*etmp = *ent;
			nl[count++] = etmp;
		}
	}

	if ((prior_errno = errno) != 0) {
		closedir(dirp);
		if (nl) {
			while (count > 0)
				free(nl[--count]);
			free(nl);
		}
		/* Ignore errors from closedir() and what not else. */
		_set_errno(prior_errno);
		return -1;
	}

	closedir(dirp);
	_set_errno(prior_errno);

	qsort(nl, count, sizeof *nl,
	      (int (*)(const void *, const void *))compar);
	if (namelist)
		*namelist = nl;
	return count;
}

int alphasort(const struct dirent **a, const struct dirent **b)
{
	return strcoll((*a)->d_name, (*b)->d_name);
}

/* support only unicode symlinks for simplicity */
#define SYMLINK_ID	"!<symlink>\xff\xfe"
#define SYMLINK_IDLEN	strlen(SYMLINK_ID)
#define SYMLINK_MAXSIZE	1024

/* limited support for cygwin symlinks */
int lstat(const char *pathname, struct stat *statbuf)
{
	int rc, fd, fattr, fsize;
	char buff[SYMLINK_IDLEN];

	rc = stat(pathname, statbuf);
	if ((rc != 0) || (statbuf->st_size > SYMLINK_MAXSIZE))
		return rc;

	fattr = GetFileAttributesA(pathname);
	if ((fattr == INVALID_FILE_ATTRIBUTES) || !(fattr & _A_SYSTEM))
		return rc;

	fd = open (pathname, O_RDONLY);
	if (fd < 0)
		return rc;

	fsize = read(fd, buff, sizeof(buff));
	close(fd);

	if ((fsize < SYMLINK_IDLEN) ||
	    memcmp(buff, SYMLINK_ID, SYMLINK_IDLEN))
		return rc;

	statbuf->st_mode = S_IFLNK | S_IRWXU | S_IRWXG | S_IRWXO;
	statbuf->st_size = (statbuf->st_size - SYMLINK_IDLEN) / sizeof (WCHAR);
	return rc;
}

ssize_t readlink(const char *pathname, char *buf, size_t bufsiz)
{
	int pathname_len, fattr, fd, fsize;
	char buff[SYMLINK_MAXSIZE + sizeof (WCHAR)];

	/* could be CP_UTF8 but mingw uses ANSI code page for char* strings */
	pathname_len = MultiByteToWideChar(CP_ACP, 0,
		pathname, -1, (LPWSTR)buff, sizeof (buff) / sizeof (WCHAR));
	if (!pathname_len) {
		_set_errno (EINVAL);
		return -1;
	}

	fattr = GetFileAttributesW((LPWSTR)buff);
	if ((fattr == INVALID_FILE_ATTRIBUTES) || !(fattr & _A_SYSTEM)) {
		_set_errno (ENOENT);
		return -1;
	}

	fd = _wopen((LPWSTR)buff, O_RDONLY);
	if (fd < 0) {
		_set_errno (EACCES);
		return -1;
	}

	fsize = read(fd, buff, sizeof(buff));
	close(fd);

	if ((fsize < SYMLINK_IDLEN) ||
	    memcmp(buff, SYMLINK_ID, SYMLINK_IDLEN)) {
		_set_errno (EINVAL);
		return -1;
	}

	pathname_len = WideCharToMultiByte(CP_ACP, 0,
		(LPWSTR)(buff + SYMLINK_IDLEN), (fsize - SYMLINK_IDLEN) / sizeof (WCHAR),
		buf, bufsiz - 1, NULL, NULL);
	if (pathname_len <= 0) {
		_set_errno (EINVAL);
		return -1;
	}
	buf [pathname_len] = 0;

	return 0;
}
