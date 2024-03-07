/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** regex
*/

#include <unistd.h>
#include <stdbool.h>

#include "regex_util.h"

static size_t calculate_nmatch(const char *pattern)
{
    size_t nmatch = 1;
    bool escape = false;
    const char *s;

    for (s = pattern; *s != '\0'; ++s) {
        if (escape) {
            escape = false;
            continue;
        }
        if (*s == '\\') {
            escape = true;
            continue;
        }
        if (*s == '(')
            ++nmatch;
    }

    return nmatch;
}

regex_result_t *execute_regex(char *pattern, char *str)
{
    regex_result_t *result = NULL;
    regex_t *regex = malloc(sizeof(regex_t));
    size_t nmatch = calculate_nmatch(pattern);
    regmatch_t *match = malloc(sizeof(regmatch_t) * nmatch);

    if (regcomp(regex, pattern, REG_EXTENDED))
        return NULL;
    if (regexec(regex, str, nmatch, match, 0))
        return NULL;
    result = malloc(sizeof(regex_result_t));
    if (result == NULL)
        return NULL;
    result->regex = regex;
    result->match = match;
    result->str = str;
    return result;
}

void free_regex_result(regex_result_t *result)
{
    regfree(result->regex);
    free(result->match);
    free(result);
}
