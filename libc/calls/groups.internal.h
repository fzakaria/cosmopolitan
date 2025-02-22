#ifndef COSMOPOLITAN_LIBC_CALLS_GROUPS_INTERNAL_H_
#define COSMOPOLITAN_LIBC_CALLS_GROUPS_INTERNAL_H_
#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

int sys_getgroups(int size, uint32_t list[]);
int sys_setgroups(size_t size, uint32_t list[]);

const char *DescribeGidList(char[128], int, int, const uint32_t list[]);
#define DescribeGidList(rc, length, gidlist) \
  DescribeGidList(alloca(128), rc, length, gidlist)

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_CALLS_GROUPS_INTERNAL_H_ */
