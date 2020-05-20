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
#include <signal.h>

#include "my.h"

#define EXIT_FAIL 8

#define ERROR_STATUS 1
#define SUCCESS_STATUS 0
#define SEGFAULT_STATUS 139
#define DIVZERO_STATUS 136

#include "shell_t.h"
#include "fd_t.h"
#include "cmd_t.h"
#include "parser.h"
#include "script.h"
#include "redirection.h"
#include "substitute_var.h"

//  MASTER FUNCTIONS
int shell_create(shell_t *shell, char **env, char *shell_script);
void shell_exit(shell_t *shell, int status);
int shell_run(shell_t *shell);
int shell_destroy(shell_t *shell);
char *shell_prompt(shell_t *shell);
void handler(__attribute((unused))int signum);

//-------------------------------------------------
//                  - ENTRY -
int shell_exec(shell_t *shell, char *entry);

cmd_t **split_cmd_list(cmd_t *cmd, ID token_id, ID token2_id);

// ENTRY : segment
int shell_exec_segment(shell_t *shell, cmd_t *cmd);

// ENTRY : PIPE
int shell_exec_pipe(shell_t *shell, cmd_t *seg_cmd);
int pipe_process_cmd(shell_t *shell, cmd_t *pipe_cmd);
int pipe_process_cmd_last(shell_t *shell, cmd_t *pipe_cmd);

// ENTRY : BOOL OP
int shell_exec_boolop(shell_t *shell, cmd_t *pipe_cmd);

// ENTRY : SCRIPT
// see script.h

// ENTRY : PROCESS
int cmd_process(shell_t *shell, cmd_t *cmd);
char **linked_list_to_warray(cmd_t *cmd);

// ENTRY : Parenthesis Exec
int parenthesis_exec(shell_t *shell, cmd_t *cmd);

// ENTRY : CMD EXEC
int shell_exec_cmd(shell_t *shell, char **cmd);
int shell_exec_shell_cmd(char **cmd, shell_t *shell);
int shell_exec_bin_cmd(char **cmd, shell_t *shell);

int get_bin_path(const char *cmd_name, char **ptr_path, shell_t *shell);
int check_access_right_file(const char *bin_path);
char *get_bin_path_search_bin(const char *cmd_name, shell_t *shell);
int child_exit_status(int wstatus);

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
int my_alias(char **cmd, shell_t *shell);
int my_unalias(char **cmd, shell_t *shell);
int my_set(char **cmd, shell_t *shell);
int my_which(char **cmd, shell_t *shell);
int my_where(char **cmd, shell_t *shell);
int my_repeat(char **cmd, shell_t *shell);

// Builtins : sub-function
int where_show_all_path(const char *cmd_name, shell_t *shell);

//-------------------------------------------------
//                 - MODULES -
// MOD : REDIRECT
// CF redirection.h

// MOD : CHECKER
int entry_checker(shell_t *shell, cmd_t *cmd, const char *entry);
bool is_redirection(ID token_id);
bool is_text_token(token_t *ptr, bool include_parenthesis);
bool is_separator(token_t *ptr);
bool check_position_redirection_in_pipe(cmd_t *cmd);
bool check_have_empty_pipe(cmd_t *cmd);
bool have_missing_str_quote(const char *entry);
bool check_parenthesis(cmd_t *cmd);
bool have_missing_name_redirection(cmd_t *cmd);
bool have_several_redirection(cmd_t *cmd);
bool have_null_command(cmd_t *cmd);

//-------------------------------------------------
//                  - TOOLS -
void display_path_without_homepath(env_t *env, char *path);
char *merge_path_filename(const char *path, const char *filename);

int word_array_search(char **array, const int size, const char *str);
int word_array_search2(const char **array, const char *str);

bool char_is_letter(const char c);
bool str_is_alphanum(const char *str);
bool have_slash(const char *str);
bool str_have_only_chars(const char *str, const char *chars);
char *my_array_to_str(char **tab, bool parent);

//-------------------------------------------------
//                  - HISTORY -
char *terminal_read(shell_t *shell);
char *term_input(shell_t *shell);
void show_main_prompt(shell_t *shell);
char **add_to_hist(char **env, char *new_line);
int built_in_history(char **line, shell_t *shell);
bool flag_save(hist_build_t *ld, history_t *hist);
bool flag_load(hist_build_t *load, shell_t *shell);
void display_line(shell_t *shell, char *line, size_t pos);
bool ctrl_d_manage(int ch, shell_t *shell, char *line, size_t *pos);

//-------------------------------------------------
//                - MAGIC QUOTE -
#define BUF_SIZE 2048

char *get_magic_quote(shell_t *shell, char *entry);
bool load_magic_quote(shell_t *shell, cmd_t *cmd);

#endif
