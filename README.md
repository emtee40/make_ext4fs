[![English](http://flags.fmcdn.net/style/silk/png/gb.png)](README.md), [![Русский](http://flags.fmcdn.net/style/silk/png/ru.png)](README.ru.md)

This is yet another clone of make_ext4fs & friends, split from the
superr/make_ext4fs repository.

The reason for cloning was to fix a severe bug and to add a few features
needed by the [Android firmware construction kit project](https://github.com/anpaza/afck).

Also I needed identical builds for linux and windows. That was achieved
by modifying makefiles to support cross-building with mingw.

The behaviour of make_ext4fs has been modified in the following ways:

* In fs_config you can specify -1 in the place of uid, gid and mode.
  If the respective field is -1, the original value is retained
  (uid and gid have value 0 by default, and mode is taken from filesystem).

* If a file is missing from fs_config, a warning is displayed but
  the uid, gid and mode are computed using the default rules
  (same like fs_config is not specified).

* The Windows version of make_ext4fs now can scan directories, same way as
  it does in Unix. MinGW will report mode 0666 for files and 0777 for
  directories; this is not very useful, so better set file modes in fs_config.

  However, this is useful to see if you ommited any files from fs_config,
  due to previous modification.

* If during image creation it turns out that one of the source files
  cannot be open, the tool will:

  * under Linux it will make an attempt to temporarily change
    file mode to 0444, then open it, then restore the original
    file mode.

  * if that fails anyway, a error message will be printed to stderr,
    with a pointer to the file that cannot be read. Also a error
    flag will be returned that will tell the tool to delete the
    invalid image (and a message will be displayed about that too).

* Mingw build now has support for Cygwin-style symlinks. Here's a example
  hex dump of such a file, say, /bin/ls:

    00000000 21 3C 73 79 │ 6D 6C 69 6E │ 6B 3E FF FE │ 74 00 6F 00 │ 79 00 62 00  !<symlink>..t.o.y.b.
    00000014 6F 00 78 00 │ 5F 00 76 00 │ 65 00 6E 00 │ 64 00 6F 00 │ 72 00 00 00  o.x._.v.e.n.d.o.r...

  The resulting ext4 image will contain a real link /bin/ls pointing to
  "toybox_vendor".

* Mingw build now has support for SELinux labeling. The labels cannot be
  extracted from file system (this is obvious), but instead the -S option
  can be used to provide a filename -> SELinux context map. You can use
  regular expressions in file names.
