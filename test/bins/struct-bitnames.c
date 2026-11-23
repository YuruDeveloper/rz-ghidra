// Structures for the test of the names of bit members in the output of pdg.
struct NameFlags {
  unsigned int Ready : 1;
  unsigned int Mode : 3;
  unsigned int Count : 12;
  int Level : 5;
  unsigned int Tail;
};

struct NameAnchor {
  long long Wide;
  unsigned int Low : 4;
  unsigned int High : 9;
};

struct __attribute__((gcc_struct)) NameShare {
  unsigned char Tag;
  unsigned int Flag : 7;
  unsigned short Value;
};

struct NameWhole {
  unsigned int Whole : 16;
  unsigned int Part : 5;
  unsigned int Rest;
};

struct NameOuter {
  unsigned char Kind;
  struct NameFlags Inner;
  unsigned int Tail;
};

struct NameBeyond {
  unsigned int Keep : 4;
  unsigned int Far : 4;
  unsigned int Tail;
};

struct NameOverlap {
  unsigned int First : 4;
  unsigned int Second : 4;
  unsigned int Tail;
};

struct NameOnPlain {
  unsigned int Bit : 4;
  unsigned int Tail;
};

struct NameLost {
  long long Wide;
  unsigned int LostBit : 1;
  unsigned int KeptBit : 1;
  unsigned int Tail;
};

_Static_assert(sizeof(struct NameFlags) == 8, "");
_Static_assert(__builtin_offsetof(struct NameFlags, Tail) == 4, "");
_Static_assert(sizeof(struct NameAnchor) == 16, "");
_Static_assert(sizeof(struct NameShare) == 4, "");
_Static_assert(__builtin_offsetof(struct NameShare, Value) == 2, "");
_Static_assert(sizeof(struct NameWhole) == 8, "");
_Static_assert(sizeof(struct NameOuter) == 16, "");
_Static_assert(__builtin_offsetof(struct NameOuter, Inner) == 4, "");
_Static_assert(__builtin_offsetof(struct NameOuter, Tail) == 12, "");
_Static_assert(sizeof(struct NameBeyond) == 8, "");
_Static_assert(sizeof(struct NameOverlap) == 8, "");
_Static_assert(sizeof(struct NameOnPlain) == 8, "");
_Static_assert(sizeof(struct NameLost) == 16, "");
_Static_assert(__builtin_offsetof(struct NameLost, Tail) == 12, "");

struct NameFlags NameGlobals[2];
unsigned int AfterNameGlobals;

__attribute__((noinline)) void SetNameMode(struct NameFlags *flags, unsigned int value) {
  flags->Mode = value;
}

__attribute__((noinline)) unsigned int GetNameCount(struct NameFlags *flags) {
  return flags->Count;
}

__attribute__((noinline)) void SetNameLevel(struct NameFlags *flags, int value) {
  flags->Level = value;
  flags->Tail = (unsigned int)value;
}

__attribute__((noinline)) int GetNameLevel(struct NameFlags *flags) {
  return flags->Level;
}

__attribute__((noinline)) void TestNameReady(struct NameFlags *flags, unsigned int value) {
  if (flags->Ready) {
    flags->Tail = value;
  }
}

__attribute__((noinline)) void SetNameLow(struct NameAnchor *anchor, unsigned int value) {
  anchor->Low = value;
}

__attribute__((noinline)) void SetNameHigh(struct NameAnchor *anchor, long long value) {
  anchor->Wide = value;
  anchor->High = 5;
}

__attribute__((noinline)) void SetNameFlag(struct NameShare *share, unsigned int value) {
  share->Flag = value;
  share->Value = (unsigned short)value;
}

__attribute__((noinline)) void SetNameWhole(struct NameWhole *whole, unsigned int value) {
  whole->Whole = value;
  whole->Rest = value;
}

__attribute__((noinline)) void SetNamePart(struct NameWhole *whole, unsigned int value) {
  whole->Part = value;
}

__attribute__((noinline)) void SetNameInner(struct NameOuter *outer, unsigned int value) {
  outer->Inner.Mode = value;
  outer->Tail = value;
}

__attribute__((noinline)) void SetNameGlobal(unsigned int value) {
  NameGlobals[1].Mode = value;
  NameGlobals[1].Tail = value;
  AfterNameGlobals = value;
}

__attribute__((noinline)) unsigned int SumNameFlags(struct NameFlags flags) {
  return flags.Mode + flags.Count + flags.Tail;
}

__attribute__((noinline)) void SetNameBeyond(struct NameBeyond *beyond, unsigned int value) {
  beyond->Keep = value;
  beyond->Far = value;
  beyond->Tail = value;
}

__attribute__((noinline)) void SetNameOverlap(struct NameOverlap *overlap, unsigned int value) {
  overlap->First = value;
  overlap->Second = value;
  overlap->Tail = value;
}

__attribute__((noinline)) void SetNameOnPlain(struct NameOnPlain *plain, unsigned int value) {
  plain->Bit = value;
  plain->Tail = value;
}

__attribute__((noinline)) void SetNameLost(struct NameLost *lost, unsigned int value) {
  lost->LostBit = value;
  lost->KeptBit = value;
  lost->Wide = value;
  lost->Tail = value;
}

unsigned int NamesEntry(void *item, unsigned int value) {
  SetNameMode(item, value);
  SetNameLevel(item, (int)value);
  TestNameReady(item, value);
  SetNameLow(item, value);
  SetNameHigh(item, value);
  SetNameFlag(item, value);
  SetNameWhole(item, value);
  SetNamePart(item, value);
  SetNameInner(item, value);
  SetNameGlobal(value);
  SetNameBeyond(item, value);
  SetNameOverlap(item, value);
  SetNameOnPlain(item, value);
  SetNameLost(item, value);
  return GetNameCount(item) + SumNameFlags(*(struct NameFlags *)item) + (unsigned int)GetNameLevel(item);
}
