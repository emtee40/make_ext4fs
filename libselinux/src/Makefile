COLIB = ../../core
OBJS = callbacks.o check_context.o \
	freecon.o init.o label.o label_file.o label_android_property.o

all: libselinux.a

libselinux.a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -I../include -I$(COLIB)/include -o $@ $<

clean:
	rm -f $(OBJS)
	rm -f libselinux.a
