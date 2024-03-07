/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** regex
*/

#ifndef REGEX_H_
    #define REGEX_H_

    #include <regex.h>

typedef struct regex_result_s {
    char *str;
    regmatch_t *match;
    regex_t *regex;
} regex_result_t;

regex_result_t *execute_regex(char *pattern, char *str);
void free_regex_result(regex_result_t *result);

#endif /* !REGEX_H_ */
