SELIB = libselinux
ZLLIB = zlib/src
SPLIB = core/libsparse
COLIB = core
MALIB = extras/ext4_utils

CC = $(PREFIX)gcc -c
CFLAGS = -O3 -DUSE_MMAP -DHOST -DANDROID
LD = $(PREFIX)gcc
LDFLAGS = -s -static
LIBS =
AR = $(PREFIX)ar
ARFLAGS = rcs

# run make TARGET=windows for a mingw32 build
ifeq ($(TARGET),windows)
PREFIX = x86_64-w64-mingw32-
CFLAGS += -DUSE_MINGW
LIBS += -lwsock32
E = .exe
endif

MFLAGS += CC="$(CC)" CFLAGS="$(CFLAGS)" \
	LD="$(LD)" LDFLAGS="$(LDFLAGS)" LIBS="$(LIBS)" \
	AR="$(AR)" ARFLAGS="$(ARFLAGS)" \
	E="$E"

all:
	$(MAKE) $(MFLAGS) -C $(SELIB)/src all
	$(MAKE) $(MFLAGS) -C $(ZLLIB) all
	$(MAKE) $(MFLAGS) -C $(SPLIB) libsparse.a
	$(MAKE) $(MFLAGS) -C $(MALIB) all
	mv $(MALIB)/make_ext4fs$E make_ext4fs$E

clean:
	$(MAKE) -C $(SELIB)/src clean
	$(MAKE) -C $(ZLLIB) clean
	$(MAKE) -C $(SPLIB) clean
	$(MAKE) -C $(MALIB) clean
