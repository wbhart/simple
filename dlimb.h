#include "simple.h"

#ifndef DLIMB_H
#define DLIMB_H

#define __adc(r, a, b, cy) \
   do { \
      dlimb_t __t = (dlimb_t) (a) + (dlimb_t) (b) + (dlimb_t) (cy); \
      (r) = (limb_t) __t; \
      (cy) = (__t >> LIMB_BITS); \
   } while (0)

#define __sbb(r, a, b, bw) \
   do { \
      dlimb_t __t = (dlimb_t) (a) - (dlimb_t) (b) - (dlimb_t) (bw); \
      (r) = (limb_t) __t; \
      (bw) = -(__t >> LIMB_BITS); \
   } while (0)

#define __shl(r, a, bits, cy) \
   do { \
      dlimb_t __t = (((dlimb_t) (a)) << (bits)); \
      (r) = (limb_t) __t + (limb_t) (cy); \
      (cy) = (__t >> LIMB_BITS); \
   } while (0)

#define __shr(r, a, bits, cy) \
   do { \
      dlimb_t __t = (((dlimb_t) (a)) << (bits)); \
      (r) = (__t >> LIMB_BITS) + (limb_t) (cy); \
      (cy) = (limb_t) __t; \
   } while (0)

#define __mul(r, a, c, cy) \
   do { \
      dlimb_t __t = (dlimb_t) (a) * (dlimb_t) (c) + (dlimb_t) (cy); \
      (r) = (limb_t) __t; \
      (cy) = (__t >> LIMB_BITS); \
   } while (0)

#define __div(q, a, d, cy) \
   do { \
      dlimb_t __t = (((dlimb_t) (cy)) << LIMB_BITS) + (dlimb_t) (a); \
      (q) = (limb_t) (__t / (dlimb_t) (d)); \
      (cy) = (limb_t) (__t % (dlimb_t) (d)); \
   } while (0)

#define __addmul(r, a, c, cy) \
   do { \
      dlimb_t __t = (dlimb_t) (r) + (dlimb_t) (a) * (dlimb_t) (c) + (dlimb_t) (cy); \
      (r) = (limb_t) __t; \
      (cy) = (__t >> LIMB_BITS); \
   } while (0)

#define __submul(r, a, c, bw) \
   do { \
      dlimb_t __t = (dlimb_t) (r) - (dlimb_t) (a) * (dlimb_t) (c) - (dlimb_t) (bw); \
      (r) = (limb_t) __t; \
      (bw) = -(__t >> LIMB_BITS); \
   } while (0)

#endif