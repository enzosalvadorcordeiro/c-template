#include "app/status.h"
#include "app/version.h"
#include "text/str.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_help(const char *argv0)
{
    printf("%s %s\n", APP_NAME, APP_VERSION);
    printf("Usage: %s [--help] [--version] [FILE]\n\n", argv0);
    printf("  Reads FILE (default: data/sample.txt) and prints each\n");
    printf("  non-blank line after trimming ASCII whitespace.\n");
}

static app_status print_trimmed_file(const char *path)
{
    char buffer[1024];
    FILE *input = fopen(path, "r");

    if (input == NULL)
    {
        fprintf(stderr, "%s: cannot open '%s'\n", APP_NAME, path);
        return APP_ERR_NOINPUT;
    }

    while (fgets(buffer, (int)sizeof buffer, input) != NULL)
    {
        str_trim(buffer);
        if (!str_is_blank(buffer))
        {
            puts(buffer);
        }
    }

    if (ferror(input))
    {
        fprintf(stderr, "%s: error reading '%s'\n", APP_NAME, path);
        fclose(input);
        return APP_ERR_IO;
    }

    fclose(input);
    return APP_OK;
}

int main(int argc, char **argv)
{
    const char *path = "data/sample.txt";
    int i;

    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
        {
            print_help(argv[0]);
            return (int)APP_OK;
        }
        if (strcmp(argv[i], "--version") == 0)
        {
            printf("%s %s\n", APP_NAME, APP_VERSION);
            return (int)APP_OK;
        }
        if (str_starts_with(argv[i], "-"))
        {
            fprintf(stderr, "%s: unknown option '%s'\n", APP_NAME, argv[i]);
            print_help(argv[0]);
            return (int)APP_ERR_USAGE;
        }
        path = argv[i];
    }

    return (int)print_trimmed_file(path);
}
