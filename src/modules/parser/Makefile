##
## EPITECH PROJECT, 2020
## parser
## File description:
## Makefile
##

INC_DIR		=	include/

SRC			=	main.c						\
				node/add_node.c				\
				node/connect_node.c			\
				node/create_node.c			\
				node/rm_node.c				\
				node/rm_next_node.c			\
				node/add_node_at_the_end.c	\
				destroy_list.c				\
				display_list.c				\
				parser_array.c				\
				create_token.c				\
				tokeniser.c					\
				tool.c						\
				main_parser.c				\

OBJ			=	$(SRC:.c=.o)

NAME		=	parser

CFLAGS		+=	-Wall -Wextra -W -I./include -g

all:		$(NAME)

$(NAME):	$(OBJ)
		gcc -o $(NAME) $(OBJ) -g

clean:
			@rm -f $(OBJ)

fclean:		clean
			@rm -f $(NAME)

re:	fclean all

run:	all
	./$(NAME)

tests_run:		fclean all
				make -C tests/

debugs:	CFLAGS += -g
debugs: re

.PHONY: all clean fclean re run tests_run debugs
