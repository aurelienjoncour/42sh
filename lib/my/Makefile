##
## EPITECH PROJECT, 2019
## LIBMY_2019
## File description:
## LIBMY Makefile
##

DNBR = nbr/
DSTR = str/
DFILE = file/
DENV = env/
DLIST = list/

SRC_LIST = $(DLIST)my_list_str.c			\

SRC_NBR	=	$(DNBR)my_compute_power_rec.c	\
			$(DNBR)my_compute_square_root.c	\
			$(DNBR)convert_base.c			\
			$(DNBR)my_factorial_it.c		\
			$(DNBR)my_power_rec.c			\
			$(DNBR)my_sqrt.c				\
			$(DNBR)my_find_prime_sup.c		\
			$(DNBR)my_getnbr.c				\
			$(DNBR)my_getnbr_base.c			\
			$(DNBR)my_isneg.c				\
			$(DNBR)my_is_prime.c			\
			$(DNBR)my_putnbr_base.c			\
			$(DNBR)my_put_double.c      	\
			$(DNBR)my_get_double.c      	\
			$(DNBR)my_putnbr_base_str.c		\
			$(DNBR)my_put_nbr.c				\
			$(DNBR)quick_sort.c				\
			$(DNBR)my_sort_int_array.c		\
			$(DNBR)my_swap.c				\

SRC_FILE =	$(DFILE)my_read_file.c			\
			$(DFILE)get_next_line.c			\
			$(DFILE)my_read_dir.c			\
			$(DFILE)my_file_ext_cmp.c		\

SRC_ENV  =	$(DENV)my_env_create_destroy.c	\
			$(DENV)my_env_merge.c			\
			$(DENV)my_env_alloc.c			\
			$(DENV)my_env_get_label.c		\
			$(DENV)my_env_get_value.c		\
			$(DENV)my_env_add.c				\
			$(DENV)my_env_display.c			\
			$(DENV)my_env_get.c				\
			$(DENV)my_env_rm.c				\
			$(DENV)my_env_update.c			\
			$(DENV)my_env_size.c			\
			$(DENV)my_env_exist.c			\
			$(DENV)my_env_check_collision.c	\

SRC_STR  =	$(DSTR)my_putchar.c				\
			$(DSTR)my_putstr_error.c		\
			$(DSTR)my_putstr.c				\
			$(DSTR)my_revstr.c				\
			$(DSTR)my_showmem.c					\
			$(DSTR)my_showstr.c					\
			$(DSTR)my_advanced_sort_word_array.c\
			$(DSTR)my_show_word_array.c 		\
			$(DSTR)my_sort_word_array.c 		\
			$(DSTR)my_str_to_word_array.c 		\
			$(DSTR)word_array.c 				\
			$(DSTR)my_strcapitalize.c			\
			$(DSTR)my_strcat.c					\
			$(DSTR)my_strcmp.c					\
			$(DSTR)my_strcpy.c					\
			$(DSTR)my_strdup.c					\
			$(DSTR)my_str_isalpha.c				\
			$(DSTR)my_str_islower.c				\
			$(DSTR)my_str_isnum.c				\
			$(DSTR)my_str_isprintable.c			\
			$(DSTR)my_str_isupper.c				\
			$(DSTR)my_strlen.c					\
			$(DSTR)my_strlowcase.c				\
			$(DSTR)my_strncat.c					\
			$(DSTR)my_strncmp.c					\
			$(DSTR)my_strncpy.c					\
			$(DSTR)my_strstr.c					\
			$(DSTR)my_strupcase.c				\
			$(DSTR)my_printf.c             		\
			$(DSTR)my_printf_display.c     		\
			$(DSTR)my_printf_disp01.c      		\
			$(DSTR)my_printf_disp02.c      		\
			$(DSTR)my_printf_disp03.c			\
			$(DSTR)my_printf_disp_misc.c   		\
			$(DSTR)my_printf_misc.c        		\
			$(DSTR)my_printf_search.c			\
			$(DSTR)my_str_concat.c				\
			$(DSTR)my_str_replace_char.c		\
			$(DSTR)my_str_have_char.c			\

SRC	= $(SRC_STR) $(SRC_NBR) $(SRC_FILE) $(SRC_ENV) $(SRC_LIST)

DINCLUDE = ./include

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -W -Werror -I$(DINCLUDE) -g

NAME	=	libmy.a

all:	$(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ) && \
		$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREEN) "$(NAME)\n"$(DEFAULT) || \
		$(ECHO) $(BOLD_T)$(RED_C)"[✘] "$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(NAME)\n"$(DEFAULT)

clean:
	@$(RM) $(OBJ)

fclean:	clean
	@$(RM) $(NAME)

re:	fclean all

%.o: %.c
	@$(CC) -c $(CFLAGS) -o $@ $< && \
		$(ECHO) $(GREEN_C) "cc $(CFLAGS) -c "$<$(COLOR_THEME)" -o "$@ $(DEFAULT) || \
		$(ECHO) "\n"$(MAGEN_C) $(UNDLN_T)$(BOLD_T)"cc $(CFLAGS) -c "$<" -o "$@$(DEFAULT)"\n"

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
COLOR_THEME	=	$(CYAN_C)
DEBUG_THEME	=	$(CYAN_C)
TESTS_THEME	=	$(RED_C)
