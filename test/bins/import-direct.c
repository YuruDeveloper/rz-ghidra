// Calls to imported functions through the import slots, without import thunks.
// Build with the import-direct rule in the Makefile. The program is not made to run.
// The types of api_large and api_return are in import-args.h for the type database.

struct aggregate {
	unsigned long long first;
	unsigned long long second;
	unsigned long long third;
};

struct header {
	char magic[4];
	unsigned short count;
	unsigned short note_length;
};

__declspec(dllimport) unsigned long long fread(void *buffer, unsigned long long size, unsigned long long count, void *stream);
__declspec(dllimport) int memcmp(const void *left, const void *right, unsigned long long length);
__declspec(dllimport) void *malloc(unsigned long long size);
__declspec(dllimport) int printf(const char *format, ...);
__declspec(dllimport) int fprintf(void *stream, const char *format, ...);
__declspec(dllimport) int vprintf(const char *format, char *list);
__declspec(dllimport) __attribute__((noreturn)) void ExitProcess(unsigned int code);
__declspec(dllimport) void api_large(struct aggregate record, int marker);
__declspec(dllimport) struct aggregate api_return(int marker);

int (*local_callback)(int value);

__attribute__((noinline)) int direct_fixed(void *stream) {
	struct header header;
	if (fread(&header, sizeof(header), 1, stream) != 1) {
		return -1;
	}
	if (memcmp(header.magic, "INV1", 4) != 0) {
		return -2;
	}
	return header.count;
}

__attribute__((noinline)) void *direct_truncate(const struct header *header) {
	unsigned short size = header->note_length + 1;
	return malloc(size);
}

__attribute__((noinline)) int direct_printf(void) {
	return printf("%d %d %d %d %d %d", 11, 22, 33, 44, 55, 66);
}

__attribute__((noinline)) int direct_fprintf(void *stream) {
	return fprintf(stream, "plain text");
}

__attribute__((noinline)) int direct_vprintf(const char *format, char *list) {
	return vprintf(format, list);
}

__attribute__((noinline)) void direct_large(void) {
	struct aggregate record = { 11, 22, 33 };
	api_large(record, 77);
}

__attribute__((noinline)) unsigned long long direct_return(void) {
	struct aggregate record = api_return(77);
	return record.third;
}

// The import does not return, so the code after the call is not a part of this function.
__attribute__((noinline)) unsigned int direct_exit(unsigned int code) {
	if (code > 3) {
		ExitProcess(code);
	}
	return code + 1;
}

// The address of an import is data here, not a call.
__attribute__((noinline)) void *direct_address(void) {
	return (void *)malloc;
}

// A call through a pointer that is not an import slot.
__attribute__((noinline)) int direct_callback(int value) {
	return local_callback(value) + 1;
}

int direct_main(void) {
	return direct_printf();
}
