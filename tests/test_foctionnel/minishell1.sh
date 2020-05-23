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
declare -a com=("ls" "cd ./test_bash.sh" "cd mdr" "ls -l" "setenv mdr lol xd" "setenv $HOME" "cd ../ my_test" "setenv HO?ME" "unsetenv")

while [ $i -lt 9 ]
do
    echo ${com[$i]} | $my &> $mysh_output
    echo ${com[$i]} | $ref &> $tcsh_output
    diff $mysh_output $tcsh_output
    ret=$?
    if [ "$ret" = 0 ]
    then
        echo "PASSED :"
        echo ${com[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${com[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

i="0"
declare -a error=("./error_handling/segv.out" "./error_handling/wrongarch" "./error_handling/flotingpoint.out" "./error_handling/free.out" "./etca1" "./error_handling/noperm.out" "/.")

while [ $i -lt 7 ]
do
    echo ${error[$i]} | $my &> $mysh_output
    echo ${error[$i]} | $ref &> $tcsh_output
    diff $mysh_output $tcsh_output
    ret=$?
    if [ "$ret" = 0 ]
    then
        echo "PASSED :"
        echo ${error[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${error[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

i="0"
declare -a bas_com=("cat test_bash.sh" "clear" "top" "etca2" "setenv test lol" "setenv *hom test" "setenv home_ lol" "setenv 1home lol" "setenv _home lol")

while [ $i -lt 9 ]
do
    echo ${bas_com[$i]} | $my &> $mysh_output
    echo ${bas_com[$i]} | $ref &> $tcsh_output
    diff $mysh_output $tcsh_output
    ret=$?
    if [ "$ret" = 0 ]
    then
        echo "PASSED :"
        echo ${bas_com[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${bas_com[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

i="0"
declare -a no_env=("cd" "cd -" "cd ~" "cd .." "clear" "etla1")

while [ $i -lt 6 ]
do
    echo ${no_env[$i]} | env -i $my &> $mysh_output
    echo ${no_env[$i]} | env -i $ref &> $tcsh_output
    diff $mysh_output $tcsh_output
    ret=$?
    if [ "$ret" = 0 ]
    then
        echo "PASSED :"
        echo ${no_env[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${no_env[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

i="0"
declare -a cd_tst=("cd ..\npwd" "cd ../src\ncd -\npwd" "cd ../src\npwd" "cd ~\npwd" "cd -")

while [ $i -lt 5 ]
do
    echo -e ${cd_tst[$i]} | $my &> $mysh_output
    echo -e ${cd_tst[$i]} | $ref &> $tcsh_output
    diff $mysh_output $tcsh_output
    ret=$?
    if [ "$ret" = 0 ]
    then
        echo "PASSED :"
        echo ${cd_tst[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${cd_tst[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

i="0"
declare -a exit_test=("exit" "exit 12" "exit rb" "exit 12 23" "exit 12 RB" "exitt" "exit rb 2")

while [ $i -lt 7 ]
do
    echo -e ${exit_test[$i]} | $my &> $mysh_output
    echo -e ${exit_test[$i]} | $ref &> $tcsh_output
    diff $mysh_output $tcsh_output
    ret=$?
    if [ "$ret" = 0 ]
    then
        echo "PASSED :"
        echo ${exit_test[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${exit_test[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

i="0"
ret1="-1"
ret2="-1"
declare -a exit_test=("exit 12" "exit 345" "exit -789" "exit 0" "exit -1" "exit 1" "exit 255")

while [ $i -lt 7 ]
do
    echo -e ${exit_test[$i]} | $my &> $mysh_output
    ret1=$?
    echo -e ${exit_test[$i]} | $ref &> $tcsh_output
    ret2=$?

    if [ "$ret1" -eq "$ret2" ]
    then
        echo "PASSED :"
        echo ${exit_test[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${exit_test[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

i="0"
rm_env="unsetenv HOSTTYPE VENDOR OSTYPE MACHTYPE SHLVL LOGNAME USER GROUP HOST\n"
put="\nenv"
declare -a setenv=("setenv" "setenv mdr" "setenv mdr lol" "setenv mdr lol" "setenv home2")

while [ $i -lt 5 ]
do
    echo -e ${setenv[$i]} $put | env -i $my &> $mysh_output
    echo -e $rm_env ${setenv[$i]} $put | env -i $ref &> $tcsh_output
    diff $mysh_output $tcsh_output
    ret=$?
    if [ "$ret" = 0 ]
    then
        echo "PASSED :"
        echo ${setenv[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${setenv[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

i="0"
rm_env="unsetenv HOSTTYPE VENDOR OSTYPE MACHTYPE SHLVL LOGNAME USER GROUP HOST\n"
set_test="setenv mdr lol\n"
put="\nenv"
declare -a unsetenv=("unsetenv pwd" "unsetenv mdr" "unsetenv lol" "unsetenv pwd lol mdr")

while [ $i -lt 4 ]
do
    echo -e ${unsetenv[$i]} $put | env -i $my &> $mysh_output
    echo -e $rm_env ${unsetenv[$i]} $put | env -i $ref &> $tcsh_output
    diff $mysh_output $tcsh_output
    ret=$?
    if [ "$ret" = 0 ]
    then
        echo "PASSED :"
        echo ${unsetenv[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${unsetenv[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

i="0"
declare -a bas_com2=("grep PASSED" "man fork" "echo 42" "./LOL" "ls ../../ -lta" "../mysh" "clear" "touch TROLLL\n rm TROLLL" "chmod 777 temp" "grep")

mkdir temp
while [ $i -lt 10 ]
do
    echo -e ${bas_com2[$i]} | $my &> $mysh_output
    echo -e ${bas_com2[$i]} | $ref &> $tcsh_output
    diff $mysh_output $tcsh_output
    ret=$?
    if [ "$ret" = 0 ]
    then
        echo "PASSED :"
        echo ${bas_com2[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${bas_com2[$i]}
        failed=$[$failed+1]
    fi

    i=$[$i+1]
done
rm -r temp

i="0"
prepare_env="setenv PATH ../:./error_handling\n"
declare -a setenv=("mysh" "segv.out" "free.out" "noperm.out" "wrongarch")

while [ $i -lt 5 ]
do
    echo -e $prepare_env ${setenv[$i]} | $my &> $mysh_output
    echo -e $prepare_env ${setenv[$i]} | $ref &> $tcsh_output
    diff $mysh_output $tcsh_output
    ret=$?
    if [ "$ret" = 0 ]
    then
        echo "PASSED :"
        echo ${setenv[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${setenv[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

i="0"
declare -a parth_test=("\tls   -l -a  " " ls         ../tests  ./error_handling  " "\t  \tls\t " "\t \tls\t-l\t" "" "         " "\t" "EOT" "can" "\n")

while [ $i -lt 10 ]
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

i="0"
declare -a parth_test=("ls;ls -l" ";" ";     ls  ;   ls;;;;" "cd ..;ls;cd -; ls" "touch TEST; cat TEST; rm TEST" "cd ..;cat Makefile;ls -l; cd -")

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

i="0"
declare -a error_pipe_redirect=("   | lol" "| lol" ">lol" "     > lol" "<< lol" ">> lol" "< lol" "  <   lol")

while [ $i -lt 8 ]
do
    echo -e ${error_pipe_redirect[$i]} | $my &> $mysh_output
    echo -e ${error_pipe_redirect[$i]} | $ref &> $tcsh_output
    diff $mysh_output $tcsh_output
    ret=$?
    if [ "$ret" = 0 ]
    then
        echo "PASSED :"
        echo ${error_pipe_redirect[$i]}
        passed=$[$passed+1]
    else
        echo "FAILED :"
        echo ${error_pipe_redirect[$i]}
        failed=$[$failed+1]
    fi
    i=$[$i+1]
done

########################

echo "test :"
echo -e "\e[92m" "" "PASSED :" "\e[97m" $passed
echo -e "\e[91m" "\e[5m" "FAILED :" "\e[25m" "\e[97m" $failed
echo -e "\e[103m" "\e[94m" "TOTAL :" "\e[97m" "\e[49m" $[$passed+$failed]
exit $passed