# Build configuration
STATIC = 0
DEBUG = 0
DIET = 0
#TARGET = windows

CC = $(PREFIX)gcc -c
CFLAGS = -DUSE_MMAP -DHOST -DANDROID
LD = $(PREFIX)gcc
LDFLAGS =
LIBS =
AR = $(PREFIX)ar
ARFLAGS = rcs

ifeq ($(ARCH),)
ARCH = `uname -m`
endif
DEPLOY = deploy/$(ARCH)/

ifeq ($(DEBUG),1)
CFLAGS += -g
LDFLAGS += -g
DEPLOY := $(DEPLOY)debug-
else
CFLAGS += -DNDEBUG -O2
LDFLAGS += -s
DEPLOY := $(DEPLOY)release-
endif

ifeq ($(DIET),1)
PREFIX += diet #
DEPLOY := $(DEPLOY)diet-
ifeq ($(STATIC),1)
# DIET builds are always static, but -static will produce wrong results
STATIC := 0
endif
endif

# run make TARGET=windows for a mingw32 build
ifeq ($(TARGET),windows)
PREFIX += x86_64-w64-mingw32-
CFLAGS += -DUSE_MINGW
LIBS += -lwsock32
E = .exe
DEPLOY := $(DEPLOY)windows
else
DEPLOY := $(DEPLOY)linux
endif

ifeq ($(STATIC),1)
LDFLAGS += -static
DEPLOY := $(DEPLOY)static-
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
	$(MAKE) $(MFLAGS) -C $(SPLIB) all
	$(MAKE) $(MFLAGS) -C $(MALIB) all

clean:
	$(MAKE) $(MFLAGS) -C $(SELIB)/src clean
	$(MAKE) $(MFLAGS) -C $(ZLLIB) clean
	$(MAKE) $(MFLAGS) -C $(SPLIB) clean
	$(MAKE) $(MFLAGS) -C $(MALIB) clean

deploy: all
	mkdir -p $(DEPLOY)
	cp ./extras/ext4_utils/make_ext4fs$E \
	   ./core/libsparse/simg2img$E \
	   ./core/libsparse/img2simg$E \
	   $(DEPLOY)
