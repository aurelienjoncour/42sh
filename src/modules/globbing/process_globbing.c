/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-15T08:53:41+02:00 | Author: simon
*/

#include "globbing.h"

static int split_filepath(const char *str, char **ptr_path, char **ptr_regexp)
{
    int idx_slash = -1;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == '/') {
            idx_slash = (int)i;
        }
    }
    if (idx_slash == -1) {
        *ptr_path = my_strdup("./");
    } else {
        *ptr_path = my_strndup(str, (idx_slash + 1));
    }
    *ptr_regexp = my_strdup(&str[idx_slash + 1]);
    if (!(*ptr_path) || !(*ptr_regexp)) {
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}

static int process_filelist(file_list_t **ptr_filenames, const char *token)
{
    file_list_t *filenames = *ptr_filenames;

    for (file_list_t *ptr = filenames; ptr != NULL; ptr = ptr->next) {
        fprintf(stderr, ":%s\n", ptr->name); // DEBUG
    }
    return EXIT_SUCCESS;
}

int process_globbing(const char *token)
{
    char *path;
    char *regexp;
    file_list_t *filenames = NULL;

    if (split_filepath(token, &path, &regexp) == EXIT_ERROR) {
        return EXIT_FAIL;
    }
    if (my_read_dir(&filenames, path) <= 0) {
        free(path);
        free(regexp);
        return EXIT_FAIL;
    }
    if (process_filelist(&filenames, token) == EXIT_ERROR) {
        return EXIT_FAIL;
    }
    free(path);
    free(regexp);
    my_file_list_destroy(filenames);
    return EXIT_SUCCESS;
}
