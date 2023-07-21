#!/bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
BOLD="\033[1m"

SUCCES=0
FAIL=0
TOTAL=0

test () {
  ./s21_cat $1 $2 > temp_1
  cat $1 $2 > temp_2

  if cmp temp_1 temp_2
  then
    echo "${GREEN}SUCC\t./s21_cat $1 $2"
    SUCCES=$(($SUCCES + 1))  
  else
    echo "${RED}FAIL\t./s21_cat $1 $2"
    FAIL=$(($FAIL + 1))   
  fi

  tput sgr0
  rm temp_1 temp_2
}

# ========== * без ключей * ==========
for file in "case" "sonet"
do
  echo ______________________________
  echo "TEST\tWITHOUT KEYS\t${file}"
  test "" $file
  # read pause
done

# ==== * без ключей | два файла * ====
echo ______________________________
echo "TEST\tWITHOUT KEYS\tcase sonet"
test "" "case sonet"
# read pause

# ========== * один ключ * ==========
for file in "case" "sonet"
do
  echo ______________________________
  echo "TEST\t1 KEY\t${file}"
  for key in -b -e -n -s -t
  do
    test $key $file
    # read pause
  done

  # echo ______________________________
  # echo "TEST\t1 GNU KEY\t${file}"
  # for key in --number-nonblank -E --number  --squeeze-blank -T
  # do
  #   test $key $file
  #   # read pause
  # done
done

# ==== * один ключ | два файла * ====
echo ______________________________
echo "TEST\t1 KEY\tcase sonet"
for key in -b -e -n -s -t
do
  test $key "case sonet"
  # read pause
done

# echo ______________________________
# echo "TEST\t1 GNU KEY\tcase sonet"
# for key in --number-nonblank -E --number  --squeeze-blank -T
# do
#   test $key "case sonet"
#   # read pause
# done


# ===== * один ключ | ∄ файл * ======
# for file in "nothing" "sonet"
# do
#   echo ______________________________
#   echo "TEST\t1 KEY\t${file}"
#   for key in -b -e -n -s -t
#   do
#     test $key $file
#     # read pause
#   done

#   echo ______________________________
#   echo "TEST\t1 GNU KEY\t${file}"
#   for key in --number-nonblank -E --number  --squeeze-blank -T
#   do
#     test $key $file
#     # read pause
#   done
# done

# ========== * два ключа * ==========
for file in "case" "sonet"
do
  echo ______________________________
  echo "TEST\t2 KEYS\t${file} "
  for key1 in -b -e -n -s -t
  do
    for key2 in -b -e -n -s -t
    do
      if 
      [ $key1 != $key2 ] 
      then
      test "$key1 $key2" $file
      fi
      # read pause
    done
  done

  # echo ______________________________
  # echo "TEST\t2 GNU KEYS\t${file} "
  # for key1 in --number-nonblank -E --number  --squeeze-blank -T
  # do  
  #   for key2 in --number-nonblank -E --number  --squeeze-blank -T
  #   do
  #     if 
  #     [ $key1 != $key2 ] 
  #     then
  #     test "$key1 $key2" $file
  #     # read pause
  #     fi
  #   done
  # done

  # echo ______________________________
  # echo "TEST\t2 MIXED KEYS\t${file} "
  # for key1 in -b -e -n -s -t
  # do  
  #   for key2 in --number-nonblank -E --number  --squeeze-blank -T
  #   do
  #     test "$key1 $key2" $file
  #     # read pause
  #   done
  # done

done

# ===== * два ключа | два файла * ====
echo ______________________________
echo "TEST\t2 KEYS\tcase sonet "
for key1 in -b -e -n -s -t
do
  for key2 in -b -e -n -s -t
  do
    if 
    [ $key1 != $key2 ] 
    then
    test "$key1 $key2" "case sonet"
    # read pause
    fi
  done
done

# echo ______________________________
# echo "TEST\t2 GNU KEYS\tcase sonet"
# for key1 in --number-nonblank -E --number  --squeeze-blank -T
# do  
#   for key2 in --number-nonblank -E --number  --squeeze-blank -T
#   do
#     if 
#     [ $key1 != $key2 ] 
#     then
#     test "$key1 $key2" "case sonet"
#     # read pause
#     fi
#   done
# done

# echo ______________________________
# echo "TEST\t2 MIXED KEYS\tcase sonet "
# for key1 in -b -e -n -s -t
# do  
#   for key2 in --number-nonblank -E --number  --squeeze-blank -T
#   do
#     test "$key1 $key2" "case sonet"
#     # read pause
#   done
# done

# ========== * три ключа * ==========
for file in "case" "sonet"
do
  echo ______________________________
  echo "TEST\t3 KEYS\t${file} "
  for key1 in -b -e -n -s -t
  do
    for key2 in -b -e -n -s -t
    do
      for key3 in -b -e -n -s -t
      do
        if 
        [ $key1 != $key2 ] && [ $key2 != $key3 ] && [ $key1 != $key3 ]
        then
        test "$key1 $key2 $key3" $file
        # read pause
        fi
      done
    done
  done

  # echo ______________________________
  # echo "TEST\t3 GNU KEYS\t${file} "
  # for key1 in --number-nonblank -E --number  --squeeze-blank -T
  # do  
  #   for key2 in --number-nonblank -E --number  --squeeze-blank -T
  #   do
  #     for key3 in --number-nonblank -E --number  --squeeze-blank -T
  #     do
  #       if 
  #       [ $key1 != $key2 ] && [ $key2 != $key3 ] && [ $key1 != $key3 ]
  #       then
  #       test "$key1 $key2 $key3" $file
  #       # read pause
  #       fi
  #     done
  #   done
  # done  
