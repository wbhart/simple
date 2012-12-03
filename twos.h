#include "simple.h"

#ifndef TWOS_H
#define TWOS_H

limb_t add(limb_t * r, limb_t * a, limb_t * b, long len, limb_t ci);

limb_t sub(limb_t * r, limb_t * a, limb_t * b, long len, limb_t bi);

limb_t mul(limb_t * r, limb_t * a, long len, limb_t c, limb_t ci);

limb_t addmul(limb_t * r, limb_t * a, long len, limb_t c, limb_t ci);

limb_t submul(limb_t * r, limb_t * a, long len, limb_t c, limb_t bi);

int cmp(limb_t * a, limb_t * b, long len);

#endif
