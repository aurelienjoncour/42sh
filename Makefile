##
## EPITECH PROJECT, 2020
## Project_2020
## File description:
## Project makefile
##

DSRC	=	./src/
DCMD 	=	cmd
DMASTER =	master
DTOOL 	=	tool

MASTER = 	$(DSRC)$(DMASTER)/shell_create_destroy.c		\
			$(DSRC)$(DMASTER)/shell_exit.c					\
			$(DSRC)$(DMASTER)/shell_run.c					\
			$(DSRC)$(DMASTER)/prompt.c						\

MODULES = 	$(DSRC)modules/redirection/do_redirection.c				\
			$(DSRC)modules/redirection/redirect_open_file.c			\
			$(DSRC)modules/redirection/redirect_stdin_to_command.c	\
			$(DSRC)modules/parser/parser.c					\

CMD		=	$(DSRC)$(DCMD)/shell_exec_cmd.c					\
			$(DSRC)$(DCMD)/binary/exec_cmd_bin.c			\
			$(DSRC)$(DCMD)/binary/get_bin_path.c			\
			$(DSRC)$(DCMD)/binary/check_access_right_file.c	\
			$(DSRC)$(DCMD)/binary/get_bin_path_search_bin.c	\
			$(DSRC)$(DCMD)/builtin/exec_cmd_builtin.c		\
			$(DSRC)$(DCMD)/builtin/cmd/my_exit.c			\
			$(DSRC)$(DCMD)/builtin/cmd/my_clear.c			\
			$(DSRC)$(DCMD)/builtin/cmd/my_pwd.c				\
			$(DSRC)$(DCMD)/builtin/cmd/my_env.c				\
			$(DSRC)$(DCMD)/builtin/cmd/my_unsetenv.c		\
			$(DSRC)$(DCMD)/builtin/cmd/my_setenv.c			\
			$(DSRC)$(DCMD)/builtin/cmd/my_cd/my_cd.c		\
			$(DSRC)$(DCMD)/builtin/cmd/my_cd/test_path.c  	\
			$(DSRC)$(DCMD)/builtin/cmd/my_cd/get_path.c 	\
			$(DSRC)$(DCMD)/builtin/cmd/show_exit_status.c	\
			$(DSRC)$(DCMD)/builtin/cmd/my_echo.c			\
			$(DSRC)$(DCMD)/builtin/cmd/my_set.c				\
			$(DSRC)$(DCMD)/builtin/cmd/my_which.c			\

ENTRY 	=	$(DSRC)entry/shell_exec.c						\
			$(DSRC)entry/shell_exec_segment.c				\
			$(DSRC)entry/pipe/shell_exec_pipe.c				\
			$(DSRC)entry/pipe/pipe_process_cmd.c			\
			$(DSRC)entry/pipe/pipe_process_cmd_last.c		\
			$(DSRC)entry/bool_op/shell_exec_boolop.c		\
			$(DSRC)entry/cmd_process.c						\

TOOLS	=	$(DSRC)$(DTOOL)/display_path_without_homepath.c	\
			$(DSRC)$(DTOOL)/merge_path_filename.c			\
			$(DSRC)$(DTOOL)/word_array_search.c				\
			$(DSRC)$(DTOOL)/tool.c							\
			$(DSRC)$(DTOOL)/my_str_count_pattern.c			\
			$(DSRC)$(DTOOL)/my_str_count_char_suite.c		\

SRC	=	$(DSRC)main.c										\
		$(MASTER) $(ENTRY) $(CMD) $(MODULES) $(TOOLS)


SRC_UT =	tests_unit/test_minishell.c							\
			$(DSRC)entry/parse_command/command_format.c			\
			$(DSRC)entry/parse_command/command_parse_tool.c		\
			$(DSRC)entry/parse_command/command_to_word_array.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	42sh

CFLAGS	+= -Wall -Wextra -W $(INCLUDE) -g # -Werror

INCLUDE = -I./include -I./lib/my/include

all:  lib $(NAME)

$(NAME): $(OBJ)
	make -C ./lib/my
	@gcc -o $(NAME) $(OBJ) -L./lib/my -lmy && \
		$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREEN) "$(NAME)\n"$(DEFAULT) || \
		$(ECHO) $(BOLD_T)$(RED_C)"[✘] "$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(NAME)\n"$(DEFAULT)

lib:
	make -C ./lib/my

lib_re:
	make re -C ./lib/my

lib_fclean:
	make fclean -C lib/my

clean:
	rm -f  $(OBJ)
	rm -f *.gcda
	rm -f *.gcno

fclean:	clean
	rm -f $(NAME)

re:	fclean all

reall:	fclean all lib_re

tests_run:
	gcc -o $(NAME) $(SRC_UT) $(INCLUDE) -L./lib/my -lmy -lcriterion --coverage && ./$(NAME)

.PHONY :        clean fclean re

ECHO	=	/bin/echo -e
DEFAULT	=	"\e[0m"
BOLD_T	=	"\e[1m"
DIM_T	=	"\e[2m"
UNDLN_T	=	"\e[4m"
BLACK_C	=	"\e[30m"
RED_C	=	"\e[31m"
GREEN_C	=	"\e[32m"
YELLO_C	=	"\e[33m"
BLUE_C	=	"\e[34m"
MAGEN_C	=	"\e[35m"
CYAN_C	=	"\e[36m"
WHITE_C	=	"\e[97m"
DEFAULT_C	=	"\e[39m"
LINE_RETURN	=	$(ECHO) ""
