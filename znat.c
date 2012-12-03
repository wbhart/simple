#include "znat.h"

znat_t::znat_t(long n) : nat_t(1L)
{
   if (n >= 0)
   {
      (*this)[0] = n;
      sign = (n != 0);
   } else
   {
      (*this)[0] = -n;
      sign = -1;
   }
}

znat_t znat_t::operator+(znat_t& b)
{
   znat_t r;
   
   if ((sign ^ b.sign) < 0) /* different signs */
   {
      if ((*this).nat_t::operator<(b))
      {
         r = znat_t(b.nat_t::operator-(*this));
         r.sign = b.sign;
      } else
      {
         r = znat_t((*this).nat_t::operator-(b));
         r.sign = sign;
      }
   } else /* same signs */
   {
      r = znat_t(b.nat_t::operator+(*this));
      r.sign = b.sign;
   }

   return r;
}

znat_t& znat_t::operator+=(znat_t& b)
{
   if ((sign ^ b.sign) < 0) /* different signs */
   {
      if ((*this).nat_t::operator<(b))
      {
         (*this) = znat_t(b.nat_t::operator-(*this));
         sign = b.sign;
      } else
         (*this).nat_t::operator-=(b);
   } else /* same signs */
   {
      (*this).nat_t::operator+=(b);
      sign = b.sign;
   }
}

znat_t znat_t::operator-(znat_t& b)
{
   znat_t r;
   
   if ((sign ^ b.sign) >= 0) /* same signs */
   {
      if ((*this).nat_t::operator<(b))
      {
         r = znat_t(b.nat_t::operator-(*this));
         r.sign = -b.sign;
      } else
      {
         r = znat_t((*this).nat_t::operator-(b));
         r.sign = sign;
      }
   } else /* different signs */
      r = znat_t(b.nat_t::operator+(*this));

   return r;
}

znat_t& znat_t::operator-=(znat_t& b)
{
   if ((sign ^ b.sign) >= 0) /* same signs */
   {
      if ((*this).nat_t::operator<(b))
      {
         (*this) = znat_t(b.nat_t::operator-(*this));
         sign = -b.sign;
      } else
         (*this).nat_t::operator-=(b);
   } else /* different signs */
      (*this).nat_t::operator+=(b);
}

znat_t znat_t::operator+(limb_t cy)
{
   znat_t r;
   
   if (sign < 0)
   {
      if ((*this).nat_t::operator>(cy))
      {
         r = znat_t((*this).nat_t::operator-(cy));
         r.sign = -1;
      } else
         r = znat_t(cy - (*this)[0]);
   } else
   {
      r = znat_t((*this).nat_t::operator+(cy));
      r.sign = 1;  
   }

   return r;
}

znat_t znat_t::operator-(limb_t cy)
{
   znat_t r;
   
   if (sign < 0)
   {
      r = znat_t((*this).nat_t::operator+(cy));
      r.sign = -1;
   } else
   {
      if ((*this).nat_t::operator>(cy))
      {
         r = znat_t((*this).nat_t::operator-(cy));
         r.sign = 1;
      } else
      {
         r = znat_t(cy - (*this)[0]);
         r.sign = -1;
      }
   }

   return r;
}

znat_t& znat_t::operator+=(limb_t cy)
{
   if (sign < 0)
   {
      if ((*this).nat_t::operator>(cy))
      {
         (*this).nat_t::operator-=(cy);
         sign = -1;
      } else
         (*this) = znat_t(cy - (*this)[0]);
   } else
   {
      (*this).nat_t::operator+=(cy);
      sign = 1;  
   }

   return *this;
}

znat_t& znat_t::operator-=(limb_t cy)
{
   if (sign < 0)
   {
      (*this).nat_t::operator+=(cy);
      sign = -1;
   } else
   {
      if ((*this).nat_t::operator>(cy))
      {
         (*this).nat_t::operator-=(cy);
         sign = 1;
      } else
      {
         (*this) = znat_t(cy - (*this)[0]);
         sign = -sign;
      }
   }

   return *this;
}

znat_t znat_t::operator<<(ulong bits)
{
   znat_t r = znat_t((*this).nat_t::operator<<(bits));
   r.sign = (*this).sign;

   return r;
}

