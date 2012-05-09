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

enum fbdimensions {
     FRAMEBUFFER_WIDTH = 80,
     FRAMEBUFFER_HEIGHT = 25
};

enum hwports {
     VGA_COMMAND_PORT = 0x3D4,
     VGA_DATA_PORT = 0x3D5
};

enum vgacommands {
     EXPECT_HIGH_BYTE = 14,
     EXPECT_LOW_BYTE = 15
};

enum fbcolors {
     BLACK = 0,
     BLUE,
     GREEN,
     CYAN,
     RED,
     MAGENTA,
     BROWN,
     LIGHT_GREY,
     DARK_GREY,
     LIGHT_BLUE,
     LIGHT_GREEN,
     LIGHT_CYAN,
     LIGHT_RED,
     LIGHT_MAGENTA,
     LIGHT_BROWN,
     WHITE
};

static void 
movecursor()
{
     short cursorloc = cursory * FRAMEBUFFER_WIDTH + cursorx;

     outb(VGA_COMMAND_PORT, EXPECT_LOW_BYTE);
     outb(VGA_DATA_PORT, cursorloc >> 8);
     outb(VGA_COMMAND_PORT, EXPECT_HIGH_BYTE);
     outb(VGA_DATA_PORT, cursorloc);
}

static uchar 
attrbyte(uchar fgcolor, uchar bgcolor)
{
     return (bgcolor << 4) | (fgcolor & 0x0F);
}
