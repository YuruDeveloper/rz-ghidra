// Structures with padding, bit-fields and a union member. The file has DWARF data.

struct padded {
	char name[30];
	unsigned int quantity;
};

struct exact {
	char name[32];
	unsigned int quantity;
};

struct flags {
	unsigned int low : 4;
	unsigned int high : 28;
	char name[28];
	unsigned int quantity;
};

union value {
	unsigned int number;
	char text[8];
};

struct tagged {
	char kind;
	union value value;
	unsigned int quantity;
};

struct single {
	unsigned int quantity;
};

__attribute__((noinline)) void set_padded(struct padded *item, unsigned int quantity) {
	item->name[0] = 0;
	item->quantity = quantity;
}

__attribute__((noinline)) void set_exact(struct exact *item, unsigned int quantity) {
	item->name[0] = 0;
	item->quantity = quantity;
}

__attribute__((noinline)) void set_flags(struct flags *item, unsigned int quantity) {
	item->name[0] = 0;
	item->quantity = quantity;
}

__attribute__((noinline)) void set_tagged(struct tagged *item, unsigned int quantity) {
	item->kind = 1;
	item->quantity = quantity;
}

__attribute__((noinline)) void set_single(struct single *item, unsigned int quantity) {
	item->quantity = quantity;
}

__attribute__((noinline)) void set_untyped(void *item, unsigned int quantity) {
	struct padded *padded = item;
	padded->name[0] = 0;
	padded->quantity = quantity;
}

void struct_main(void *item, unsigned int quantity) {
	set_padded(item, quantity);
	set_exact(item, quantity);
	set_flags(item, quantity);
	set_tagged(item, quantity);
	set_single(item, quantity);
	set_untyped(item, quantity);
}
