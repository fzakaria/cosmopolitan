#include "libc/x/x.h"
/* clang-format off */

static _Atomic(void *) cp949_encmap_ptr;
static const unsigned char cp949_encmap_rodata[] = {
  0xcd, 0xd0, 0x5b, 0x48, 0x93, 0x61, 0x18, 0x07, 0xf0, 0xe7, 0xfd, 0x0e, 0xfb,
  0x76, 0xe8, 0x6b, 0x6d, 0x6a, 0xab, 0x65, 0xa6, 0x35, 0x9d, 0x1d, 0xb6, 0xd4,
  0xa5, 0x36, 0x2d, 0xb5, 0xa5, 0x56, 0xeb, 0xe8, 0x3c, 0x55, 0x5a, 0xae, 0xe3,
  0x4c, 0xb3, 0xb3, 0xd9, 0x61, 0xb9, 0xd1, 0x45, 0x04, 0x81, 0xd0, 0x45, 0x37,
  0xe9, 0x4d, 0x44, 0x77, 0x5d, 0x15, 0x04, 0x42, 0x37, 0x41, 0x20, 0x5d, 0x14,
  0x4e, 0x82, 0x84, 0xf0, 0xa6, 0x13, 0x8d, 0xa2, 0xc0, 0xd9, 0x94, 0xef, 0xdb,
  0xfb, 0xbe, 0x3d, 0xd7, 0x5d, 0xd5, 0x8d, 0xf4, 0x87, 0xdf, 0xcd, 0x1f, 0x1e,
  0x78, 0xf8, 0x13, 0x78, 0xc0, 0xba, 0xc0, 0x16, 0x79, 0x06, 0x63, 0x53, 0xaf,
  0xe1, 0xee, 0x2b, 0x03, 0x21, 0x4d, 0x30, 0x8f, 0x69, 0x27, 0x39, 0x8f, 0x7f,
  0x12, 0xf1, 0xed, 0x0b, 0x01, 0x1e, 0x45, 0x44, 0xbb, 0xbd, 0x5b, 0x0c, 0x27,
  0xa7, 0x45, 0x48, 0xbc, 0x94, 0xe4, 0xbe, 0xbf, 0xb9, 0xf7, 0xc8, 0x90, 0x76,
  0x19, 0x4a, 0x87, 0x6e, 0x1a, 0x20, 0x26, 0x28, 0xf1, 0xa9, 0xf9, 0xfa, 0x3b,
  0xac, 0x80, 0xde, 0x69, 0x24, 0x5a, 0x9b, 0x49, 0xe0, 0x2d, 0x66, 0xa0, 0x21,
  0x0b, 0xf0, 0xd0, 0x02, 0x79, 0xae, 0x51, 0x15, 0xb5, 0x9a, 0x85, 0x12, 0xf3,
  0x5b, 0x0d, 0x9a, 0x77, 0x91, 0x98, 0x29, 0xb6, 0x01, 0x2d, 0xb2, 0x5b, 0xb9,
  0x23, 0x8b, 0x24, 0x21, 0x5b, 0xd6, 0xd2, 0xd9, 0x84, 0xa6, 0x72, 0x14, 0xf6,
  0x6d, 0xb1, 0xa0, 0x7f, 0x76, 0x10, 0xfe, 0x69, 0x89, 0x55, 0x4f, 0x2c, 0x25,
  0x7c, 0xdc, 0x09, 0x7c, 0x7c, 0x19, 0x99, 0x1d, 0xcb, 0x55, 0xd9, 0xe8, 0x72,
  0xe0, 0xa3, 0x79, 0x06, 0xfe, 0x74, 0x05, 0xb0, 0x27, 0xf9, 0x76, 0x6d, 0xb8,
  0x00, 0xf8, 0xf0, 0x4a, 0x41, 0xbf, 0xb7, 0x4a, 0xfa, 0x3e, 0xe8, 0x32, 0xa6,
  0x7a, 0x0a, 0x2d, 0x7a, 0x47, 0x91, 0x83, 0xd7, 0xbb, 0x09, 0x0b, 0x14, 0x13,
  0x5a, 0xbb, 0x5a, 0xe2, 0xd5, 0x6b, 0x80, 0xfa, 0xd7, 0x9a, 0x99, 0x77, 0x1d,
  0x99, 0x2d, 0xf4, 0x90, 0x4c, 0x81, 0x17, 0x58, 0xfe, 0x7a, 0x92, 0xca, 0x2a,
  0x11, 0x74, 0xb5, 0x94, 0xe8, 0xc6, 0x32, 0xe0, 0x46, 0x9f, 0x35, 0xf9, 0xd1,
  0xa7, 0xb0, 0xf7, 0x1b, 0x40, 0x7f, 0x57, 0x6e, 0x1a, 0xe9, 0xad, 0xa8, 0xc8,
  0x94, 0x55, 0x02, 0x2d, 0xd9, 0x28, 0x30, 0x8f, 0x5f, 0x66, 0xee, 0x2a, 0x42,
  0x5d, 0xd5, 0x62, 0x26, 0x6f, 0x93, 0x8d, 0xab, 0x9b, 0x05, 0x66, 0xae, 0x01,
  0x66, 0xaa, 0x95, 0xa9, 0x50, 0xa7, 0xcc, 0xcd, 0xd4, 0x01, 0x4b, 0x6d, 0x81,
  0xfb, 0x43, 0x81, 0x4a, 0xda, 0xba, 0x55, 0x4a, 0x35, 0xd4, 0x9b, 0x59, 0x55,
  0x83, 0x48, 0xcb, 0x1b, 0x81, 0xfa, 0xb6, 0x09, 0xbf, 0xdc, 0xdb, 0xd5, 0x8c,
  0x63, 0x87, 0x94, 0x36, 0x07, 0xa5, 0xd8, 0xad, 0xe0, 0xc0, 0x87, 0xe9, 0x60,
  0xae, 0x3e, 0xb1, 0x13, 0xf8, 0xc4, 0x2e, 0x60, 0x89, 0xdd, 0x22, 0x7f, 0xb3,
  0x87, 0xfc, 0x78, 0xbe, 0xd7, 0xf9, 0xf5, 0xce, 0x3e, 0x35, 0xdd, 0xdf, 0x64,
  0xd2, 0x22, 0x21, 0xe7, 0x4c, 0xa0, 0x59, 0x19, 0xf9, 0xd7, 0xdd, 0x27, 0x9b,
  0x81, 0x4f, 0xb6, 0xa0, 0x56, 0xd4, 0x86, 0xda, 0xd1, 0x7e, 0x74, 0x00, 0x1d,
  0x44, 0x1d, 0xa8, 0x13, 0x1d, 0x42, 0x87, 0x51, 0x17, 0x0a, 0xa3, 0x23, 0xe8,
  0x28, 0x3a, 0x86, 0x8e, 0xa3, 0x13, 0xe8, 0x24, 0x8a, 0xa0, 0x6e, 0x74, 0x0a,
  0xf5, 0xa0, 0x5e, 0x74, 0x1a, 0xf5, 0xa1, 0x33, 0xe8, 0x2c, 0x3a, 0x87, 0xce,
  0xa3, 0x0b, 0xe8, 0x22, 0xba, 0x84, 0xfa, 0xd1, 0x65, 0x34, 0x80, 0xae, 0xa0,
  0xab, 0xe8, 0x1a, 0xba, 0x8e, 0xa2, 0xe8, 0x06, 0x1a, 0x84, 0x87, 0xf0, 0x1f,
  0x24, 0x1a, 0x03, 0x1e, 0x8d, 0x83, 0xe5, 0xcf, 0xfe, 0x76, 0x9c, 0x7c, 0xf9,
  0x0d,
};

optimizesize void *cp949_encmap(void) {
  return xload(&cp949_encmap_ptr,
               cp949_encmap_rodata,
               534, 1024); /* 52.1484% profit */
}
