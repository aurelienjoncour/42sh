/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** minishell header
*/

#ifndef H_SHELL
#define H_SHELL

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include <string.h>

#include "my.h"

#define EXIT_FAIL 8

#define ERROR_STATUS 1
#define SUCCESS_STATUS 0
#define SEGFAULT_STATUS 139
#define DIVZERO_STATUS 136

#include "shell_t.h"
#include "fd_t.h"
#include "cmd_t.h"

//  MASTER FUNCTIONS
int shell_create(shell_t *shell, char **env);
void shell_exit(shell_t *shell, int status);
int shell_run(shell_t *shell);
int shell_destroy(shell_t *shell);
char *shell_prompt(shell_t *shell);

//  TOOLS
void display_path_without_homepath(env_t *env, char *path);
char *merge_path_filename(const char *path, const char *filename);

int word_array_search(char **array, const int size, const char *str);
int word_array_search2(const char **array, const int size, const char *str);

bool char_is_letter(const char c);
bool str_is_alphanum(const char *str);
bool have_slash(const char *str);
bool str_have_only_chars(const char *str, const char *chars);
bool word_array_have_empty_str(char **warray);
int my_str_count_pattern(char *str, const char *pattern);
void my_str_count_char_suite(const char *str, const char c,
int *occur, int *serie);

//-------------------------------------------------
//  ENTRY
int shell_exec(shell_t *shell, char *entry);

// ENTRY : PIPE
// int shell_exec_piped(shell_t *shell, char *sub_entry);
// int pipe_process_cmd(shell_t *shell, char *command);
// int pipe_process_cmd_last(shell_t *shell, char *command);

// ENTRY : PROCESS
int cmd_process(shell_t *shell, cmd_t *cmd);

// ENTRY : CMD EXEC
int shell_exec_cmd(shell_t *shell, char **cmd);
int shell_exec_shell_cmd(char **cmd, shell_t *shell);
int shell_exec_bin_cmd(char **cmd, shell_t *shell);

int get_bin_path(const char *cmd_name, char **ptr_path, shell_t *shell);
int check_access_right_file(const char *bin_path);
char *get_bin_path_search_bin(const char *cmd_name, shell_t *shell);

// BUILTINS
int my_exit(char **cmd, shell_t *shell);
int my_clear(char **cmd, shell_t *shell);
int my_cd(char **cmd, shell_t *shell);
int my_env(char **cmd, shell_t *shell);
int my_unsetenv(char **cmd, shell_t *shell);
int my_setenv(char **cmd, shell_t *shell);
int my_pwd(char **cmd, shell_t *shell);
int show_exit_status(char **cmd, shell_t *shell);

int my_echo(char **cmd, shell_t *shell);
int my_set(char **cmd, shell_t *shell);

//-------------------------------------------------
//                 - MODULES -
// MOD : REDIRECT
// void redirection_open_file(cmd_t *cmd);
// void show_error(const char *param);
// int do_redirection(cmd_t *cmd);
// int redirect_stdin_to_command(const char *end_pattern, cmd_t *cmd);


#endif
