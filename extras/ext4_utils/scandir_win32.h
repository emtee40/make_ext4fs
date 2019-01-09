/* scandir.cc

   Copyright 1998, 1999, 2000, 2001 Red Hat, Inc.

   Written by Corinna Vinschen <corinna.vinschen@cityweb.de>

   This file is part of Cygwin.

   This software is a copyrighted work licensed under the terms of the
   Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
   details. */

#ifndef _SCANDIR_WIN32_H
#define _SCANDIR_WIN32_H

extern int scandir (
	 const char *dir,
	 struct dirent ***namelist,
	 int (*select) (const struct dirent *),
	 int (*compar) (const struct dirent **, const struct dirent **));

extern int alphasort (const struct dirent **a, const struct dirent **b);

#endif /* _SCANDIR_WIN32_H */
