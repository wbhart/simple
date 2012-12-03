#include <nat.h>

nat_t nat_t::operator+(nat_t& b)
{
   const long len1 = size();
   const long len2 = b.size();
   long i, min = MIN(len1, len2);
   long max = MAX(len1, len2);
   nat_t r = nat_t(max);
   
   limb_t cy = 0;

   for (i = 0; i < min; i++)
      __adc(r[i], (*this)[i], b[i], cy);
   
   for ( ; i < len2; i++)
      __adc(r[i], 0, b[i], cy);
    
   for ( ; i < len1; i++)
      __adc(r[i], 0, (*this)[i], cy);
  
   if ((limb_t) cy)
      r.push_back((limb_t) cy);

   return r;
}

nat_t nat_t::operator-(nat_t& b)
{
   const long len1 = size();
   const long len2 = b.size();
   long i;
   nat_t r = nat_t(len1);
   
   limb_t bw = 0;

   for (i = 0; i < len2; i++)
      __sbb(r[i], (*this)[i], b[i], bw);
   
   for ( ; i < len1; i++)
      __sbb(r[i], (*this)[i], 0, bw);
    
   while (i-- > 0 && r[i] == 0)
      r.pop_back();

   return r;
}

nat_t& nat_t::operator+=(nat_t& b)
{
   const long len1 = size();
   const long len2 = b.size();
   long i, min = MIN(len1, len2);
   long max = MAX(len1, len2);
   limb_t cy = 0;

   for (i = 0; i < min; i++)
      __adc((*this)[i], (*this)[i], b[i], cy);
   
   for ( ; i < len2; i++)
      __adc((*this)[i], 0, b[i], cy);
    
   for ( ; i < len1 && cy != 0; i++)
      __adc((*this)[i], 0, (*this)[i], cy);
   
   if ((limb_t) cy)
      push_back((limb_t) cy);

   return *this;
}

nat_t& nat_t::operator-=(nat_t& b)
{
   const long len1 = size();
   const long len2 = b.size();
   long i;
   
   limb_t bw = 0;

   for (i = 0; i < len2; i++)
      __sbb((*this)[i], (*this)[i], b[i], bw);
   
   for ( ; i < len1 && bw != 0; i++)
      __sbb((*this)[i], (*this)[i], 0, bw);
    
   while (i-- > 0 && (*this)[i] == 0)
      pop_back();

   return *this;
}

nat_t nat_t::operator+(limb_t cy)
{
   const long len = size();
   long i;
   nat_t r = nat_t(len);
   
   for (i = 0; i < len; i++)
      __adc(r[i], 0, (*this)[i], cy);
  
   if ((limb_t) cy)
      r.push_back((limb_t) cy);

   return r;
}

nat_t& nat_t::operator+=(limb_t cy)
{
   const long len = size();
   long i;
   
   for (i = 0; i < len && cy != 0; i++)
      __adc((*this)[i], 0, (*this)[i], cy);
  
   if ((limb_t) cy)
      push_back((limb_t) cy);

   return *this;
}

nat_t nat_t::operator-(limb_t bw)
{
   const long len = size();
   long i;
   nat_t r = nat_t(len);
   
   for (i = 0; i < len; i++)
      __sbb(r[i], (*this)[i], 0, bw);
  
   while (i-- > 0 && r[i] == 0)
      r.pop_back();

   return r;
}

nat_t& nat_t::operator-=(limb_t bw)
{
   const long len = size();
   long i;
   
   for (i = 0; i < len && bw != 0; i++)
      __sbb((*this)[i], (*this)[i], 0, bw);
  
   while (i-- > 0 && (*this)[i] == 0)
      pop_back();

   return *this;
}

nat_t nat_t::operator<<(ulong bits)
{
   const long w = bits / LIMB_BITS;
   const long b = bits % LIMB_BITS;
   const long len = size();
   long i;
   nat_t r = nat_t(w + len);
   
   limb_t cy = 0;

   for (i = 0; i < w; i++)
      r[i] = 0;

   for (i = 0; i < len; i++)
      __shl(r[w + i], (*this)[i], b, cy);
   
   if ((limb_t) cy)
      r.push_back((limb_t) cy);

   return r;
}

