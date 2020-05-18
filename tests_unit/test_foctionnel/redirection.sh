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

mkdir test_red
red_tcsh="test_red/tcsh_red.test"
red_mysh="test_red/mysh_red.test"

ret="-1"
passed="0"
failed="0"

rm $red_tcsh
rm $red_mysh

i="0"
declare -a basic_red=("ls > " "cat < " "grep grep < redirection.sh >" "cat < Makefile >" "cat < redirection.sh" "ls >>")
while [ $i -lt 6 ]
do
    echo -e ${basic_red[$i]}$red_mysh | $my &> $mysh_output
    echo -e ${basic_red[$i]}$red_tcsh | $ref &> $tcsh_output
    diff $red_tcsh $red_mysh

    ret=$?
    if [ "$ret" = 0 ]
    then
        echo "PASSED :"
        echo ${basic_red[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${basic_red[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

i="0"
declare -a error_red=("ls -l >" "> lol" "   > lol" "ls > < lol" "ls <> xd" "lol>>>" "lol ><> lol" "cat <<> lol" ">lol" "     > lol" "<< lol" ">> lol" "< lol" "  <   lol" "ls >>    " "ls >>     " "ls <<" "ls <<       ")

while [ $i -lt 18 ]
do
    echo -e ${error_red[$i]} | $my &> $mysh_output
    echo -e ${error_red[$i]} | $ref &> $tcsh_output
    diff $mysh_output $tcsh_output
    ret=$?
    if [ "$ret" = 0 ]
    then
        echo "PASSED :"
        echo ${error_red[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${error_red[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

i="0"
declare -a pipe_red=("ls | cat -e >" "cat < ./redirection.sh | cat -e > " "cat < ./redirection.sh | cat -e >> ")
while [ $i -lt 3 ]
do
    echo -e ${pipe_red[$i]}$red_mysh | $my &> $mysh_output
    echo -e ${pipe_red[$i]}$red_tcsh | $ref &> $tcsh_output
    diff $red_tcsh $red_mysh

    ret=$?
    if [ "$ret" = 0 ]
    then
        echo "PASSED :"
        echo ${pipe_red[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${pipe_red[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

i="0"
declare -a error_pipe_red=("ls > lol | cat -e" "ls >> lol | cat -e" "cat < lol | grep xs" "cat <| cat -e")

while [ $i -lt 4 ]
do
    echo -e ${error_pipe_red[$i]} | $my &> $mysh_output
    echo -e ${error_pipe_red[$i]} | $ref &> $tcsh_output
    diff $mysh_output $tcsh_output
    ret=$?
    if [ "$ret" = 0 ]
    then
        echo "PASSED :"
        echo ${error_pipe_red[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${error_pipe_red[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

echo "test :"
echo -e "\e[92m" "" "PASSED :" "\e[97m" $passed
echo -e "\e[91m" "\e[5m" "FAILED :" "\e[25m" "\e[97m" $failed
echo -e "\e[103m" "\e[94m" "TOTAL :" "\e[97m" "\e[49m" $[$passed+$failed]
exit $passed