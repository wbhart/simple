#include <simple.h>
#include "dlimb.h"
#include "twos.h"

#ifndef NAT_H
#define NAT_H

class nat_t:public vector<limb_t> {
public:
   nat_t(long len) : vector<limb_t>(len) { };
   nat_t(limb_t n) : vector<limb_t>(1) { (*this)[0] = n; };
   nat_t() : vector<limb_t>(0) {};
   nat_t(const nat_t& n) : vector<limb_t>(n) {};
   nat_t operator+(nat_t& b);
   nat_t operator-(nat_t& b);
   nat_t& operator+=(nat_t& b);
   nat_t& operator-=(nat_t& b);
   nat_t operator+(limb_t cy);
   nat_t operator-(limb_t bw);
   nat_t& operator+=(limb_t cy);
   nat_t& operator-=(limb_t bw);
   nat_t operator<<(ulong bits);
   nat_t& operator<<=(ulong bits);
   nat_t operator>>(ulong bits);
   nat_t& operator>>=(ulong bits);
   nat_t operator*(limb_t c);
   nat_t& operator*=(limb_t c);
   nat_t operator/(limb_t d);
   limb_t operator%(limb_t d);
   nat_t& operator/=(limb_t c);
   nat_t& operator%=(limb_t c);
   int operator<=(nat_t& b);
   int operator>=(nat_t& b);
   int operator<(nat_t& b);
   int operator>(nat_t& b);
   int operator==(nat_t& b);
   int operator!=(nat_t& b);
   int operator<=(limb_t b);
   int operator>=(limb_t b);
   int operator<(limb_t b);
   int operator>(limb_t b);
   int operator==(limb_t b);
   int operator!=(limb_t b); 
   nat_t operator*(nat_t& b);
   nat_t operator/(nat_t& b);
   nat_t operator%(nat_t& b);
};

string to_string(const nat_t& n);

ostream& operator<<(ostream& os, const nat_t& nat);

nat_t divrem(nat_t& a, limb_t d);

nat_t divrem(nat_t& a, nat_t& b);

nat_t gcd(nat_t& a, nat_t& b);

#endif
