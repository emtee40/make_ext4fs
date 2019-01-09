SELIB = ../../libselinux
ZLLIB = ../../zlib/src
COLIB = ../../core
SPLIB = ../../core/libsparse
OBJS = ext4fixup.o ext4_utils.o allocate.o contents.o extent.o \
	indirect.o uuid.o sha1.o wipe.o crc16.o ext4_sb.o canned_fs_config.o
MKE4FS_OBJS = make_ext4fs_main.o make_ext4fs.o

MKE4FS = ../../make_ext4fs$E

all: $(MKE4FS)

$(MKE4FS): $(MKE4FS_OBJS) $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^ \
	$(SELIB)/src/libselinux.a $(SPLIB)/libsparse.a $(ZLLIB)/libz.a $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -I$(SELIB)/include -I$(SPLIB)/include -I$(COLIB)/include -o $@ $<

clean:
	rm -f $(MKE4FS_OBJS)
	rm -f $(MKE4FS)
