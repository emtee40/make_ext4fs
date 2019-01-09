OBJS = adler32.o compress.o crc32.o deflate.o gzclose.o \
	gzlib.o gzread.o gzwrite.o infback.o inflate.o \
	inftrees.o inffast.o trees.o uncompr.o zutil.o

all: libz.a

libz.a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -I.. -o $@ $<

clean:
	rm -f $(OBJS)
	rm -f libz.a
