struct Pair {
  unsigned short Kind;
  unsigned int Quantity;
};

struct Table {
  struct Pair Items[3];
  unsigned int Tail;
};

__attribute__((noinline)) void SetTail(struct Table *table,
                                       unsigned int value) {
  table->Tail = value;
}

void ReviewEntry(struct Table *table, unsigned int value) {
  SetTail(table, value);
}
