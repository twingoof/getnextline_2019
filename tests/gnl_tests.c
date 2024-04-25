/*
** EPITECH PROJECT, 2020
** CPE_getnextline_2019
** File description:
** gnl_tests
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <criterion/criterion.h>
#include "get_next_line.h"

char *get_from_file(int fd, char **carry, char *next_line);
char *get_from_carry(char **carry);
int my_strlen(char *str);
char *my_strcat(char *s1, char *s2, int free_s1, int free_s2);

int fd = -1;

void open_file(void)
{
    fd = open("tests/txts/a", O_RDONLY);
}

void close_file(void)
{
    if (fd != -1)
        close(fd);
}

Test(get_next_line, read_first_line, .init = open_file, .fini = close_file)
{
    char *expected = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempora";
    char *got = get_next_line(fd);

    cr_assert_str_eq(got, expected);
}

Test(get_next_line, entire_file, .init = open_file, .fini = close_file)
{
    char *got = get_next_line(fd);

    while ((got = get_next_line(fd)) != NULL);

    cr_assert_null(got);
}

Test(get_next_line, multiple_line, .init = open_file, .fini = close_file)
{
    cr_assert_str_eq(get_next_line(fd), "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempora");
    cr_assert_str_eq(get_next_line(fd), "incididunt ut labore et dolore magna aliqua. Sapien faucibus et molestie acazer");
    cr_assert_str_eq(get_next_line(fd), "feugiat sed. Magnis dis parturient montes nascetur ridiculus mus mauris vitae.a");
}

Test(get_next_line, bad_fd)
{
    char *got = get_next_line(-84);

    cr_assert_null(got);
}

Test(get_next_line, get_text_in_carry, .init = open_file, .fini = close_file)
{
    cr_assert_str_eq(get_next_line(fd), "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempora");
    cr_assert_str_eq(get_next_line(fd), "incididunt ut labore et dolore magna aliqua. Sapien faucibus et molestie acazer");
}

Test(get_next_line, line_without_eol, .fini = close_file)
{
    fd = open("tests/txts/c", O_RDONLY);

    cr_assert_str_eq(get_next_line(fd), "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempora");
}

Test(get_next_line, only_eof, .fini = close_file)
{
    fd = open("tests/txts/eof", O_RDONLY);

    cr_assert_null(get_next_line(fd));
}

Test(get_next_line, only_eol, .fini = close_file)
{
    fd = open("tests/txts/eol", O_RDONLY);

    cr_assert_str_empty(get_next_line(fd));
}

Test(get_from_carry, no_carry)
{
    char *carry[2] = {NULL, NULL};
    char *got = get_from_carry(carry);

    cr_assert_null(got);
}

Test(get_from_carry, no_eol)
{
    char *carry = "banane";
    char *got = get_from_carry(&carry);

    cr_assert_str_eq(got, "banane");
    cr_assert_null(carry);
}

Test(get_from_carry, one_eol)
{
    char *carry = "banan\ne";
    char *got = get_from_carry(&carry);

    cr_assert_str_eq(got, "banan");
    cr_assert_str_eq(carry, "e");
}

Test(get_from_file, buff_without_eol)
{
    int fd2 = open("tests/txts/c", O_RDONLY);
    char *carry = NULL;
    char *got = get_from_file(fd2, &carry, NULL);

    cr_assert_str_eq(got, "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempora");
    close(fd2);
}

Test(get_from_file, bad_fd)
{
    char *carry = NULL;
    char *got = get_from_file(12344, &carry, NULL);

    cr_assert_null(got);
}

Test(my_strlen, null_value)
{
    cr_assert_eq(my_strlen(NULL), 0);
}

Test(my_strcat, free_s1)
{
    char *s1 = "zom";
    char *s2 = "bie";
    char *got = my_strcat(s1, s2, false, false);

    cr_assert_str_eq(got, "zombie");
}
