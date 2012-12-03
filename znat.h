#include "simple.h"
#include "nat.h"

#ifndef ZNAT_H
#define ZNAT_H

class znat_t:public nat_t {
public:
   int sign;

   znat_t() : nat_t() { sign = 0; };
   znat_t(limb_t n) : nat_t(n) { sign = (n != 0); };
   znat_t(long n);
   znat_t(const znat_t& n) : nat_t(n) { sign = n.sign; };
   znat_t(const nat_t& n) : nat_t(n) { sign = (n.size() != 0); };
   znat_t operator+(znat_t& b); 
   znat_t operator-(znat_t& b); 
   znat_t& operator+=(znat_t& b); 
   znat_t& operator-=(znat_t& b); 
   znat_t operator+(limb_t cy);
   znat_t operator-(limb_t bw);
   znat_t& operator+=(limb_t cy);
   znat_t& operator-=(limb_t bw);
   znat_t operator<<(ulong bits);
   znat_t& operator<<=(ulong bits);
   znat_t operator>>(ulong bits);
   znat_t& operator>>=(ulong bits);
   znat_t operator*(limb_t c);
   znat_t& operator*=(limb_t c);
   znat_t operator/(limb_t d);
   znat_t operator%(limb_t d);
   znat_t& operator/=(limb_t c);
   znat_t& operator%=(limb_t c);
   int operator<=(znat_t& b);
   int operator>=(znat_t& b);
   int operator<(znat_t& b);
   int operator>(znat_t& b);
   int operator==(znat_t& b);
   int operator!=(znat_t& b);
   int operator<=(limb_t b);
   int operator>=(limb_t b);
   int operator<(limb_t b);
   int operator>(limb_t b);
   int operator==(limb_t b);
   int operator!=(limb_t b);
   znat_t operator*(znat_t& b);
   znat_t operator/(znat_t& b);
   znat_t operator%(znat_t& b);
};

ostream& operator<<(ostream& os, const znat_t& nat);

znat_t divrem(znat_t& a, limb_t d);

znat_t divrem(znat_t& a, znat_t& b);

znat_t gcd(znat_t& a, znat_t& b);

#endif

