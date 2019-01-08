ZLLIB = ../../zlib/src
OBJS = $(patsubst %.c,%.o,$(wildcard *.c))

all: libsparse.a simg2img img2simg

libsparse.a:
	$(CC) $(CFLAGS) -Iinclude -c backed_block.c output_file.c sparse.c sparse_crc32.c sparse_err.c sparse_read.c
	$(AR) $(ARFLAGS) libsparse.a *.o

simg2img:
	$(LD) $(CFLAGS) $(LDFLAGS) -Iinclude -I$(ZLLIB) -o simg2img simg2img.c sparse_crc32.c libsparse.a $(ZLLIB)/libz.a

img2simg:
	$(LD) $(CFLAGS) $(LDFLAGS) -Iinclude -I$(ZLLIB) -o img2simg img2simg.c sparse_crc32.c libsparse.a $(ZLLIB)/libz.a

clean:
	rm -f $(OBJS)
	rm -f libsparse.a
	rm -f simg2img img2simg

