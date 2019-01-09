# Build configuration
STATIC = 0
DEBUG = 1
#TARGET = windows

CC = $(PREFIX)gcc -c
CFLAGS = -DUSE_MMAP -DHOST -DANDROID
LD = $(PREFIX)gcc
LDFLAGS =
LIBS =
AR = $(PREFIX)ar
ARFLAGS = rcs

ifeq ($(DEBUG),1)
CFLAGS += -g
LDFLAGS += -g
else
CFLAGS += -O2
LDFLAGS += -s
endif

ifeq ($(STATIC),1)
LDFLAGS += -static
endif

# run make TARGET=windows for a mingw32 build
ifeq ($(TARGET),windows)
PREFIX = x86_64-w64-mingw32-
CFLAGS += -DUSE_MINGW
LIBS += -lwsock32
E = .exe
endif

SELIB = libselinux
ZLLIB = zlib/src
SPLIB = core/libsparse
COLIB = core
MALIB = extras/ext4_utils

MFLAGS += CC="$(CC)" CFLAGS="$(CFLAGS)" \
	LD="$(LD)" LDFLAGS="$(LDFLAGS)" LIBS="$(LIBS)" \
	AR="$(AR)" ARFLAGS="$(ARFLAGS)" \
	E="$E"

all:
	$(MAKE) $(MFLAGS) -C $(SELIB)/src all
	$(MAKE) $(MFLAGS) -C $(ZLLIB) all
	$(MAKE) $(MFLAGS) -C $(SPLIB) libsparse.a
	$(MAKE) $(MFLAGS) -C $(MALIB) all

clean:
	$(MAKE) -C $(SELIB)/src clean
	$(MAKE) -C $(ZLLIB) clean
	$(MAKE) -C $(SPLIB) clean
	$(MAKE) -C $(MALIB) clean
