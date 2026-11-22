// Calls to imported functions through import thunks.
// Build with the import-args rule in the Makefile. The program is not made to run.

#include "import-args.h"

extern unsigned long long fread(void *buffer, unsigned long long size, unsigned long long count, void *stream);
extern int memcmp(const void *left, const void *right, unsigned long long length);
extern void *malloc(unsigned long long size);
extern int printf(const char *format, ...);
extern int fprintf(void *stream, const char *format, ...);
extern int sprintf(char *buffer, const char *format, ...);
extern int vprintf(const char *format, char *list);
extern int vfprintf(void *stream, const char *format, char *list);

struct header {
	char magic[4];
	unsigned short count;
	unsigned short note_length;
};

__attribute__((noinline)) int probe_fixed(void *stream) {
	struct header header;
	if (fread(&header, sizeof(header), 1, stream) != 1) {
		return -1;
	}
	if (memcmp(header.magic, "INV1", 4) != 0) {
		return -2;
	}
	return header.count;
}

__attribute__((noinline)) void *probe_truncate(const struct header *header) {
	unsigned short size = header->note_length + 1;
	return malloc(size);
}

__attribute__((noinline)) int probe_printf(void) {
	return printf("%d %d %d %d %d %d", 11, 22, 33, 44, 55, 66);
}

__attribute__((noinline)) int probe_fprintf(void *stream) {
	return fprintf(stream, "plain text");
}

__attribute__((noinline)) int probe_sprintf(char *buffer) {
	return sprintf(buffer, "plain text");
}

__attribute__((noinline)) int probe_vprintf(const char *format, char *list) {
	return vprintf(format, list);
}

__attribute__((noinline)) int probe_vfprintf(void *stream, const char *format, char *list) {
	return vfprintf(stream, format, list);
}

__attribute__((noinline)) void probe_large(void) {
	struct aggregate record = { 11, 22, 33 };
	api_large(record, 77);
}

__attribute__((noinline)) unsigned long long probe_return(void) {
	struct aggregate record = api_return(77);
	return record.third;
}

int probe_main(void) {
	return probe_printf();
}
