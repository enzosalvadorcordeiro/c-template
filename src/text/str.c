#include "text/str.h"

#include <ctype.h>
#include <string.h>

char *str_trim(char *text)
{
    char *start;
    char *end;

    if (text == NULL)
    {
        return NULL;
    }

    start = text;
    while (*start != '\0' && isspace((unsigned char)*start))
    {
        start++;
    }

    if (*start == '\0')
    {
        text[0] = '\0';
        return text;
    }

    end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end))
    {
        end--;
    }
    end[1] = '\0';

    if (start != text)
    {
        memmove(text, start, (size_t)(end - start + 2));
    }

    return text;
}

bool str_is_blank(const char *text)
{
    if (text == NULL)
    {
        return true;
    }

    while (*text != '\0')
    {
        if (!isspace((unsigned char)*text))
        {
            return false;
        }
        text++;
    }

    return true;
}

bool str_starts_with(const char *text, const char *prefix)
{
    size_t prefix_len;

    if (text == NULL || prefix == NULL)
    {
        return false;
    }

    prefix_len = strlen(prefix);
    return strncmp(text, prefix, prefix_len) == 0;
}
