#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdint.h>

using namespace std;

#ifndef SIMPLE_H
#define SIMPLE_H

#define ulong unsigned long

#if ULONG_MAX == 4294967295U /* 32 bit unsigned long */
typedef uint32_t limb_t;
typedef unsigned int dlimb_t __attribute__((mode(DI)));
#define LIMB_BITS 32

#define count_leading_zeros(count, x)                                 \
  do {                                                                \
    limb_t __cbtmp;                                                \
    __asm__ ("bsrl %1,%0" : "=r" (__cbtmp) : "rm" ((limb_t)(x)));  \
    (count) = __cbtmp ^ 31;                                           \
  } while (0)

#else /* 64 bit unsigned long */
typedef uint64_t limb_t;
typedef unsigned int dlimb_t __attribute__((mode(TI)));
#define LIMB_BITS 64

#define count_leading_zeros(count, x)                                 \
  do {                                                                \
    limb_t __cbtmp;                                                \
    __asm__ ("bsrq %1,%0" : "=r" (__cbtmp) : "rm" ((limb_t)(x)));  \
    (count) = __cbtmp ^ 63;                                           \
  } while (0)

#endif

#define MAX(x, y) ((x) <= (y) ? (y) : (x))
#define MIN(x, y) ((x) >= (y) ? (y) : (x))

#endif