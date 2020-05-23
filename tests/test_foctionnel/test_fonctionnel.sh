#!/usr/bin/env bash

if [ "$#" -ne 1 ]
then
    echo "Usage : ./$0 path_to_minishell" 
    exit 1
fi

passed="0"

./minishell1.sh "$1"
passed=$[$passed+$?]
./minishell2.sh "$1"
passed=$[$passed+$?]
./pipe.sh "$1"
passed=$[$passed+$?]
./redirection.sh "$1"
passed=$[$passed+$?]


echo "ALL TESTS :"
echo -e "\e[92m" "" "PASSED :" "\e[97m" $passed
echo -e "\e[92m" "" "PASSED :" "\e[97m"
exit $passed