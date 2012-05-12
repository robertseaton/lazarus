/* The framebuffer is mapped into memory by GRUB at 0xB8000. 
   It's just an array of 16 bit words. Each represents the
   display of one character.

   The eight low bits are the ASCII character code. The eight
   high bits are divided into 4 bits for the background color
   and 4 bits for the foreground color. 

   The hardware cursor is controlled via commands sent to the
   VGA controller. */

#include "types.h"
#include "x86.h"
#include "defs.h"

enum fbdimensions {
     FB_WIDTH = 80,
     FB_HEIGHT = 25
};

enum hwports {
     VGA_COMMAND_PORT = 0x3D4,
     VGA_DATA_PORT = 0x3D5
};

enum vgacommands {
     HIGH_BYTE = 14,
     LOW_BYTE = 15
};

enum fbcolors {
     BLACK = 0,
     BLUE,
     GREEN,
     CYAN,
     RED,
     MAGENTA,
     BROWN,
     LIGHTGREY,
     DARKGREY,
     LIGHTBLUE,
     LIGHTGREEN,
     LIGHTCYAN,
     LIGHTRED,
     LIGHTMAGENTA,
     LIGHTBROWN,
     WHITE
};

enum charactercodes {
     BACKSPACE = 0x100
};

static ushort *fb = (ushort *)0xB8000;

static void 
movecursor(int position)
{
     outb(VGA_COMMAND_PORT, HIGH_BYTE);
     outb(VGA_DATA_PORT, position >> 8);
     outb(VGA_COMMAND_PORT, LOW_BYTE);
     outb(VGA_DATA_PORT, position);
}

static uint
getcursor()
{
     int position;

     outb(VGA_COMMAND_PORT, HIGH_BYTE);
     position = inb(VGA_DATA_PORT) << 8;
     outb(VGA_COMMAND_PORT, LOW_BYTE);
     position |= inb(VGA_DATA_PORT);

     return position;
}

static uchar 
getcolor(uchar fgcolor, uchar bgcolor)
{
     return (bgcolor << 4) | (fgcolor & 0x0F);
}

static ushort
getfbsymbol(int c, uchar color)
{
     ushort symbol;

     symbol = color << 8;
     symbol |= c;

     return symbol;
}

static int
nextline(int position)
{
     return position + FB_WIDTH - position % FB_WIDTH;
}

static bool
needscroll(int position)
{
     if ((position / FB_WIDTH) >= FB_HEIGHT)
          return true;
     else
          return false;
}

static void 
scroll(int *position)
{
     memmove(fb, fb + FB_WIDTH, sizeof(fb[0]) * (FB_HEIGHT - 1) * FB_WIDTH);
     *position -= FB_WIDTH;
     memset(fb + *position, 0, sizeof(fb[0]) * (FB_HEIGHT * FB_WIDTH - *position));
}

static void
writec(int c, int *position, uchar color)
{
     if (c == BACKSPACE && position > 0)
          (*position)--;
     else if (c == '\n')
          *position = nextline(*position);
     else
          fb[(*position)++] = getfbsymbol(c, color);

     if (needscroll(*position))
          scroll(position);
}

static void
vgaputc(int c)
{
     int position;
     uchar color;
     
     position = getcursor();
     color = getcolor(WHITE, BLACK);
     writec(c, &position, color);
     movecursor(position);
}

void
kprintf(char *string)
{
     int i = 0;
     while (string[i] != '\0')
          vgaputc(string[i++]);
}
