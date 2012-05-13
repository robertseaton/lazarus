#include <atf-c.h>

#include <stdlib.h>

#include "../string.c"

ATF_TC(test_memset);
ATF_TC_HEAD(test_memset, tc)
{
     atf_tc_set_md_var(tc, "descr", "Ensure memset() functions correctly.");
}
ATF_TC_BODY(test_memset, tc)
{
     uchar *x = malloc(20);
     memset(x, 0, 20);

     int i;
     for (i = 0; i < 20; i++)
          ATF_REQUIRE(x[i] == 0);
}

ATF_TP_ADD_TCS(tp)
{
     ATF_TP_ADD_TC(tp, test_memset);
}
