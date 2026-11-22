// Calls to imported functions in an ELF object file. Each call goes to a reloc target.
// Build with the import-reloc rule in the Makefile.

struct header {
	char magic[4];
	unsigned short count;
	unsigned short note_length;
};

extern unsigned long fread(void *buffer, unsigned long size, unsigned long count, void *stream);
extern void *malloc(unsigned long size);
extern int printf(const char *format, ...);
extern int vprintf(const char *format, void *list);
extern void exit(int status) __attribute__((noreturn));

int reloc_fixed(void *stream) {
	struct header header;
	if (fread(&header, sizeof(header), 1, stream) != 1) {
		return -1;
	}
	return header.count;
}

void *reloc_truncate(const struct header *header) {
	unsigned short size = header->note_length + 1;
	return malloc(size);
}

int reloc_printf(void) {
	return printf("%d %d %d %d %d %d %d", 11, 22, 33, 44, 55, 66, 77);
}

int reloc_vprintf(const char *format, void *list) {
	return vprintf(format, list);
}

int reloc_exit(int status) {
	if (status > 3) {
		exit(status);
	}
	return status + 1;
}
