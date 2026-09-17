#ifndef TEXT_STR_H
#define TEXT_STR_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Trims leading and trailing ASCII whitespace in place.
 *
 * Returns `text`. Passing NULL is a no-op and returns NULL.
 * An all-whitespace string becomes the empty string.
 */
char *str_trim(char *text);

/** True when `text` is NULL or contains only ASCII whitespace. */
bool str_is_blank(const char *text);

/** True when `text` begins with `prefix`. NULL arguments yield false. */
bool str_starts_with(const char *text, const char *prefix);

#ifdef __cplusplus
}
#endif

#endif /* TEXT_STR_H */
