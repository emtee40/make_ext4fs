/*
   Windows support for make_ext4fs
   Partly based on Cygwin source code.

   Copyright 1998, 1999, 2000, 2001 Red Hat, Inc.

   Written by Corinna Vinschen <corinna.vinschen@cityweb.de>

   This file is part of Cygwin.

   This software is a copyrighted work licensed under the terms of the
   Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
   details. */

#ifndef _WINDOWS_SUPP_H
#define _WINDOWS_SUPP_H

#include <dirent.h>
#include <sys/stat.h>

#define S_ISUID		0
#define S_ISGID		0
#define S_ISVTX		0

#define S_IFLNK		0xA000
#define S_ISLNK(m)	(((m) & S_IFMT) == S_IFLNK)

extern int scandir (
	 const char *dir,
	 struct dirent ***namelist,
	 int (*select) (const struct dirent *),
	 int (*compar) (const struct dirent **, const struct dirent **));

extern int alphasort (const struct dirent **a, const struct dirent **b);

extern int lstat(const char *pathname, struct stat *statbuf);
extern ssize_t readlink(const char *pathname, char *buf, size_t bufsiz);

#endif /* _WINDOWS_SUPP_H */