done

# ==== * три ключа | два файла * ====
echo ______________________________
echo "TEST\t3 KEYS\tcase sonet"
for key1 in -b -e -n -s -t
do
  for key2 in -b -e -n -s -t
  do
    for key3 in -b -e -n -s -t
    do
      if 
      [ $key1 != $key2 ] && [ $key2 != $key3 ] && [ $key1 != $key3 ]
      then
      test "$key1 $key2 $key3" "case sonet"
      # read pause
      fi
    done
  done
done

# echo ______________________________
# echo "TEST\t3 GNU KEYS\tcase sonet"
# for key1 in --number-nonblank -E --number  --squeeze-blank -T
# do  
#   for key2 in --number-nonblank -E --number  --squeeze-blank -T
#   do
#     for key3 in --number-nonblank -E --number  --squeeze-blank -T
#     do
#       if 
#       [ $key1 != $key2 ] && [ $key2 != $key3 ] && [ $key1 != $key3 ]
#       then
#       test "$key1 $key2 $key3" "case sonet"
#       # read pause
#       fi
#     done
#   done
# done  

# ========== * пять ключей * ==========
for file in "case" "sonet"
do
  echo ______________________________
  echo "TEST\t5 KEYS\t${file} "
  for key1 in -b -e -n -s -t
  do
    for key2 in -b -e -n -s -t
    do
      for key3 in -b -e -n -s -t
      do
        for key4 in -b -e -n -s -t
        do
          for key5 in -b -e -n -s -t
          do
            if 
            [ $key1 != $key2 ] && [ $key1 != $key3 ] && 
            [ $key1 != $key4 ] && [ $key1 != $key5 ] &&  
            [ $key2 != $key3 ] && [ $key2 != $key4 ] &&
            [ $key2 != $key5 ] && [ $key3 != $key4 ] &&
            [ $key3 != $key5 ] && [ $key4 != $key5 ]
            then
            test "$key1 $key2 $key3 $key4 $key5" $file
            # read pause
            fi
          done
        done
      done
    done
  done

  # echo ______________________________
  # echo "TEST\t5 GNU KEYS\t${file} "
  # for key1 in --number-nonblank -E --number  --squeeze-blank -T
  # do
  #   for key2 in --number-nonblank -E --number  --squeeze-blank -T
  #   do
  #     for key3 in --number-nonblank -E --number  --squeeze-blank -T
  #     do
  #       for key4 in --number-nonblank -E --number  --squeeze-blank -T
  #       do
  #         for key5 in --number-nonblank -E --number  --squeeze-blank -T
  #         do
  #           if 
  #           [ $key1 != $key2 ] && [ $key1 != $key3 ] && 
  #           [ $key1 != $key4 ] && [ $key1 != $key5 ] &&  
  #           [ $key2 != $key3 ] && [ $key2 != $key4 ] &&
  #           [ $key2 != $key5 ] && [ $key3 != $key4 ] &&
  #           [ $key3 != $key5 ] && [ $key4 != $key5 ]
  #           then
  #           test "$key1 $key2 $key3 $key4 $key5" $file
  #           # read pause
  #           fi
  #         done
  #       done
  #     done
  #   done
  # done
done

# ==== * пять ключей | два файла * ====
  echo ______________________________
  echo "TEST\t5 KEYS\tcase sonet"
  for key1 in -b -e -n -s -t
  do
    for key2 in -b -e -n -s -t
    do
      for key3 in -b -e -n -s -t
      do
        for key4 in -b -e -n -s -t
        do
          for key5 in -b -e -n -s -t
          do
            if 
            [ $key1 != $key2 ] && [ $key1 != $key3 ] && 
            [ $key1 != $key4 ] && [ $key1 != $key5 ] &&  
            [ $key2 != $key3 ] && [ $key2 != $key4 ] &&
            [ $key2 != $key5 ] && [ $key3 != $key4 ] &&
            [ $key3 != $key5 ] && [ $key4 != $key5 ]
            then
            test "$key1 $key2 $key3 $key4 $key5" "case sonet"
            # read pause
            fi
          done
        done
      done
    done
  done

  # echo ______________________________
  # echo "TEST\t5 GNU KEYS\tcase sonet"
  # for key1 in --number-nonblank -E --number  --squeeze-blank -T
  # do
  #   for key2 in --number-nonblank -E --number  --squeeze-blank -T
  #   do
  #     for key3 in --number-nonblank -E --number  --squeeze-blank -T
  #     do
  #       for key4 in --number-nonblank -E --number  --squeeze-blank -T
  #       do
  #         for key5 in --number-nonblank -E --number  --squeeze-blank -T
  #         do
  #           if 
  #           [ $key1 != $key2 ] && [ $key1 != $key3 ] && 
  #           [ $key1 != $key4 ] && [ $key1 != $key5 ] &&  
  #           [ $key2 != $key3 ] && [ $key2 != $key4 ] &&
  #           [ $key2 != $key5 ] && [ $key3 != $key4 ] &&
  #           [ $key3 != $key5 ] && [ $key4 != $key5 ]
  #           then
  #           test "$key1 $key2 $key3 $key4 $key5" "case sonet"
  #           # read pause
  #           fi
  #         done
  #       done
  #     done
  #   done
  # done

# ========= * И Т О Г О * =========
echo ${BOLD}______________________________
echo "TOTAL\t$(($SUCCES + $FAIL))"
if [ $FAIL -eq 0 ]
then
  echo "${GREEN}SUCC\t100 %\n"
else
  echo "${RED}FAIL\t$FAIL"
  echo "${GREEN}SUCC\t$SUCCES"
fi
