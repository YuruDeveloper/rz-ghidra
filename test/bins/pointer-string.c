// Pointers to short strings and to other data in a PE for x86-64.
// Build with the pointer-string.exe rule in the Makefile. The program is not made to run.
// Rizin finds a string for the long mode. It finds no string for "rb" and "a", and it gives
// each of these addresses a flag "data.<address>".

typedef struct _iobuf FILE;
FILE *fopen(const char *filename, const char *mode);
int write(int descriptor, const char *buffer, unsigned int count);

// The first address of a section gets no flag "data.<address>", thus the string is not first.
static struct {
	int count;
	char mode[4];
} writable = { 5, "wb" };
static const int numbers[4] = { 1, 2, 3, 4 };
// The bytes of this array are the same as the string "rb".
static const unsigned short string_bytes[4] = { 0x6272, 0, 7, 9 };
// Each record has four bytes and no terminator. The first two bytes of each record are the same
// as the string "A". The third byte has no flag, thus a record is not a string.
static const struct {
	unsigned first_pad;
	char first[4];
	unsigned second_pad;
	char second[4];
	unsigned last_pad;
} records = { 0, { 'A', 0, 'B', 0 }, 0, { 'A', 0, 'C', 0 }, 0 };

__attribute__((noinline)) FILE *pointer_open_long(const char *name) {
	return fopen(name, "r+b,ccs=UTF-8");
}

__attribute__((noinline)) FILE *pointer_open(const char *name) {
	return fopen(name, "rb");
}

__attribute__((noinline)) FILE *pointer_open_one(const char *name) {
	return fopen(name, "a");
}

__attribute__((noinline)) FILE *pointer_open_writable(const char *name) {
	return fopen(name, writable.mode);
}

__attribute__((noinline)) int pointer_numbers(unsigned index) {
	return numbers[index & 3];
}

__attribute__((noinline)) int pointer_string_bytes(unsigned index) {
	return string_bytes[index & 3];
}

__attribute__((noinline)) int pointer_write_records(int descriptor) {
	return write(descriptor, records.first, 4) + write(descriptor, records.second, 4);
}

int pointer_main(const char *name, unsigned index) {
	writable.count += index;
	writable.mode[0] = (char)('a' + (index & 1));
	return (pointer_open_long(name) != 0) + (pointer_open(name) != 0) + (pointer_open_one(name) != 0) +
		(pointer_open_writable(name) != 0) + pointer_numbers(index) + pointer_string_bytes(index) + pointer_write_records((int)index) +
		writable.count;
}
