#include "types.h"
#include "x86.h"

void*
memset(void *dst, int c, uint n)
{
     char *d;
     d = dst;

     while (n-- > 0)
          *++d = c;

     return dst;
}

static bool
overlap(char *dst, char *src, uint n)
{
     if (src < dst && src + n > dst)
          return true;
     else 
          return false;
}

void*
memmove(void *dst, const void *src, uint n)
{
     char *d, *s;

     d = dst;
     s = src;

     if (overlap(d, s, n)) {
          s += n;
          d += n;
          while (n-- > 0)
               *--d = *--s;
     } else {
          while (n-- > 0)
               *d++ = *s++;
     }

     return dst;
}
