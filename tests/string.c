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

ATF_TC(test_memset_zero);
ATF_TC_HEAD(test_memset_zero, tc)
{
     atf_tc_set_md_var(tc, "descr", "Ensure memset() handles size 0.");
}
ATF_TC_BODY(test_memset_zero, tc)
{
     uchar *x = malloc(20);
     memset(x, 0, 20);
     memset(x, 1, 0);

     int i;
     for (i = 0; i < 20; i++)
          ATF_REQUIRE(x[i] == 0);
}


ATF_TC(test_memmove_no_overlap);
ATF_TC_HEAD(test_memmove_no_overlap, tc)
{
     atf_tc_set_md_var(tc, "descr", "Test memmove() with non-overlapping regions.");
}
ATF_TC_BODY(test_memmove_no_overlap, tc)
{
     uchar *x = malloc(20);
     uchar *y = malloc(20);

     memset(x, 0, 20);
     memset(y, 1, 20);

     memmove(y, x, 20);

     int i;
     for (i = 0; i < 20; i++)
          ATF_REQUIRE(y[i] == 0);
}

ATF_TC(test_memmove_overlap);
ATF_TC_HEAD(test_memmove_overlap, tc)
{
     atf_tc_set_md_var(tc, "descr", "Test memmove() with overlapping regions.");
}
ATF_TC_BODY(test_memmove_overlap, tc) 
{
     uchar *x = malloc(100);

     int i;
     for (i = 0; i < 100; i++)
          x[i] = i;

     memmove(&x[20], &x[0], 30);

     for (i = 0; i < 30; i++)
          ATF_REQUIRE(x[i + 20] == i);
}

ATF_TP_ADD_TCS(tp)
{
     ATF_TP_ADD_TC(tp, test_memset);
     ATF_TP_ADD_TC(tp, test_memset_zero);
     ATF_TP_ADD_TC(tp, test_memmove_no_overlap);
     ATF_TP_ADD_TC(tp, test_memmove_overlap);
}
