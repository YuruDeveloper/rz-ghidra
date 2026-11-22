struct MatrixRecord {
  unsigned char Grid[1][2];
  unsigned char Tail;
};

__attribute__((noinline)) void WriteGrid(struct MatrixRecord *record,
                                         unsigned char value) {
  record->Grid[0][1] = value;
}

__attribute__((noinline)) void SetTrailer(struct MatrixRecord *record,
                                          unsigned char value) {
  record->Tail = value;
}

void ReviewEntry(struct MatrixRecord *record, unsigned char value) {
  WriteGrid(record, value);
  SetTrailer(record, value);
}
