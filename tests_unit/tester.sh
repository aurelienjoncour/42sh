#!/bin/bash

MYSHELL="$PWD/42sh"
REFER="/bin/tcsh -f"
TESTS_FILE="tests"
TRAPSIG=0

CAT=`which cat`
GREP=`which grep`
SED=`which sed`
RM=`which rm`
TR=`which tr`
HEAD=`which head`
TAIL=`which tail`
WC=`which wc`
CHMOD=`which chmod`
EXPR=`which expr`
MKDIR=`which mkdir`
CP=`which cp`

####
make -C ../
cp ../42sh .
###

for i in `env | grep BASH_FUNC_ | cut -d= -f1`; do
    f=`echo $i | sed s/BASH_FUNC_//g | sed s/%%//g`
    unset -f $f
done

disp_test()
{
  id=$1
  $CAT $TESTS_FILE | $GREP -A1000 "\[$id\]" | $GREP -B1000 "^\[$id-END\]" | $GREP -v "^\[.*\]"
}

run_script()
{
  SC="$1"
  echo "$SC" > /tmp/.tmp.$$
  . /tmp/.tmp.$$
  $RM -f /tmp/.tmp.$$
}

prepare_test()
{
  local testfn="/tmp/.tester.$$"
  local runnerfn="/tmp/.runner.$$"
  local refoutfn="/tmp/.refer.$$"
  local shoutfn="/tmp/.shell.$$"

  WRAPPER="$runnerfn"

  echo "#!/bin/bash" > $runnerfn
  echo "$SETUP" >> $runnerfn
  #echo "/usr/bin/cat "$testfn" | "$MYSHELL" ; echo Shell exit with code \$? > "$shoutfn" 2>&1" >> $runnerfn
  echo "/bin/bash -c 'cat "$testfn" | "$MYSHELL" ; echo Shell exit with code \$?' > "$shoutfn" 2>&1" >> $runnerfn
  echo "$CLEAN" >> $runnerfn
  echo "$SETUP" >> $runnerfn
  echo "$TCSHUPDATE" >> $runnerfn
  echo "/bin/bash -c 'cat "$testfn" | "$REFER" ; echo Shell exit with code \$?' > "$refoutfn" 2>&1" >> $runnerfn
  #echo "/usr/bin/cat "$testfn" | "$REFER" ; echo Shell exit with code \$? > "$refoutfn" 2>&1" >> $runnerfn
  echo "$CLEAN" >> $runnerfn

  #echo "#!/bin/bash" > $testfn
  echo "$TESTS" | $TR "²" "\n" > $testfn
  chmod 755 $testfn
  chmod 755 $runnerfn
  # echo "---------"
  # cat $WRAPPER
  # echo "---------"
}

load_test()
{
  id=$1
  debug=$2
  SETUP=`disp_test "$id" | $GREP "SETUP=" | $SED s/'SETUP='// | $SED s/'"'//g`
  CLEAN=`disp_test "$id" | $GREP "CLEAN=" | $SED s/'CLEAN='// | $SED s/'"'//g`
  NAME=`disp_test "$id" | $GREP "NAME=" | $SED s/'NAME='// | $SED s/'"'//g`
  TCSHUPDATE=`disp_test "$id" | $GREP "TCSHUPDATE=" | $SED s/'TCSHUPDATE='// | $SED s/'"'//g`
  TESTS=`disp_test "$id" | $GREP -v "SETUP=" | $GREP -v "CLEAN=" | $GREP -v "NAME=" | $GREP -v "TCSHUPDATE=" | $GREP -v "TESTS=" | $TR "\n" "²" | $SED s/"²$"//`
  prepare_test
  $WRAPPER
  nb=`$CAT /tmp/.refer.$$ | $GREP -v '^_=' | $GREP -v '^\[1\]' | $WC -l`
  i=1
  ok=1
  while [ $i -le $nb ]
  do
    l=`$CAT /tmp/.refer.$$ | $GREP -v '^_=' | $GREP -v '^\[1\]' | $HEAD -$i | $TAIL -1`
    a=`$CAT /tmp/.shell.$$ | $GREP -v '^_=' | $GREP -v '^\[1\]' | $GREP -- "$l$" | $WC -l`
    if [ $a -eq 0 ];then
      ok=0
    fi
    i=`$EXPR $i + 1`
  done

  if [ $ok -eq 1 ]
  then
    if [ $debug -ge 1 ]
    then
      echo "Test $id ($NAME) : OK"
      if [ $debug -eq 2 ]
      then
        echo "Output $MYSHELL :"
        $CAT -e /tmp/.shell.$$
        echo ""
        echo "Output $REFER :"
        $CAT -e /tmp/.refer.$$
        echo ""
      fi
    else
      echo "OK"
    fi
  else
    if [ $debug -ge 1 ]
    then
      echo "Test $id ($NAME) : KO - Check output in /tmp/test.$$/$id/"
      $MKDIR -p /tmp/test.$$/$id 2>/dev/null
      $CP /tmp/.shell.$$ /tmp/test.$$/$id/mysh.out
      $CP /tmp/.refer.$$ /tmp/test.$$/$id/tcsh.out
      echo "42sh / Tcsh DIFF:"
      echo -e "\e[31m"
      diff /tmp/test.$$/$id/mysh.out /tmp/test.$$/$id/tcsh.out
      echo -e "\e[0m"
    else
      echo "KO"
    fi
  fi
}

if [ $TRAPSIG -eq 1 ]
then
  for sig in `trap -l`
  do
    echo "$sig" | grep "^SIG" >/dev/null 2>&1
    if [ $? -eq 0 ]
    then
      trap "echo Received signal $sig !" $sig
    fi
  done
fi

if [ ! -f $TESTS_FILE ]
then
  echo "No tests file. Please read README.ME" >&2
  exit 1
fi

if [ ! -f $MYSHELL ]
then
  echo "$MYSHELL not found" >&2
  exit 1
fi

if [ $# -eq 2 ]
then
  echo "Debug mode" >&2
  echo "Shell : $MYSHELL" >&2
  echo "Reference : $REFER" >&2
  echo ""
fi

if [ ! $# -eq 0 ]; then
    TESTS_FILE=$1
fi
if [ $# == 0 ] || [ ! -f $TESTS_FILE ]; then
    if [ ! -f $TESTS_FILE ]; then
        echo -e "\n$TESTS_FILE: Test file not found."
    fi
    echo -e "\nUsage: [Test Filename] <-d> <id Test>\n"
    exit 1
fi
echo "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
echo -e "\tTEST FILE: $TESTS_FILE\n"

if [ $# -eq 1 ]; then
  for lst in `cat $TESTS_FILE | grep "^\[.*\]$" | grep -vi end | sed s/'\['// | sed s/'\]'//`
  do
    path_backup=$PATH
    load_test $lst 1
    export PATH=$path_backup
  done
else
    if [ $# -eq 2 ]; then
        load_test $2 0
    else
        if [ "X$2" = "X-d" ]; then
            load_test $3 2
        else
            load_test $2 2
        fi
    fi
fi

rm -f log
