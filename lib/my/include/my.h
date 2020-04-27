/*
** EPITECH PROJECT, 2019
** LIBMY
** File description:
** Headers of libmy
*/

#ifndef MY_H_
#define MY_H_

#include <math.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "get_next_line.h"
#include "my_env.h"

#include "list_str_t.h"
#include "file_list_t.h"

#define POW(x, y) my_compute_power_rec(x, y)
#define SQRT(x) my_compute_square_root(x)

#define EXIT_ERROR 84

#define DEFAULT_T "\e[0m"
#define BOLD_T "\e[1m"
#define DIM_T "\e[2m"
#define UNDLN_T	"\e[4m"
#define BLACK_C	"\e[30m"
#define RED_C "\e[31m"
#define GREEN_C "\e[32m"
#define YELLO_C "\e[33m"
#define BLUE_C "\e[34m"
#define MAGEN_C "\e[35m"
#define CYAN_C "\e[36m"
#define WHITE_C "\e[97m"
#define DEFAULT_C "\e[39m"

// LINKED LIST
void my_str_list_destroy(list_str_t *list);
char *my_str_list_read(list_str_t *list);
int my_str_list_add(list_str_t **list, const char *str);

// FILE
char **my_read_file(const char *filepath);
int my_read_dir(file_list_t **files, const char *dirpath);
int my_file_list_add(file_list_t **list, const char *filename);
void my_file_list_destroy(file_list_t *list);
char *my_file_list_read(file_list_t *list);
bool my_file_ext_cmp(const char *filepath, const char *extension);

// STRING

int my_printf(char *format, ...);
int my_putchar(char c);
int my_putstr(char const *str);
int my_putstr_error(const char *str);
int my_puterror(const char *str, int status);
int puterr(const char *str, int status);
int my_strlen(char const *str);
char *my_strdup(char const *src);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_revstr(char *str);
char *my_strstr(char *str, char const *to_find);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_str_concat(const char *stra, const char *strb);
char *my_strupcase(char *str);
char *my_strlowcase(char *str);
char *my_strcapitalize(char *str);
bool my_str_isalpha(char const *str);
bool my_str_isnum(char const *str);
bool my_str_islower(char const *str);
bool my_str_isupper(char const *str);
bool my_str_isprintable(char const *str);
int my_showstr(char const *str);
char *my_strcat(char *dest, const char *src);
char *my_strncat(char *dest, char const *src, int nb);
char *my_strdup(char const *str);
char **my_str_to_word_array(char const *str, const char *delim);
int my_show_word_array(char * const *tab);
int my_sort_word_array(char **tab);
void word_array_destroy(char **array);
int word_array_len(char **array);
bool have_str_in_array(char **array, const int size, const char *str);
int my_advanced_sort_word_array(char **tab,
int (*cmp)(char const *, char const *));
bool my_str_replace_char(char *str, const char *from, const char *to);
int my_str_have_char(const char *str, char c);

// NUMBER
char *my_putnbr_base_str(int nbr, char const *base);
int my_sqrt(int nb);
int my_power_rec(int nb, const int p);
int my_factorial_it(const int nb);
bool my_isneg(const int nb);
int my_put_nbr(long long int nb);
int my_put_nbr_ul(unsigned long long int nb);
int my_putnbr_base(long int nbr, char const *base);
char *my_putnbr_base_s(int nbr, char const *base);
void my_put_double(const double nb, int nb_decimal);
double my_get_double(const char *nbr);
int my_getnbr(char const *str);
void my_swap(int *a, int *b);
void my_sort_int_array(int *tab, int size);
int my_compute_power_rec(int nb, int power);
bool my_is_prime(const size_t nb);
int my_compute_square_root(const int nb);
int my_find_prime_sup(const int nb);
char *convert_base(char const *nbr, char const *base_from, char const *base_to);
int my_getnbr_base(char const *str, char const *base);
void quick_sort(int *array, int idx_begin, int idx_end);

// MISC
int my_showmem(char const *str, int size);

#endif
