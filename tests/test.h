#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <string.h>

extern int g_tests_run;
extern int g_tests_failed;

#define ASSERT_TRUE(cond)                                                      \
    do                                                                         \
    {                                                                          \
        g_tests_run++;                                                         \
        if (!(cond))                                                           \
        {                                                                      \
            g_tests_failed++;                                                  \
            fprintf(stderr, "  FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond);  \
        }                                                                      \
    } while (0)

#define ASSERT_FALSE(cond) ASSERT_TRUE(!(cond))

#define ASSERT_STREQ(actual, expected)                                         \
    do                                                                         \
    {                                                                          \
        g_tests_run++;                                                         \
        if ((actual) == NULL || (expected) == NULL                             \
            || strcmp((actual), (expected)) != 0)                              \
        {                                                                      \
            g_tests_failed++;                                                  \
            fprintf(stderr,                                                    \
                    "  FAIL %s:%d: expected \"%s\", got \"%s\"\n",             \
                    __FILE__,                                                  \
                    __LINE__,                                                  \
                    (expected) ? (expected) : "(null)",                        \
                    (actual) ? (actual) : "(null)");                           \
        }                                                                      \
    } while (0)

#endif /* TEST_H */
