/* The callers give the address of a small local and small values to functions of this file.
 * The type of an argument of a callee must not become smaller because of the local of the caller. */
typedef struct _iobuf FILE;
FILE *fopen(const char *path, const char *mode);
int atoi(const char *text);

__attribute__((noinline)) void fill_int(int *out) {
	*out = 5;
}

__attribute__((noinline)) void fill_wide(long long *out) {
	*out = 7;
}

__attribute__((noinline)) int take_int(int value) {
	return value + 100000;
}

__attribute__((noinline)) unsigned take_unsigned(unsigned value) {
	return value / 3;
}

__attribute__((noinline)) long long take_long(long long value) {
	return value / 3;
}

__attribute__((noinline)) int keep_stream(void *stream) {
	return stream != 0;
}

__attribute__((noinline)) void bump_short(unsigned short *value) {
	*value += 1;
}

int call_address(void) {
	short value = 3;
	fill_int((int *)&value);
	return value;
}

int call_address_int(void) {
	int value = 3;
	fill_wide((long long *)&value);
	return value;
}

int call_value(void) {
	volatile short small = 3;
	volatile unsigned char tiny = 200;
	return take_int(small) + (int)take_unsigned(tiny);
}

/* The local gets the type int from the return value of atoi. The callee has an argument of 8 bytes. */
long long call_widen(const char *text) {
	volatile int count = atoi(text);
	return take_long(count);
}

int call_stream(const char *path) {
	FILE *volatile stream = fopen(path, "r");
	return keep_stream(stream);
}

/* A compiler does not compare a stack slot with a constant in memory, so this caller is in assembly.
 * It makes an unsigned comparison of a local of 2 bytes and then gives the address of the local. */
int call_compared(void);
__asm__(
	".def call_compared; .scl 2; .type 32; .endef\n"
	".globl call_compared\n"
	"call_compared:\n"
	"	subq $40, %rsp\n"
	"	movw $200, 32(%rsp)\n"
	"	cmpw $128, 32(%rsp)\n"
	"	jbe 1f\n"
	"	leaq 32(%rsp), %rcx\n"
	"	callq bump_short\n"
	"1:\n"
	"	movzwl 32(%rsp), %eax\n"
	"	addq $40, %rsp\n"
	"	retq\n");

int width_main(const char *path) {
	return call_address() + call_address_int() + call_value() + (int)call_widen(path) + call_stream(path) + call_compared();
}
