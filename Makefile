##
## EPITECH PROJECT, 2020
## CPE_getnextline_2019
## File description:
## Makefile
##

NAME		=	gnl

SRC			=	falsemain.c\
				get_next_line.c\

TESTS		=	get_next_line.c\
				tests/gnl_tests.c\

OBJ			=	$(SRC:%.c=%.o)

OBJTESTS	=	$(TESTS:%.c=%.o)

CC			=	gcc

CFLAGS		=	-W -Wextra -Wshadow -Wall -I . 

LDFLAGS		=	-lcriterion -lgcov

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

debug:		CFLAGS += -g
debug:		clean $(NAME)

clean:
		$(RM) -R $(OBJ)
		$(RM) -R $(OBJTESTS)
		$(RM) $(NAME)

fclean:		clean
		$(RM) -R $(OBJ:%.o=%.gcno)
		$(RM) -R $(OBJ:%.o=%.gcda)
		$(RM) -R $(OBJTESTS:%.o=%.gcno)
		$(RM) -R $(OBJTESTS:%.o=%.gcda)
		$(RM) unit_tests

re:			fclean all

tests_run:	CFLAGS += --coverage
tests_run:	fclean $(OBJTESTS)
		$(CC) -o unit_tests $(OBJTESTS) $(LDFLAGS)
		./unit_tests

.PHONY: all debug clean fclean re tests_run