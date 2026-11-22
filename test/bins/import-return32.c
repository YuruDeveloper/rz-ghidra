// Calls of imported functions with different kinds of return value in a PE for x86 with 32 bits.
// Build with the import-return32 rules in the Makefile. The program is not made to run.
// The cdecl model gives a 64-bit integer the register pair EDX:EAX and a floating-point value
// the register ST0. A structure goes to memory, and the caller gives its address as a hidden arg.
// With USE_SLOTS, each call goes through the import slot. Without it, each import gets a thunk.

#ifdef USE_SLOTS
#define IMPORT __declspec(dllimport)
#else
#define IMPORT
#endif

struct wide_record {
	unsigned long long first;
	unsigned long long second;
	unsigned long long third;
};

IMPORT unsigned long long api_wide(int marker);
IMPORT double api_double(int marker);
IMPORT float api_float(int marker);
IMPORT struct wide_record api_record(int marker);
IMPORT void api_void(int marker);

__attribute__((noinline)) unsigned long long return_wide(int marker) {
	return api_wide(marker) + 0x100000002ULL;
}

__attribute__((noinline)) double return_double(int marker) {
	return api_double(marker) * 2.0;
}

__attribute__((noinline)) float return_float(int marker) {
	return api_float(marker) * 2.0f;
}

__attribute__((noinline)) unsigned long long return_record(int marker) {
	struct wide_record record = api_record(marker);
	return record.first + record.third;
}

__attribute__((noinline)) int return_void(int marker) {
	api_void(marker);
	return marker + 7;
}

int return_main(void) {
	return 0;
}
