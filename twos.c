#include "twos.h"
#include "dlimb.h"

limb_t add(limb_t * r, limb_t * a, limb_t * b, long len, limb_t cy)
{
   long i;
   
   for (i = 0; i < len; i++)
      __adc(r[i], a[i], b[i], cy);
    
   return cy;
}

limb_t sub(limb_t * r, limb_t * a, limb_t * b, long len, limb_t bw)
{
   long i;
   
   for (i = 0; i < len; i++)
      __sbb(r[i], a[i], b[i], bw);
    
   return bw;
}

limb_t mul(limb_t * r, limb_t * a, long len, limb_t c, limb_t cy)
{
   long i;
   
   for (i = 0; i < len; i++)
      __mul(r[i], a[i], c, cy);
    
   return cy;
}

limb_t addmul(limb_t * r, limb_t * a, long len, limb_t c, limb_t cy)
{
   long i;
   
   for (i = 0; i < len; i++)
      __addmul(r[i], a[i], c, cy);
    
   return cy;
}

limb_t submul(limb_t * r, limb_t * a, long len, limb_t c, limb_t bw)
{
   long i;
   
   for (i = 0; i < len; i++)
      __submul(r[i], a[i], c, bw);
    
   return bw;
}

int cmp(limb_t * a, limb_t * b, long len)
{
   long i;
   
   for (i = len - 1; i >= 0; i--)
   {
      if (a[i] > b[i])
         return 1;
      if (a[i] < b[i])
         return -1;
   }
    
   return 0;
}
