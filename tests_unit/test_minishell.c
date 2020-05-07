/*
** EPITECH PROJECT, 2020
** Unit_Test_Criterion
** File description:
** Test File
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "shell.h"

void disp(char **wa)
{
    for (size_t i = 0; wa[i] != NULL; i++) {
        my_printf("(%s)\n", wa[i]);
    }
    my_putstr("\n");
}

Test(command_format, t01)
{
    char *format = command_format("echo hello world");

    cr_assert_str_eq(format, "echo\ahello\aworld");
    free(format);
}

Test(command_format, t02)
{
    char *format = command_format(" echo  hello  world   ");

    cr_assert_str_eq(format, "\aecho\a\ahello\a\aworld\a\a\a");
    free(format);
}

Test(command_format, t03)
{
    char *format = command_format("cat \"hello\"\"world\"");

    cr_assert_str_eq(format, "cat\ahelloworld");
    free(format);
}

Test(command_format, t04)
{
    char *format = command_format("echo hello>log");

    cr_assert_str_eq(format, "echo\ahello\a>\alog");
    free(format);
}

Test(command_format, t05)
{
    char *format = command_format("echo \"'hello'world\" hello>log");

    cr_assert_str_eq(format, "echo\a'hello'world\ahello\a>\alog");
    free(format);
}

Test(command_format, t06)
{
    char *format = command_format("echo'hello'  world>>log<<log");

    cr_assert_str_eq(format, "echohello\a\aworld\a>>\alog\a<<\alog");
    free(format);
}

Test(command_format, t07)
{
    char *format = command_format(" echo 'hel'lo'  '  ' orld<log<<log");

    cr_assert_str_eq(format, "\aecho\ahello  \a\a orld<log<<log");
    free(format);
}

Test(command_format, t08)
{
    char *format = command_format("echo '<>\"   \"  '");

    cr_assert_str_eq(format, "echo\a<>\"   \"  ");
    free(format);
}

Test(command_format, t09)
{
    char *format = command_format(" ls \\\"hello world");

    cr_assert_str_eq(format, "\als\a\\\"hello\aworld");
    free(format);
}

Test(command_format, t10)
{
    char *format = command_format(" ls \"a\"b c\\\" ");

    cr_assert_str_eq(format, "\als\aab\ac\\\"\a");
    free(format);
}

Test(command_to_word_array, t01)
{
    char **result = command_to_word_array("aa\abb\acc");

    if (result)
        disp(result);
    cr_assert_eq(word_array_len(result), 3);
    word_array_destroy(result);
}

Test(command_to_word_array, t02)
{
    char **result = command_to_word_array("aa\abbccdd");

    if (result)
        disp(result);
    cr_assert_arr_eq(result[1], "bbccdd", my_strlen(result[1]));
    word_array_destroy(result);
}

Test(command_to_word_array, t03)
{
    char **result = command_to_word_array("aa\abc\" \"cb \a>\add");

    if (result)
        disp(result);
    cr_assert_arr_eq(result[1], "bc\" \"cb ", my_strlen(result[1]));
    word_array_destroy(result);
}

Test(command_to_word_array, t04)
{
    char **result = command_to_word_array("aa\abb  cc\a>>\add");

    if (result) {
        disp(result);
    }
    cr_assert_arr_eq(result[2], ">>", my_strlen(result[2]));
    cr_assert_arr_eq(result[1], "bb  cc", my_strlen(result[1]));
    cr_assert_arr_eq(result[0], "aa", my_strlen(result[0]));
    cr_assert_arr_eq(result[3], "dd", my_strlen(result[3]));
    word_array_destroy(result);
}

Test(command_to_word_array, t05)
{
    char **result = command_to_word_array("\a\als\ahelloworld\a\a\a");

    if (result)
        disp(result);
    cr_assert_arr_eq(result[1], "helloworld", my_strlen(result[1]));
    word_array_destroy(result);
}
