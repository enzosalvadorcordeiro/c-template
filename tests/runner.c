#include "test.h"

#include <stdio.h>

void test_str_trim(void);
void test_str_is_blank(void);
void test_str_starts_with(void);

int g_tests_run;
int g_tests_failed;

int main(void)
{
    test_str_trim();
    test_str_is_blank();
    test_str_starts_with();

    if (g_tests_failed == 0)
    {
        printf("ok  %d assertions\n", g_tests_run);
        return 0;
    }

    printf("FAILED  %d of %d assertions\n", g_tests_failed, g_tests_run);
    return 1;
}
