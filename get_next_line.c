/*
** EPITECH PROJECT, 2020
** CPE_getnextline_2019
** File description:
** get_next_line
*/

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

int my_strlen(char *str)
{
    int len = 0;

    if (!str)
        return (len);
    for (len = 0; str[len] != '\0'; len ++);
    return (len);
}

char *my_strncpy(char *source, int n)
{
    int i = 0;
    int source_len = my_strlen(source);
    int size = 0;
    char *dest = NULL;

    if (source_len <= n)
        size = source_len;
    else
        size = n;
    dest = malloc(sizeof(char) * (size + 1));
    dest[size] = '\0';
    for (i = 0; source[i] != '\0' && i != n; i++)
        dest[i] = source[i];
    return (dest);
}

char *my_strcat(char *s1, char *s2, int free_s1, int free_s2)
{
    int index = 0;
    int s1_len = my_strlen(s1);
    int s2_len = my_strlen(s2);
    int total_len = s1_len + s2_len;
    char *nw_str = malloc(sizeof(char) * (total_len + 1));

    nw_str[total_len] = '\0';
    for (index = 0; index != s1_len; index++)
        nw_str[index] = s1[index];
    for (int i = 0; i != s2_len; i++)
        nw_str[index + i] = s2[i];
    if (free_s1 == true)
        free(s1);
    if (free_s2 == true)
        free(s2);
    return (nw_str);
}

int has_eol(char *buffer, int readed)
{
    int i = 0;

    for (i = 0; i != readed; i++) {
        if (buffer[i] == '\n')
            return (i);
    } return (-1);
}

char *get_from_file(int fd, char **carry, char *next_line)
{
    int readed = -1;
    int eol_pos = -1;
    char *buffer = malloc(sizeof(char) * (READ_SIZE + 1));

    if (!buffer)
        return (NULL);
    while ((readed = read(fd, buffer, READ_SIZE)) != -1) {
        buffer[readed] = '\0';
        if (readed == 0) {
            return ((buffer[0] == '\0') ? next_line : NULL);
        } if ((eol_pos = has_eol(buffer, readed)) != -1)
            break;
        next_line = (!next_line) ? my_strncpy(buffer, my_strlen(buffer)) \
: my_strcat(next_line, buffer, true, false);
    } if (readed < 0)
        return (NULL);
    next_line = my_strcat(next_line, my_strncpy(buffer, eol_pos), true, true);
    carry[0] = my_strncpy(&buffer[eol_pos + 1], my_strlen(&buffer[eol_pos+1]));
    free(buffer);
    return (next_line);
}

char *get_from_carry(char **carry)
{
    char *line = NULL;
    int eol = -1;

    if (!carry[0])
        return (NULL);
    eol = has_eol(carry[0], my_strlen(carry[0]));
    if (eol < 0) {
        line = my_strncpy(carry[0], my_strlen(carry[0]));
        carry[0] = NULL;
        return (line);
    } line = my_strncpy(carry[0], eol);
    carry[0] = &carry[0][eol + 1];
    return (line);
}

char *get_next_line(int fd)
{
    static char *carry = NULL;
    char *nxt_line = NULL;

    if (fd < 0)
        return (NULL);
    if (carry)
        nxt_line = get_from_carry(&carry);
    if (carry)
        return (nxt_line);
    nxt_line = get_from_file(fd, &carry, nxt_line);
    if (nxt_line && (nxt_line[0] == '\n' || nxt_line[0] == '\0'))
        return (my_strncpy("\0", 1));
    return (nxt_line);
}