nat_t& nat_t::operator<<=(ulong bits)
{
   const long w = bits / LIMB_BITS;
   const long b = bits % LIMB_BITS;
   const long len = size();
   long i;
   (*this).resize(len + w);

   limb_t cy = 0;

   for (i = 0; i < len; i++)
      __shl((*this)[i], (*this)[i], b, cy);
   
   if (w)
   {
      for (i = len - 1; i >= 0; i--)
         (*this)[i + w] = (*this)[i];
         
      for (i = 0; i < w; i++)
         (*this)[i] = 0;
   }

   if ((limb_t) cy)
      push_back((limb_t) cy);

   return *this;
}

nat_t nat_t::operator>>(ulong bits)
{
   const long w = bits / LIMB_BITS;
   const long b = LIMB_BITS - (bits % LIMB_BITS);
   const long len = size() - w;
   long i;
   nat_t r = nat_t(len);
   
   limb_t cy = 0;
   
   for (i = len - 1; i >= 0; i--)
      __shr(r[i], (*this)[w + i], b, cy);
   
   if (len != 0 && r[len - 1] == 0)
      r.pop_back();

   return r;
}

nat_t& nat_t::operator>>=(ulong bits)
{
   const long w = bits / LIMB_BITS;
   const long b = LIMB_BITS - (bits % LIMB_BITS);
   const long len = size() - w;
   long i;
   
   limb_t cy = 0;
   
   for (i = len - 1; i >= 0; i--)
      __shr((*this)[w + i], (*this)[w + i], b, cy);
   
   if (w)
   {
      for (i = 0; i < len; i++)
         (*this)[i] = (*this)[w + i];
   }
   
   resize(len);

   if (len != 0 && (*this)[len - 1] == 0)
      pop_back();

   return *this;
}

nat_t nat_t::operator*(limb_t c)
{
   const long len = size();
   long i;
   nat_t r = nat_t(len);
   
   limb_t cy = 0;

   for (i = 0; i < len; i++)
      __mul(r[i], (*this)[i], c, cy);
    
   if ((limb_t) cy)
      r.push_back((limb_t) cy);

   return r;
}

nat_t& nat_t::operator*=(limb_t c)
{
   const long len = size();
   long i;
   
   limb_t cy = 0;

   for (i = 0; i < len; i++)
      __mul((*this)[i], (*this)[i], c, cy);
    
   if ((limb_t) cy)
      push_back((limb_t) cy);

   return *this;
}

nat_t nat_t::operator/(limb_t d)
{
   const long len = size();
   long i;
   nat_t r = nat_t(len);
   
   limb_t cy = 0;

   for (i = len - 1; i >= 0; i--)
      __div(r[i], (*this)[i], d, cy);
    
   if (r[len - 1] == 0)
      r.pop_back();

   return r;
}

limb_t nat_t::operator%(limb_t d)
{
   const long len = size();
   long i;
   limb_t r;
   
   limb_t cy = 0;

   for (i = len - 1; i >= 0; i--)
      __div(r, (*this)[i], d, cy);
    
   return (limb_t) cy;
}

nat_t& nat_t::operator%=(limb_t d)
{
   const long len = size();
   long i;
   limb_t r;
   
   limb_t cy = 0;

   for (i = len - 1; i >= 0; i--)
      __div((*this)[i], (*this)[i], d, cy);
    
   if (cy)
   {
      resize(1);
      (*this)[0] = cy;
   } else
      resize(0);

   return *this;
}

nat_t& nat_t::operator/=(limb_t d)
{
   const long len = size();
   long i;
   
   limb_t cy = 0;

   for (i = len - 1; i >= 0; i--)
      __div((*this)[i], (*this)[i], d, cy);
    
   if ((*this)[len - 1] == 0)
      pop_back();

   return *this;
}

int nat_t::operator<=(nat_t& b)
{
   const long len1 = size();
   const long len2 = b.size();
   
   if (len1 < len2)
      return 1;
   
   if (len1 > len2)
      return 0;

   long i = len1;

   while (i--)
   {
      if ((*this)[i] < b[i])
         return 1;
      if ((*this)[i] > b[i])
         return 1;
   }

   return 1;
}

int nat_t::operator<(nat_t& b)
{
   const long len1 = size();
   const long len2 = b.size();
   
   if (len1 < len2)
      return 1;
   
   if (len1 > len2)
      return 0;

   long i = len1;

   while (i--)
   {
      if ((*this)[i] < b[i])
         return 1;
      if ((*this)[i] > b[i])
         return 0;
   }

   return 0;
}

