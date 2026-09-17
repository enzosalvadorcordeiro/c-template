#include "test.h"
#include "text/str.h"

#include <string.h>

void test_str_trim(void);
void test_str_is_blank(void);
void test_str_starts_with(void);

void test_str_trim(void)
{
    char padded[] = "  hello  ";
    char inner[] = "  hello world  ";
    char empty[] = "   ";
    char already[] = "ok";

    ASSERT_STREQ(str_trim(padded), "hello");
    ASSERT_STREQ(str_trim(inner), "hello world");
    ASSERT_STREQ(str_trim(empty), "");
    ASSERT_STREQ(str_trim(already), "ok");
    ASSERT_TRUE(str_trim(NULL) == NULL);
}

void test_str_is_blank(void)
{
    ASSERT_TRUE(str_is_blank(NULL));
    ASSERT_TRUE(str_is_blank(""));
    ASSERT_TRUE(str_is_blank(" \t\n"));
    ASSERT_FALSE(str_is_blank("a"));
    ASSERT_FALSE(str_is_blank(" a "));
}

void test_str_starts_with(void)
{
    ASSERT_TRUE(str_starts_with("filename.c", "file"));
    ASSERT_TRUE(str_starts_with("--help", "--"));
    ASSERT_TRUE(str_starts_with("abc", "abc"));
    ASSERT_TRUE(str_starts_with("abc", ""));
    ASSERT_FALSE(str_starts_with("abc", "abcd"));
    ASSERT_FALSE(str_starts_with(NULL, "a"));
    ASSERT_FALSE(str_starts_with("a", NULL));
}
