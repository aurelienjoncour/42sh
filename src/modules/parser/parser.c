/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** parser
*/

#include <stdlib.h>
#include "parser.h"

const parser_t delimit[] =
{
    {" ", "", D_NORMAL, ID_SPACE},
    {"\t", "", D_NORMAL, ID_TAB},
    {"\"", "\"", D_DELIM, ID_DOUBLE_QUOTE},
    {"'", "'", D_DELIM, ID_SIMPLE_QUOTE},
    {"`", "`", D_DELIM, ID_BACK_QUOTE},
    {"(", ")", D_DELIM, ID_PARENTHESE},
    {">&", "", D_NORMAL, ID_REDIRECTION},
    {">>", "", D_GET, ID_DOUBLE_RIGHT},
    {">", "", D_GET, ID_RIGHT},
    {"<<", "", D_GET, ID_DOUBLE_LEFT},
    {"<", "", D_GET, ID_LEFT},
    {"||", "", D_SEPARATOR, ID_OR},
    {"&&", "", D_SEPARATOR, ID_AND},
    {";", "", D_SEPARATOR, ID_SEP},
    {"|", "", D_GET, ID_PIPE},
    {"&", "", D_GET, ID_BACKGROUND},
    {NULL, NULL, ID_WIHOUT, ID_WIHOUT},
};