znat_t& znat_t::operator<<=(ulong bits)
{
   (*this).nat_t::operator<<=(bits);
}

znat_t znat_t::operator>>(ulong bits)
{
   znat_t r = znat_t((*this).nat_t::operator>>(bits));
   r.sign = (*this).sign;

   return r;
}

znat_t& znat_t::operator>>=(ulong bits)
{
   (*this).nat_t::operator>>=(bits);
}

znat_t znat_t::operator*(limb_t c)
{
   znat_t r = znat_t((*this).nat_t::operator*(c));
   r.sign = (*this).sign;

   return r;
}

znat_t& znat_t::operator*=(limb_t c)
{
   (*this).nat_t::operator*=(c);
}

znat_t znat_t::operator/(limb_t c)
{
   znat_t r = znat_t((*this).nat_t::operator/(c));
   r.sign = (*this).sign;

   return r;
}

znat_t& znat_t::operator/=(limb_t c)
{
   (*this).nat_t::operator/=(c);
}

znat_t znat_t::operator%(limb_t c)
{
   znat_t r = znat_t((*this).nat_t::operator%(c));
   r.sign = (*this).sign;

   return r;
}

znat_t& znat_t::operator%=(limb_t c)
{
   (*this).nat_t::operator%=(c);
}

int znat_t::operator<=(znat_t& b)
{
   if (sign < b.sign)
      return 1;

   if (sign > b.sign)
      return -1;

   if (sign >= 0)
      return (*this).nat_t::operator<=(b);
   else
      return (*this).nat_t::operator>(b);
}

int znat_t::operator>(znat_t& b)
{
   return !((*this) <= b);
}

int znat_t::operator>=(znat_t& b)
{
   if (sign > b.sign)
      return 1;

   if (sign < b.sign)
      return -1;

   if (sign >= 0)
      return (*this).nat_t::operator>=(b);
   else
      return (*this).nat_t::operator<(b);
}

int znat_t::operator<(znat_t& b)
{
   return !((*this) >= b);
}

int znat_t::operator==(znat_t& b)
{
   return (sign == b.sign && (*this).nat_t::operator==(b));
}

int znat_t::operator!=(znat_t& b)
{
   return !((*this) == b);
}

int znat_t::operator<=(limb_t b)
{
   if (sign <= 0)
      return 1;

   return (*this).nat_t::operator<=(b);
}

int znat_t::operator>(limb_t b)
{
   return !((*this) <= b);
}

int znat_t::operator>=(limb_t b)
{
   if (sign < 0)
      return -1;

   return (*this).nat_t::operator>=(b);
}

int znat_t::operator<(limb_t b)
{
   return !((*this) >= b);
}

int znat_t::operator==(limb_t b)
{
   return (((sign > 0 && b > 0) && (*this).nat_t::operator==(b))
        || (sign == 0 && b == 0));
}

int znat_t::operator!=(limb_t b)
{
   return !((*this) == b);
}

znat_t znat_t::operator*(znat_t& b)
{
   znat_t r = znat_t((*this).nat_t::operator*(b));
   
   r.sign = sign * b.sign;

   return r;
}

znat_t znat_t::operator/(znat_t& b)
{
   znat_t r = znat_t((*this).nat_t::operator/(b));
   
   r.sign = sign * b.sign;

   return r;
}

znat_t znat_t::operator%(znat_t& b)
{
   znat_t r = znat_t((*this).nat_t::operator%(b));
   
   r.sign = sign * b.sign;

   return r;
}

ostream& operator<<(ostream& os, const znat_t& nat)
{
   if (nat.sign < 0)
      os << "-";
   
   os << to_string(nat) << endl;
   
   return os;
}

znat_t divrem(znat_t& a, limb_t d)
{
   znat_t r = znat_t(divrem((nat_t&) a, d));
   r.sign = a.sign;

   return r;
}

znat_t divrem(znat_t& a, znat_t& b)
{
   znat_t r = znat_t(divrem((nat_t&) a, (nat_t&) b));
   r.sign = a.sign * b.sign;

   return r;
}

znat_t gcd(znat_t& a, znat_t& b)
{
   znat_t r = znat_t(gcd((nat_t&) a, (nat_t&) b));
   if (a.sign == b.sign)
      r.sign = a.sign;

   return r;
}
