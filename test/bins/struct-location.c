// Structures for the test of member locations in DWARF 2 data.
// The file struct-location.s has the changed locations.

struct LocationMixed {
  unsigned int Flags : 32;
  unsigned int MixedValue;
};

struct LocationGap {
  unsigned char Tag;
  unsigned int GapValue;
  unsigned int GapLast;
};

struct LocationTight {
  unsigned int First;
  unsigned int TightSecond;
  unsigned int Third;
};

struct LocationOuter {
  unsigned char Kind;
  struct LocationMixed Inner;
  unsigned int Tail;
};

_Static_assert(__builtin_offsetof(struct LocationMixed, MixedValue) == 4, "");
_Static_assert(__builtin_offsetof(struct LocationGap, GapValue) == 4, "");
_Static_assert(__builtin_offsetof(struct LocationGap, GapLast) == 8, "");
_Static_assert(__builtin_offsetof(struct LocationTight, TightSecond) == 4, "");
_Static_assert(__builtin_offsetof(struct LocationTight, Third) == 8, "");
_Static_assert(__builtin_offsetof(struct LocationOuter, Inner) == 4, "");
_Static_assert(__builtin_offsetof(struct LocationOuter, Tail) == 12, "");

struct LocationMixed Mixes[2];
unsigned int AfterMixes;

__attribute__((noinline)) void SetMixed(struct LocationMixed *mixed,
                                        unsigned int value) {
  mixed->MixedValue = value;
}

__attribute__((noinline)) void SetGap(struct LocationGap *gap,
                                      unsigned int value) {
  gap->GapValue = value;
  gap->GapLast = value;
}

__attribute__((noinline)) void SetTight(struct LocationTight *tight,
                                        unsigned int value) {
  tight->TightSecond = value;
  tight->Third = value;
}

__attribute__((noinline)) void SetOuter(struct LocationOuter *outer,
                                        unsigned int value) {
  outer->Inner.MixedValue = value;
  outer->Tail = value;
}

__attribute__((noinline)) void SetMixes(unsigned int value) {
  Mixes[1].MixedValue = value;
  AfterMixes = value;
}

void LocationEntry(void *memory, unsigned int value) {
  SetMixed(memory, value);
  SetGap(memory, value);
  SetTight(memory, value);
  SetOuter(memory, value);
  SetMixes(value);
}
