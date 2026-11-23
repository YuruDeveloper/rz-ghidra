struct Pair {
  unsigned short Kind;
  unsigned int Quantity;
};

struct {
  unsigned short Kind;
  unsigned int Quantity;
} Things[3];

struct Pair Pairs[3];
int Numbers[4];

__attribute__((noinline)) void SetThings(unsigned int value) {
  Things[2].Quantity = value;
  Pairs[2].Quantity = value;
  Numbers[3] = (int)value;
}

unsigned int GlobalEntry(unsigned int value) {
  SetThings(value);
  return Things[1].Quantity + Pairs[1].Quantity + (unsigned int)Numbers[1];
}
