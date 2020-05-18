/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** shell command function
*/

#include "shell.h"

static bool is_number(char *number)
{
    for (size_t i = 0; number[i]; i++) {
        if (number[i] == '-' && i == 0)
            continue;
        if (number[i] < '0' || number[i] > '9')
            return false;
    }
    return true;
}

static bool check_nb_args(char **command)
{
    for (size_t i = 0; command[i]; i++) {
        if (i > 1)
            return true;
    }
    return false;
}

static int repeat_command(char **cmd, shell_t *shell)
{
    int number = my_getnbr(cmd[1]);
    char *entry = NULL;
    int return_value = 0;
    shell_t sub_shell;

    if (shell_create(&sub_shell, shell->env.var) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    for (int i = 0; i < number; i++) {
        entry = my_array_to_str(&cmd[2], false);
        return_value = shell_exec(&sub_shell, entry);
    }
    shell->exit_status = sub_shell.exit_status;
    shell_destroy(&sub_shell);
    return return_value;
}

static int make_only_redirection(char **cmd, shell_t *shell)
{
    char *entry = my_array_to_str(&cmd[2], false);
    cmd_t *cmd_s = parse_entry(entry);
    redirect_t redirect;
    int return_value = 0;

    free(entry);
    if (entry_checker(shell, cmd_s, entry) == EXIT_ERROR)
        return EXIT_ERROR;
    return_value = redirection_process(cmd_s, &redirect);
    clean_redirect(&redirect);
    return return_value;
}

int my_repeat(char **cmd, shell_t *shell)
{
    if (!is_number(cmd[1])) {
        my_putstr_error("repeat : Badly formed number.");
        shell->exit_status = ERROR_STATUS;
        return EXIT_ERROR;
    }
    if (!check_nb_args(cmd)) {
        my_putstr_error("repeat : Too few arguments.");
        shell->exit_status = ERROR_STATUS;
        return EXIT_ERROR;
    }
    if (my_getnbr(cmd[1]) != 0)
        return repeat_command(cmd, shell);
    return make_only_redirection(cmd, shell);
}
