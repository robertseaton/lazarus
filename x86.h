static void
outb(ushort port, uchar data)
{
     asm volatile("out %0,%1" : : "a" (data), "d" (port));
}

static uchar
inb(ushort port)
{
     uchar data;

     asm volatile("in %1,%0" : "=a" (data) : "d" (port));

     return data;
}

