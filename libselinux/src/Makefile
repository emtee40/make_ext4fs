COLIB = ../../core
EXT4U = ../../extras/ext4_utils
OBJS = callbacks.o check_context.o \
	init.o label.o label_file.o label_android_property.o

INCLUDE = -I../include -I$(COLIB)/include
ifeq ($E,.exe)
INCLUDE += -I$(EXT4U) -I$(EXT4U)/regex
endif

all: libselinux.a

libselinux.a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $<

clean:
	rm -f $(OBJS)
	rm -f libselinux.a
