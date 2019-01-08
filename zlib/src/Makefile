OBJS = $(patsubst %.c,%.o,$(wildcard *.c))

all: libz.a

libz.a:
	$(CC) $(CFLAGS) -I.. adler32.c compress.c crc32.c deflate.c gzclose.c \
	gzlib.c gzread.c gzwrite.c infback.c inflate.c inftrees.c inffast.c trees.c uncompr.c zutil.c
	$(AR) $(ARFLAGS) libz.a *.o

clean:
	rm -f $(OBJS)
	rm -f libz.a
