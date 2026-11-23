// Structures for the test of bit-fields in DWARF 5 data.
struct BitsWide {
  unsigned int A : 3;
  unsigned int B : 5;
  unsigned int C : 8;
  unsigned int D : 4;
};

struct __attribute__((gcc_struct)) BitsSqueeze {
  char Tag;
  int Mid : 8;
  int Tail;
};

struct BitsTwoUnits {
  unsigned int A : 20;
  unsigned int B : 20;
  unsigned short Last;
};

struct BitsAnchor {
  struct BitsWide Mode;
  long long Wide;
  unsigned int Low : 1;
  unsigned int High : 1;
};

struct BitsOuter {
  unsigned char Kind;
  struct BitsWide Inner;
  unsigned short Low : 4;
  unsigned int Tail;
};

struct BitsRow {
  struct BitsWide Items[3];
  unsigned char Mark;
  unsigned int Tail;
};

_Static_assert(sizeof(struct BitsWide) == 4, "");
_Static_assert(sizeof(struct BitsSqueeze) == 8, "");
_Static_assert(__builtin_offsetof(struct BitsSqueeze, Tail) == 4, "");
_Static_assert(sizeof(struct BitsTwoUnits) == 12, "");
_Static_assert(__builtin_offsetof(struct BitsTwoUnits, Last) == 8, "");
_Static_assert(sizeof(struct BitsAnchor) == 24, "");
_Static_assert(__builtin_offsetof(struct BitsAnchor, Wide) == 8, "");
_Static_assert(sizeof(struct BitsOuter) == 16, "");
_Static_assert(__builtin_offsetof(struct BitsOuter, Inner) == 4, "");
_Static_assert(__builtin_offsetof(struct BitsOuter, Tail) == 12, "");
_Static_assert(sizeof(struct BitsRow) == 20, "");
_Static_assert(__builtin_offsetof(struct BitsRow, Mark) == 12, "");
_Static_assert(__builtin_offsetof(struct BitsRow, Tail) == 16, "");

struct BitsOuter BitsOuters[2];
unsigned int AfterBitsOuters;
struct BitsWide BitsWides[3];
unsigned int AfterBitsWides;

__attribute__((noinline)) void SetBitsSqueeze(struct BitsSqueeze *squeeze,
                                              int value) {
  squeeze->Tag = (char)value;
  squeeze->Tail = value;
}

__attribute__((noinline)) void SetBitsTwoUnits(struct BitsTwoUnits *two,
                                               unsigned int value) {
  two->Last = (unsigned short)value;
}

__attribute__((noinline)) void SetBitsAnchor(struct BitsAnchor *anchor,
                                             long long value) {
  anchor->Wide = value;
}

__attribute__((noinline)) void SetBitsOuter(struct BitsOuter *outer,
                                            unsigned int value) {
  outer->Kind = (unsigned char)value;
  outer->Tail = value;
}

__attribute__((noinline)) void SetBitsRow(struct BitsRow *row,
                                          unsigned int value) {
  row->Mark = (unsigned char)value;
  row->Tail = value;
}

__attribute__((noinline)) void SetBitsMode(struct BitsAnchor *anchor,
                                           struct BitsWide mode) {
  anchor->Mode = mode;
}

__attribute__((noinline)) void SetBitsItem(struct BitsRow *row,
                                           struct BitsWide item) {
  row->Items[2] = item;
}

__attribute__((noinline)) void SetBitsOuters(unsigned int value) {
  BitsOuters[1].Tail = value;
  AfterBitsOuters = value;
}

__attribute__((noinline)) void SetBitsWides(struct BitsWide item,
                                            unsigned int value) {
  BitsWides[2] = item;
  AfterBitsWides = value;
}

void BitsEntry(void *item, unsigned int value) {
  SetBitsSqueeze(item, (int)value);
  SetBitsTwoUnits(item, value);
  SetBitsAnchor(item, value);
  SetBitsOuter(item, value);
  SetBitsRow(item, value);
  SetBitsMode(item, *(struct BitsWide *)item);
  SetBitsItem(item, *(struct BitsWide *)item);
  SetBitsOuters(value);
  SetBitsWides(*(struct BitsWide *)item, value);
}
