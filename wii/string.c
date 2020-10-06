#include <stdio.h>
#include <string.h>

void *memset(void *dst, int val, size_t count)
{
   void *start = dst;

   while (count--)
   {
      *(char*)dst = (char)val;
      dst = (char*)dst + 1;
   }
   return start;
}

void *memcpy(void *dst, const void *src, size_t len)
{
   size_t i;

   for (i = 0; i < len; i++)
      ((unsigned char *)dst)[i] = ((unsigned char *)src)[i];

   return dst;
}
