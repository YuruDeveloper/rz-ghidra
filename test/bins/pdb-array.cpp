struct Pair {
  unsigned short Kind;
  unsigned int Quantity;
};

struct PairTable {
  struct Pair Items[3];
  unsigned int Tail;
};

struct GridRecord {
  short Grid[2][3];
  unsigned int Tail;
};

struct WideRecord {
  wchar_t Wide[16];
  unsigned int Tail;
};

struct Utf8Record {
  char8_t Utf8[5];
  unsigned int Tail;
};

extern "C" {
__attribute__((noinline)) void SetItem(struct PairTable *table,
                                       unsigned int value) {
  table->Items[2].Quantity = value;
}

__attribute__((noinline)) void SetTableTail(struct PairTable *table,
                                            unsigned int value) {
  table->Tail = value;
}

__attribute__((noinline)) void SetGrid(struct GridRecord *record, short value) {
  record->Grid[1][2] = value;
}

__attribute__((noinline)) void SetGridTail(struct GridRecord *record,
                                           unsigned int value) {
  record->Tail = value;
}

__attribute__((noinline)) void SetWide(struct WideRecord *record,
                                       wchar_t value) {
  record->Wide[15] = value;
}

__attribute__((noinline)) void SetWideTail(struct WideRecord *record,
                                           unsigned int value) {
  record->Tail = value;
}

__attribute__((noinline)) void SetUtf8(struct Utf8Record *record,
                                       char8_t value) {
  record->Utf8[4] = value;
}

void PdbArrayEntry(struct PairTable *table, struct GridRecord *grid,
                   struct WideRecord *wide, struct Utf8Record *utf8,
                   unsigned int value) {
  SetUtf8(utf8, (char8_t)value);
  SetItem(table, value);
  SetTableTail(table, value);
  SetGrid(grid, (short)value);
  SetGridTail(grid, value);
  SetWide(wide, (wchar_t)value);
  SetWideTail(wide, value);
}
}
