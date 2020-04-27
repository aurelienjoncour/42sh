/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** Created: 2020-03-25T14:34:11+01:00 | Author: simon
*/

#ifndef H_ENV
#define H_ENV

#include "env_t.h"

// Main functions

void my_env_destroy(env_t *env);
int my_env_create(env_t *env, char **copy_env);
int my_env_merge(env_t *env, char **env_src);

// Variable Management

int my_env_update(env_t *self, const char *label, const char *value);
int my_env_rm(env_t *self, const char *label);
int my_env_add(env_t *self, const char *label, const char *value);

// [Get variables]
//   For str variables
char *my_env_get_value(env_t *env, const char *label);
//   For Int varaibles
int my_env_get_value_int(env_t *env, const char *label, bool *error);
//   For double variables
double my_env_get_value_dec(env_t *env, const char *label, bool *error);

// Utility
bool my_env_exist(env_t *env, const char *label);
int my_env_size(env_t *env);
void my_env_display(env_t *env);

// Advanced functions
char **my_env_get_ptr(env_t *self, const char *label);
char *my_env_get(env_t *self, const char *label);
char *my_env_get_var_value(char *entry);
char *my_env_get_var_label(char *entry);

// Sub function (do not use)
char **my_env_alloc(char **src, env_t *old, int new_size, int src_size);
int my_env_check_collision(const env_t *env, char **env_array);

#endif