int nat_t::operator>(nat_t& b)
{
   return !((*this) <= b);
}

int nat_t::operator>=(nat_t& b)
{
   return !((*this) < b);
}

int nat_t::operator==(nat_t& b)
{
   const long len1 = size();
   const long len2 = b.size();
   
   if (len1 < len2)
      return 0;
   
   if (len1 > len2)
      return 0;

   long i = len1;

   while (i--)
   {
      if ((*this)[i] != b[i])
         return 0;
   }

   return 1;
}

int nat_t::operator!=(nat_t& b)
{
   return !((*this) == b);
}

int nat_t::operator<=(limb_t b)
{
   const long len = size();
   
   if (len > 1)
      return 0;
   
   if (len == 0)
      return 1;

   return ((*this)[0] <= b);
}

int nat_t::operator>(limb_t b)
{
   return !(*this <= b);
}

int nat_t::operator<(limb_t b)
{
   const long len = size();
   
   if (len > 1)
      return 0;
   
   if (len == 0)
      return (b == 0);

   return ((*this)[0] < b);
}

int nat_t::operator>=(limb_t b)
{
   return !(*this < b);
}

int nat_t::operator==(limb_t b)
{
   const long len = size();
   
   if (len > 1)
      return 0;
   
   if (len == 0)
      return (b == 0);

   return ((*this)[0] == b);
}

int nat_t::operator!=(limb_t b)
{
   return !(*this == b);
}

string to_string(const nat_t& n)
{
   nat_t m = n;

   if (m.size() == 0)
      return string("0");

   string str = string();

   while (m.size() != 0)
   {
      char r = (m % 10) + 48;
      str.push_back(r);
      m /= 10;
   }

   reverse(str.begin(), str.end());
   
   return str;
}

ostream& operator<<(ostream& os, const nat_t& nat)
{
   os << to_string(nat) << endl;
   
   return os;
}

nat_t nat_t::operator*(nat_t& b)
{
   const long len1 = size();
   const long len2 = b.size();
   long i, j;
   
   if (len1 == 0 || len2 == 0)
      return nat_t(0UL);

   nat_t r = nat_t(len1 + len2);
   
   limb_t * r_ptr = r.data();
   limb_t * a_ptr = data();
   limb_t cy;

   for (i = 0; i < len2; i++, r_ptr++)
   {
      for (j = 0, cy = 0; j < len1; j++)
         __addmul(r_ptr[j], a_ptr[j], b[i], cy);

      r_ptr[j] = cy;
   }
   
   if (cy == 0)
      r.pop_back();

   return r;
}

nat_t nat_t::operator/(nat_t& b)
{
   long i, j;
   
   if (b.size() == 1)
      return *this/b[0];

   nat_t r = nat_t(*this);
   nat_t b2 = nat_t(b);

   limb_t count;
   count_leading_zeros(count, b.data()[b.size() - 1]);
   if (count)
   {
      r <<= count;
      b2 <<= count;
   }

   const long len1 = r.size();
   const long len2 = b2.size();

   if (len1 < len2)
      return nat_t(0UL);

   nat_t q = nat_t(len1 - len2 + 1);
   
   limb_t * q_ptr = q.data();
   limb_t * r_ptr = r.data();
   limb_t * b_ptr = b2.data();
   dlimb_t d = b_ptr[len2 - 1] + 1;
   dlimb_t t = 0;
   limb_t cy;

   if (cmp(r_ptr + len1 - len2, b_ptr, len2) >= 0)
   {
      q[len1 - len2]++;
      sub(r_ptr + len1 - len2, r_ptr + len1 - len2, b_ptr, len2, 0);
   }
   
   for (i = len1 - len2 - 1; i >= 0; i--)
   {
      t = ((dlimb_t) r_ptr[i + len2] << LIMB_BITS) + r_ptr[i + len2 - 1];
      q[i] = t/d;
      
      r_ptr[i + len2] -= submul(r_ptr + i, b_ptr, len2, q[i], 0);
      
      while (r_ptr[i + len2] || cmp(r_ptr + i, b_ptr, len2) >= 0)
      {
         q[i]++;
         r_ptr[i + len2] -= sub(r_ptr + i, r_ptr + i, b_ptr, len2, 0);
      }
   }

   if (q_ptr[len1 - len2] == 0)
      q.pop_back();

   return q;
}

