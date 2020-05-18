#!/usr/bin/env bash

if [ "$#" -ne 1 ]
then
    echo "Usage : ./$0 path_to_minishell" 
    exit 1
fi

ref="/bin/tcsh"
my="$1"

output="/tmp/minishell1_tests"

mkdir -p "$output"

mysh_output="$output/mysh_output"
tcsh_output="$output/tcsh_output"

ret="-1"
passed="0"
failed="0"

i="0"
declare -a error_pipe=("   | lol" "| lol" "ls | pdtr | xd | lol" "ls | cd | exit LOL | ls" "ptdr | lol | xd" "ls | " " ls | | xd" "ls | ./lol |" "ls |  | ./LOL" "ls |" "  | ls")

while [ $i -lt 11 ]
do
    echo -e ${error_pipe[$i]} | $my &> $mysh_output
    echo -e ${error_pipe[$i]} | $ref &> $tcsh_output
    diff $mysh_output $tcsh_output
    ret=$?
    if [ "$ret" = 0 ]
    then
        echo "PASSED :"
        echo ${error_pipe[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${error_pipe[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

i="0"
declare -a pipe_test=("ls -l /dev | grep tty | grep vcs | grep 128 | cat -e" "ls -la | cat -e | cat -e" "cat ../Makefile | grep main")

while [ $i -lt 3 ]
do
    echo -e ${pipe_test[$i]} | $my &> $mysh_output
    echo -e ${pipe_test[$i]} | $ref &> $tcsh_output
    diff $mysh_output $tcsh_output
    ret=$?
    if [ "$ret" = 0 ]
    then
        echo "PASSED :"
        echo ${pipe_test[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${pipe_test[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

i="0"
declare -a other_pipe=("ls | cat -e" "cat -e < minishell2.sh | cat -e" "ls -R ../../../../../ | cat -e" "ls -l /dev/ | grep tty | cat -e" "ls | cat -e" "exit | cat -e")

while [ $i -lt 6 ]
do
    echo -e ${other_pipe[$i]} | $my &> $mysh_output
    echo -e ${other_pipe[$i]} | $ref &> $tcsh_output
    diff $mysh_output $tcsh_output
    ret=$?
    if [ "$ret" = 0 ]
    then
        echo "PASSED :"
        echo ${other_pipe[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${other_pipe[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

echo "test :"
echo -e "\e[92m" "" "PASSED :" "\e[97m" $passed
echo -e "\e[91m" "\e[5m" "FAILED :" "\e[25m" "\e[97m" $failed
echo -e "\e[103m" "\e[94m" "TOTAL :" "\e[97m" "\e[49m" $[$passed+$failed]
exit $passed