function check_executable
{
    if [ $# != 1 ];then
      echo "Error. check_executable takes exactly one argument.";
      return 1;
    else
        if [ -f $1 ];then
          if [ -x $1 ];then
            return 0;
          else
            echo "Error. $1 is not executable.";
            return 1;
          fi
        else
            echo "Error. The executable $1 is not a file or does not exist.";
            return 1;
        fi
    fi
}

function check_valgrind_errors
{
    if [ $# != 1 ];then
        echo "Error. check_valgrind_errors takes exactly one argument.";
        return 100;
    fi
    LOGFILE=$1
    if [ ! -s $LOGFILE ];then
        echo "Error. Could not examine valgrind log at $LOGFILE".
        return 101;
    fi
    RESULT=`$GREP "ERROR SUMMARY: 0" $LOGFILE`
    if [ -z "$RESULT" ];then
        if [ "$DO_LEAKCHECK" == "yes" ];then
          RESULT=`$GREP "definitely lost: 0" $LOGFILE`
          if [ -z "$RESULT" ];then
            return 103;
          fi
        fi
        return 102;
    else
        if [ "$DO_LEAKCHECK" == "yes" ];then
          RESULT=`$GREP "definitely lost: 0" $LOGFILE`
          if [ -z "$RESULT" ];then
            return 104;
          fi
        fi
    fi
    return 0;
}


