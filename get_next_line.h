/*
** EPITECH PROJECT, 2020
** CPE_getnextline_2019
** File description:
** get_next_line
*/

#ifndef GET_NEXT_LINE_H_
#define GET_NEXT_LINE_H_

#include <stdbool.h>

#ifndef READ_SIZE
#define READ_SIZE   26
#endif /* !READ_SIZE */

#ifndef EPI_ERROR
#define EPI_ERROR   -1
#endif  /* !EPI_ERROR */


char *get_next_line(int fd);

#endif /* !GET_NEXT_LINE_H_ */
