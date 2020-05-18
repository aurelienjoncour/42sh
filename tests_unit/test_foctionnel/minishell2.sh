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
ret2="-1"
ret1="-1"
declare -a exit_value=("./error_handling/segv.out" "./error_handling/wrongarch" "./error_handling/flotingpoint.out" "./error_handling/free.out" "./etca1" "./error_handling/noperm.out" "/." "clear" "cd lol" "ls ./lol")
while [ $i -lt 10 ]
do
    echo -e ${exit_value[$i]} | $my &> $mysh_output
    ret1=$?
    echo -e ${exit_value[$i]} | $ref &> $tcsh_output
    ret2=$?

    if [ "$ret1" -eq "$ret2" ]
    then
        echo "PASSED :"
        echo ${exit_value[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${exit_value[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

i="0"
declare -a parth_test=("ls;ls -l" ";" ";     ls  ;   ls;;;;" "cd ..;ls;cd -; ls" "touch TEST; cat ./TEST; rm TEST" "cd ..;cat ./Makefile;ls -l; cd -")

while [ $i -lt 6 ]
do
    echo -e ${parth_test[$i]} | $my &> $mysh_output
    echo -e ${parth_test[$i]} | $ref &> $tcsh_output
    diff $mysh_output $tcsh_output
    ret=$?
    if [ "$ret" = 0 ]
    then
        echo "PASSED :"
        echo ${parth_test[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${parth_test[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

echo "test :"
echo -e "\e[92m" "" "PASSED :" "\e[97m" $passed
echo -e "\e[91m" "\e[5m" "FAILED :" "\e[25m" "\e[97m" $failed
echo -e "\e[103m" "\e[94m" "TOTAL :" "\e[97m" "\e[49m" $[$passed+$failed]
exit $passed