nat_t nat_t::operator%(nat_t& b)
{
   long i, j;
   
   if (b.size() == 1)
      return nat_t(*this%b[0]);

   nat_t r = nat_t(*this);
   nat_t b2 = nat_t(b);

   limb_t count;
   count_leading_zeros(count, b.data()[b.size() - 1]);
   if (count)
   {
      r <<= count;
      b2 <<= count;
   }

   const long len1 = r.size();
   const long len2 = b2.size();

   if (len1 < len2)
   {
      if (count)
         return r >> count;
      else
         return r;
   }

   limb_t q;
   limb_t * r_ptr = r.data();
   limb_t * b_ptr = b2.data();
   dlimb_t d = b_ptr[len2 - 1] + 1;
   dlimb_t t = 0;
   limb_t cy;

   if (cmp(r_ptr + len1 - len2, b_ptr, len2) >= 0)
      sub(r_ptr + len1 - len2, r_ptr + len1 - len2, b_ptr, len2, 0);
   
   for (i = len1 - len2 - 1; i >= 0; i--)
   {
      t = ((dlimb_t) r_ptr[i + len2] << LIMB_BITS) + r_ptr[i + len2 - 1];
      q = t/d;
      
      r_ptr[i + len2] -= submul(r_ptr + i, b_ptr, len2, q, 0);
      
      while (r_ptr[i + len2] || cmp(r_ptr + i, b_ptr, len2) >= 0)
         r_ptr[i + len2] -= sub(r_ptr + i, r_ptr + i, b_ptr, len2, 0);
   }

   for (i = len1 - 1; i >= 0 && r[i] == 0; i--)
      r.pop_back();

   if (count) 
      return r >> count;
   else
      return r;
}

nat_t divrem(nat_t& a, nat_t& b)
{
   long i, j;
   
   if (b.size() == 1)
      return divrem(a, b[0]);

   nat_t b2 = nat_t(b);

   limb_t count;
   count_leading_zeros(count, b.data()[b.size() - 1]);
   if (count)
   {
      a <<= count;
      b2 <<= count;
   }

   const long len1 = a.size();
   const long len2 = b2.size();

   if (len1 < len2)
   {
      if (count)
         a >>= count;
      return nat_t(0UL);
   }

   nat_t q = nat_t(len1 - len2 + 1);
   
   limb_t * q_ptr = q.data();
   limb_t * r_ptr = a.data();
   limb_t * b_ptr = b2.data();
   dlimb_t d = b_ptr[len2 - 1] + 1;
   dlimb_t t = 0;
   limb_t cy;

   if (cmp(r_ptr + len1 - len2, b_ptr, len2) >= 0)
   {
      q[len1 - len2]++;
      sub(r_ptr + len1 - len2, r_ptr + len1 - len2, b_ptr, len2, 0);
   }
   
   for (i = len1 - len2 - 1; i >= 0; i--)
   {
      t = ((dlimb_t) r_ptr[i + len2] << LIMB_BITS) + r_ptr[i + len2 - 1];
      q[i] = t/d;
      
      r_ptr[i + len2] -= submul(r_ptr + i, b_ptr, len2, q[i], 0);
      
      while (r_ptr[i + len2] || cmp(r_ptr + i, b_ptr, len2) >= 0)
      {
         q[i]++;
         r_ptr[i + len2] -= sub(r_ptr + i, r_ptr + i, b_ptr, len2, 0);
      }
   }

   if (q_ptr[len1 - len2] == 0)
      q.pop_back();

   if (count) 
      a >>= count;

   return q;
}

nat_t divrem(nat_t& a, limb_t d)
{
   const long len = a.size();
   long i;
   nat_t q = nat_t(len);
   
   limb_t cy = 0;

   for (i = len - 1; i >= 0; i--)
      __div(q[i], a[i], d, cy);
    
   if (q[len - 1] == 0)
      q.pop_back();

   if (cy)
   {
      a.resize(1);
      a[0] = cy;
   } else
      a.resize(0);

   return q;
}

nat_t gcd(nat_t& a, nat_t& b)
{
   nat_t a1 = nat_t(a);
   nat_t b1 = nat_t(b);
   
   while (b1.size())
   {
      divrem(a1, b1);
      a1.swap(b1);
   }

   return a1;
}
