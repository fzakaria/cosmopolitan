#ifndef COSMOPOLITAN_THIRD_PARTY_GETOPT_LONG_H_
#define COSMOPOLITAN_THIRD_PARTY_GETOPT_LONG_H_

#define no_argument       0
#define required_argument 1
#define optional_argument 2

#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

struct option {
  const char *name;
  int has_arg;
  int *flag;
  int val;
};

int getopt_long(int, char *const *, const char *, const struct option *, int *);
int getopt_long_only(int, char *const *, const char *, const struct option *,
                     int *);

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_THIRD_PARTY_GETOPT_LONG_H_ */
