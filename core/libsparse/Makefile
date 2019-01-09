ZLLIB = ../../zlib/src
OBJS = backed_block.o output_file.o simg2simg.o sparse.o sparse_err.o sparse_read.o sparse_crc32.o
SIMG2IMG_OBJS = simg2img.o
IMG2SIMG_OBJS = img2simg.o

all: libsparse.a simg2img$E img2simg$E

libsparse.a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -I$(ZLLIB) -c $< -o $@

simg2img$E: $(SIMG2IMG_OBJS) libsparse.a $(ZLLIB)/libz.a
	$(LD) $(LDFLAGS) -o $@ $^

img2simg$E: $(IMG2SIMG_OBJS) libsparse.a $(ZLLIB)/libz.a
	$(LD) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(SIMG2IMG_OBJS) $(IMG2SIMG_OBJS)
	rm -f libsparse.a
	rm -f simg2img$E img2simg$E
