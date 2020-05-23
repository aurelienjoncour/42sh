/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** header
*/

#ifndef H_GLOBBING
#define H_GLOBBING

#include "shell.h"

int process_globbing(token_t *token, cmd_t *cmd);
bool process_regexp(const char *pattern, const char *filename);
int process_bracket(const char *pattern, const char *filename,
size_t *c_pat, size_t *c_fil);
interval_t *create_interval(char c1, char c2);
int add_interval(interval_t *data, char c1, char c2);
void destroy_interval(interval_t *data);
bool check_interval(interval_t *interval, const char *filename, size_t *c_fil);
void remove_invalid_node(file_list_t *del_node, file_list_t *prev_node,
file_list_t **first_node);

token_t *file_list_to_token_list(file_list_t *file_list, char *path);
token_t *list_to_token_list(file_list_t *flist);

void insert_new_token(token_t *old, token_t *new_first, token_t *new_last,
cmd_t *main_cmd);

#endif
