/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** read file : simonR
*/

#include "my.h"

static const int BUFFER_BLOCK = 42;
static const int BUFFER_MAX_LEN = 1000000;

static int realloc_buffer(char **buffer, int *buffer_len, int str_len)
{
    char *new_buffer = malloc(sizeof(char) * (*buffer_len + BUFFER_BLOCK));

    if (!new_buffer)
        return EXIT_FAILURE;
    *buffer_len += BUFFER_BLOCK;
    my_strncpy(new_buffer, *buffer, str_len);
    free(*buffer);
    *buffer = new_buffer;
    return EXIT_SUCCESS;
}

static int read_content(char **content, int *len, int fd)
{
    int buffer_len = BUFFER_BLOCK;
    int ret;

    while (true) {
        ret = read(fd, *content + (*len), BUFFER_BLOCK - 1);
        if (ret == -1)
            return EXIT_FAILURE;
        (*len) += ret;
        if (ret < (BUFFER_BLOCK - 1) || (*len) > BUFFER_MAX_LEN)
            return EXIT_SUCCESS;
        if (realloc_buffer(content, &buffer_len, *len) == EXIT_FAILURE)
            return EXIT_FAILURE;
    }
}

char **build_word_array(char *content, int len)
{
    char **word_array = NULL;

    if (len > 0) {
        content[len - 1] = '\0';
        word_array =  my_str_to_word_array(content, "\n");
    } else {
        word_array = NULL;
    }
    free(content);
    return word_array;
}

char **my_read_file(const char *filepath)
{
    int fd;
    int len = 0;
    char *content = NULL;

    fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        my_putstr_error("read_file : error fail to open file.\n");
        return NULL;
    }
    if (!(content = malloc(sizeof(char) * BUFFER_BLOCK)))
        return NULL;
    if (read_content(&content, &len, fd) == EXIT_FAILURE) {
        my_putstr_error("read_content : error\n");
        return NULL;
    }
    return build_word_array(content, len);
}
