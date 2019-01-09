ZLLIB = ../../zlib/src
OBJS = backed_block.o output_file.o simg2simg.o sparse.o sparse_err.o sparse_read.o sparse_crc32.o
SIMG2IMG_OBJS = simg2img.o
IMG2SIMG_OBJS = img2simg.o

all: libsparse.a simg2img img2simg

libsparse.a: $(OBJS)
	$(AR) $(ARFLAGS) libsparse.a *.o

.c.o:
	$(CC) $(CFLAGS) -Iinclude -I$(ZLLIB) -c $< -o $@

simg2img: $(SIMG2IMG_OBJS) libsparse.a
	$(LD) $(LDFLAGS) -o simg2img $^ $(ZLLIB)/libz.a

img2simg: $(IMG2SIMG_OBJS) libsparse.a
	$(LD) $(LDFLAGS) -o img2simg $^ $(ZLLIB)/libz.a

clean:
	rm -f $(OBJS) $(SIMG2IMG_OBJS) $(IMG2SIMG_OBJS)
	rm -f libsparse.a
	rm -f simg2img img2simg

