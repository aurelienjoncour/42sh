/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** minishell header
*/

#ifndef H_MINISHELL
#define H_MINISHELL

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

#include "minishell_t.h"
#include "fd_t.h"
#include "cmd_t.h"

//  MAIN FUNCTIONS
int minishell_create(minishell_t *shell, char **env);
void minishell_exit(minishell_t *shell, int status);
int minishell_run(minishell_t *shell);
int minishell_destroy(minishell_t *shell);
char *minishell_prompt(minishell_t *shell);

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

//  ENTRY
int minishell_exec(minishell_t *shell, char *entry);
char **split_entry(char *entry);

// ENTRY : PIPE
int minishell_exec_piped(minishell_t *shell, char *sub_entry);
int pipe_process_cmd(minishell_t *shell, char *command);
int pipe_process_cmd_last(minishell_t *shell, char *command);

// ENTRY : CHECK SUB-ENTRY
bool check_sub_entry(const char *sub_entry);
bool check_position_redirection_in_pipe(const char *sub_entry);

// ENTRY : PROCESS
int cmd_process(minishell_t *shell, char *command);
void cmd_destroy(cmd_t *cmd);
void cmd_create(cmd_t *cmd, char *command);

// ENTRY : PARSE/CHECK-CMD
void command_parse(cmd_t *cmd);
char *command_format(const char *command);
char **command_to_word_array(const char *formatted);
bool set_delim_mode(const int type_char, const int prev_type_char, int *delim);
int get_type_char(const char c, const int delim);
bool have_missing_str_quote(cmd_t *cmd);
bool have_missing_name_redirection(cmd_t *cmd);
bool have_several_redirection(cmd_t *cmd);
bool have_null_command(cmd_t *cmd);
bool is_invalid_redirection(const char *str);
int cmd_split_word_array(cmd_t *cmd);

// ENTRY : REDIRECT
void redirection_open_file(cmd_t *cmd);
void show_error(const char *param);
int do_redirection(cmd_t *cmd);
int redirect_stdin_to_command(const char *end_pattern, cmd_t *cmd);

//  CMD
int minishell_exec_cmd(minishell_t *shell, char **cmd);
int minishell_exec_shell_cmd(char **cmd, minishell_t *shell);
int minishell_exec_bin_cmd(char **cmd, minishell_t *shell);
int check_access_right_file(const char *bin_path);
int get_bin_path(char ***ptr_cmd, minishell_t *shell);
int get_bin_path_search_bin(char ***cmd, minishell_t *shell);

int my_exit(char **cmd, minishell_t *shell);
int my_clear(char **cmd, minishell_t *shell);
int my_cd(char **cmd, minishell_t *shell);
int my_env(char **cmd, minishell_t *shell);
int my_unsetenv(char **cmd, minishell_t *shell);
int my_setenv(char **cmd, minishell_t *shell);
int my_pwd(char **cmd, minishell_t *shell);
int show_exit_status(char **cmd, minishell_t *shell);

#endif
