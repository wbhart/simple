#include <nat.h>
#include <znat.h>

using namespace std;

int main()
{
   long i, j;
   
   znat_t a = znat_t(1234567890123456789UL);
   znat_t b = znat_t(1234567890123456789UL);
   znat_t c;

   cout << a << endl;
   
   for (i = 0; i < 50000000; i++)
      a += b;
   
   for (i = 0; i < 50000000; i++)
      a -= b;
   
   for (i = 0; i < 50000000; i++)
      a -= b;
   
   for (i = 0; i < 50000000; i++)
      a += b;
   
   cout << a << endl;
   
   for (i = 0; i < 100000; i++)
   {
      for (j = 0; j < 50; j++)
         a <<= j;

      for (j = 0; j < 50; j++)
         a >>= j;

      a.sign = -a.sign;

      for (j = 0; j < 50; j++)
         a <<= j;

      for (j = 0; j < 50; j++)
         a >>= j;

      a.sign = -a.sign;
   }

   cout << a << endl;
   
   a.sign = -a.sign;
   
   for (i = 0; i < 1000000; i++)
   {
      for (j = 0; j < 10; j++)
         a *= 1234567890123456789UL;
   
      for (j = 0; j < 10; j++)
         a /= 1234567890123456789UL;
   }
   
   a.sign = -a.sign;

   cout << a << endl;
   
   for (i = 0; i < 100000000; i++)
      a += 1234567890123456789UL;
   
   for (i = 0; i < 100000000; i++)
      a -= 1234567890123456789UL;
   
   cout << a << endl;
   
   c = a * 1000UL + 1234567890123456789UL;

   for (i = 0; i < 1000000; i++)
   {
      b = c;
      for (j = 0; j < 5; j++)
         b = b * b;
   }

   a = a * a * a;

   cout << b << endl;

   for (i = 0; i < 1000000; i++)
   {
      b = b * a;
      b = b / a;
   }

   cout << a << endl;
   cout << b << endl;
   cout << c << endl;
   
   return 0;
}