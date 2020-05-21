/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** autocompletion get files
*/

#include <dirent.h>
#include <string.h>
#include "my.h"
#include "autocompletion.h"

static char *get_line_path(char **path, int i)
{
    char *cmd;
    int k = 0;

    if (*path == NULL || **path == '\0') {
        *path = "./";
        return my_strdup("");
    }
    for (; i >= 0 && (*path)[i] != ' ' && (*path)[i] != '/'; i--);
    cmd = my_strdup(*path + i + 1);
    for (; cmd[k] != ' ' && cmd[k] != '\0'; k++);
    cmd[k] = '\0';
    if (i <= 0 || (*path)[i] == ' ') {
        *path = "./";
        return cmd;
    }
    (*path)[i + 1] = '\0';
    for (; i > 0 && (*path)[i] != ' '; i--);
    *path += i + 1;
    return cmd;
}

static file_t *add_file(char *name, file_t *next,
                        char *path, char const *cmd)
{
    struct stat st;
    file_t *file;

    if (name != NULL && name[0] != '.'
    && !my_strncmp(cmd, name, my_strlen(cmd))) {
        file = malloc(sizeof(file_t));
        path = my_strdupcat(3, path, "/", name);
        if (file == NULL || path == NULL || stat(path, &st) == -1)
            return next;
        file->name = my_strdupcat(2, name, S_ISDIR(st.st_mode) ? "/" : "");
        free(path);
        if (file->name == NULL) {
            free(file);
            return next;
        }
        file->next = next;
        return file;
    }
    return next;
}

static file_t *get_dir_files(file_t *files, char *path, char *cmd)
{
    DIR *dir = opendir(path);
    struct dirent *d_file = dir != NULL ? readdir(dir) : NULL;

    if (dir == NULL)
        fprintf(stdout, "\n%s not found\n\n", path);
    while (d_file != NULL && cmd != NULL) {
        files = add_file(d_file->d_name, files, path, cmd);
        d_file = readdir(dir);
    }
    closedir(dir);
    return files;
}

static file_t *get_path_dir_files(file_t *files, env_t *env, char *cmd)
{
    char **cmd_list = my_str_to_word_array(my_env_get_value(env, "PATH"), ":");

    if (cmd_list == NULL)
        return NULL;
    for (int i = 0; cmd_list[i] != NULL; i++) {
        files = get_dir_files(files, cmd_list[i], cmd);
        free(cmd_list[i]);
    }
    free(cmd_list);
    return files;
}

file_t *get_files(char *path, size_t pos, env_t *env)
{
    char *line = path;
    file_t *files;
    char *cmd = get_line_path(&path, pos);

    if (cmd == NULL)
        return NULL;
    files = get_dir_files(NULL, path, cmd);
    if (line != NULL && *line != '\0') {
        for (; line[0] == ' '; line++);
        if (!my_strcmp(line, cmd))
            files = get_path_dir_files(files, env, cmd);
    }
    free(cmd);
    return files;
}