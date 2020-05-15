/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** node
*/

#ifndef PARSER_H_
#define PARSER_H_

#include "parser_t.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "cmd_t.h"

// Sub functions Node
void add_node(token_t *node, token_t *node_add);
token_t *rm_node(token_t *deleted);
void connect_node(token_t *node_1, token_t *node_2);
token_t *create_node(char *token, ID id, TYPE type);
int rm_next_nodes(token_t *node);
int add_node_at_the_end(token_t *node_1, token_t *node_2);
int list_push_node(token_t **list_dest, token_t *src);
token_t *get_last_token(token_t *token);
token_t **realloc_node_array(token_t **array_src, size_t size);
void free_node_array(token_t **array);

// Sub Functions
int create_token(token_t *last, char *argv, size_t cursor[2], ssize_t index);
char *my_strncat_realloc(char *s1, char *s2, size_t n);
ssize_t is_special_id(char *str, size_t cursor[2]);
void destroy_list(token_t *ptr);
void display_list(token_t *start);
token_t *tokeniser(char *entry);

////////////////////////////
// Main Functions
void cmd_destroy(cmd_t *cmd);
void cmd_array_destroy(cmd_t **cmd_array);
cmd_t *parse_entry(char *entry);

#define EXIT_ERROR 84

#endif /* !NODE_H_ */
