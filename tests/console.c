#include <atf-c.h>

#include <stdlib.h>

#include "../console.c"

ATF_TC(test_getcolor);
ATF_TC_HEAD(test_getcolor, tc)
{
     atf_tc_set_md_var(tc, "descr", "Ensure getcolor() is returning the correct values.");
}
ATF_TC_BODY(test_getcolor, tc)
{
     uchar bg, fg;
     for (bg = BLACK; bg <= WHITE; bg++) {
          for (fg = BLACK; fg <= WHITE; fg++) {
               uchar color = getcolor(fg, bg);
               ATF_REQUIRE((color >> 4) == bg);
               ATF_REQUIRE((color & 0x0F) == fg);
          }
     }
}

ATF_TC(test_getfbsymbol_color);
ATF_TC_HEAD(test_getfbsymbol_color, tc)
{
     atf_tc_set_md_var(tc, "descr", "Ensure getfbsymbol() is setting the given color.");
}
ATF_TC_BODY(test_getfbsymbol_color, tc)
{
     ushort fbsymbol;
     uchar color;
     
     color = getcolor(BLACK, WHITE);
     fbsymbol = getfbsymbol('c', color);

     ATF_REQUIRE((fbsymbol >> 8) == color);
}

ATF_TC(test_getfbsymbol_char);
ATF_TC_HEAD(test_getfbsymbol_char, tc)
{
     atf_tc_set_md_var(tc, "descr", "Ensure getfbsymbol() is setting the given character.");
}
ATF_TC_BODY(test_getfbsymbol_char, tc)
{
     ushort fbsymbol;
     uchar color;

     color = getcolor(BLACK, WHITE);
     fbsymbol = getfbsymbol('c', color);

     ATF_REQUIRE((fbsymbol & 0xFF) == 'c');
}

ATF_TC(test_writec);
ATF_TC_HEAD(test_writec, tc)
{
     atf_tc_set_md_var(tc, "descr", "Ensure writec() is writing to the framebuffer correctly.");
}
ATF_TC_BODY(test_writec, tc)
{
     ushort fbsymbol;
     uchar color;
     int loc;

     loc = 50;
     color = getcolor(BLACK, WHITE);
     fbsymbol = getfbsymbol('j', color);

     fb = malloc(sizeof(fb[0]) * FB_WIDTH * FB_HEIGHT);
     
     writec('j', &loc, color);
     ATF_REQUIRE(fb[50] == fbsymbol);
     ATF_REQUIRE(loc == 51);
}

ATF_TP_ADD_TCS(tp)
{
     ATF_TP_ADD_TC(tp, test_getcolor);
     ATF_TP_ADD_TC(tp, test_getfbsymbol_color);
     ATF_TP_ADD_TC(tp, test_getfbsymbol_char);
     ATF_TP_ADD_TC(tp, test_writec);
}
