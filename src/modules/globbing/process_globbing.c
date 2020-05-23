/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-15T08:53:41+02:00 | Author: simon
*/

#include "globbing.h"
#include <glob.h>

static int replace_token(token_t *token_list, cmd_t *cmd, token_t *old_token)
{
    token_t *last = get_last_token(token_list);

    insert_new_token(old_token, token_list, last, cmd);
    free(old_token->token);
    free(old_token);
    return EXIT_SUCCESS;
}

static int post_process(file_list_t *filenames, token_t *tok, cmd_t *cmd,
glob_t *pglob)
{
    token_t *token_list;

    pglob->gl_pathv = my_advanced_sort_word_array(pglob->gl_pathv,
        &my_strcmp_nocase, pglob->gl_pathc);
    for (size_t i = 0; i < pglob->gl_pathc; i++) {
        my_file_list_add(&filenames, pglob->gl_pathv[i]);
    }
    token_list = list_to_token_list(filenames);
    if (!token_list) {
        return EXIT_ERROR;
    }
    if (replace_token(token_list, cmd, tok) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    my_file_list_destroy(filenames);
    return EXIT_SUCCESS;
}

int process_globbing(token_t *tok, cmd_t *cmd)
{
    int ret = EXIT_SUCCESS;
    int status;
    file_list_t *list = NULL;
    glob_t pglob;

    status = glob(tok->token, GLOB_TILDE, NULL, &pglob);
    if (status == GLOB_NOMATCH) {
        ret = EXIT_FAIL;
    } else if (status != 0) {
        ret = EXIT_FAIL;
    }
    if (status == 0 && post_process(list, tok, cmd, &pglob) == EXIT_ERROR) {
        ret = EXIT_FAIL;
    }
    globfree(&pglob);
    return ret;
}
