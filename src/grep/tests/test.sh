#!/bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
BOLD="\033[1m"

SUCCES=0
FAIL=0
TOTAL=0

test () {
  ./s21_grep $1 $2 $3 > temp_1
  grep $1 $2 $3 > temp_2

  if cmp temp_1 temp_2
  then
    echo "${GREEN}SUCC\t./s21_grep $1 $2 $3"
    SUCCES=$(($SUCCES + 1))  
  else
    echo "${RED}FAIL\t./s21_grep $1 $2 $3"
    FAIL=$(($FAIL + 1))   
  fi

  tput sgr0
}

# 1 ∃ паттерн, 1 файл, 0 ключей
echo ______________________________
echo "TEST1\tWITHOUT KEYS\t∃"
test "th" "sonet"

# 1 ∃ паттерн, 2 файла, 0 ключей
echo ______________________________
echo "test\tWITHOUT KEYS\t∃"
test "th" "sonet" "sonet2"

# 1 ∄ паттерн, 1 файл, 0 ключей
echo ______________________________
echo "TEST3\tWITHOUT KEYS\t∄"
test "zz" "sonet"

# 1 ∄ паттерн, 2 файл, 0 ключей
echo ______________________________
echo "TEST4\tWITHOUT KEYS\t∄"
test "zz" "sonet" "sonet2"

# 1 ∃ паттерн, 1 файл, 1 ключ
echo ______________________________
echo "TEST5\t1 KEY\t∃"
for key in -i -v -c -l -n -h -s -o
do
test "th sonet" "$key"
# read pause
done

# 1 ∃ паттерн, 2 файла, 1 ключ
echo ______________________________
echo "TEST6\t1 KEY\t∃"
for key in -i -v -c -l -n -h -s -o
do
test "th" "sonet sonet2" "$key"
# read pause
done

# 1 ∄ паттерн, 1 файл, 1 ключ
echo ______________________________
echo "TEST7\t1 KEY\t∄"
for key in -i -v -c -l -n -h -s -o
do
test "zz sonet" "$key"
# read pause
done

# 1 ∄ паттерн, 2 файла, 1 ключ
echo ______________________________
echo "TEST8\t1 KEY\t∄"
for key in -i -v -c -l -n -h -s -o
do
test "zz" "sonet sonet2" "$key"
# read pause
done

# 1 ∃ паттерн, 1 файл, 2 ключа
echo ______________________________
echo "TEST9\t2 KEYS\t ∃"
for key1 in -i -v -c -l -n -h -s -o
do
  for key2 in -i -v -c -l -n -h -s -o
  do
    if 
    [ $key1 != $key2 ] 
    then  
    test "th sonet" $key1 $key2
    # read pause
    fi
  done
done


# 1 ∄ паттерн, 1 файл, 2 ключа
echo ______________________________
echo "TEST10\t2 KEYS\t ∄"
for key1 in -i -v -c -l -n -h -s -o
do
  for key2 in -i -v -c -l -n -h -s -o
  do
    if 
    [ $key1 != $key2 ] 
    then  
    test "zz sonet" $key1 $key2
    # read pause
    fi
  done
done

# 1 ∃ паттерн, 2 файла, 2 ключа
echo ______________________________
echo "TEST11\t2 KEYS\t2 FILES\t∃"
for key1 in -i -v -c -l -n -h -s -o
do
  for key2 in -i -v -c -l -n -h -s -o
  do
    if 
    [ $key1 != $key2 ] 
    then  
    test "th sonet sonet2" $key1 $key2
    # read pause
    fi
  done
done

# 1 ∄ паттерн, 2 файла, 2 ключа
echo ______________________________
echo "TEST12\t2 KEYS\t2 FILES\t∄"
for key1 in -i -v -c -l -n -h -s -o
do
  for key2 in -i -v -c -l -n -h -s -o
  do
    if 
    [ $key1 != $key2 ] 
    then  
    test "zz sonet sonet2" $key1 $key2
    # read pause
    fi
  done
done

# 2 ∃ паттерн, 2 файла, 2 ключа
echo ______________________________
echo "TEST13\t2 PATTERNS\t2 FILES\t∃"
for key1 in -i -v -c -l -n -h -s -o
do
  for key2 in -i -v -c -l -n -h -s -o
  do
    if 
    [ $key1 != $key2 ] 
    then  
    test "-e ^int -e ss sonet patterns" $key1 $key2
    # read pause
    fi
  done
done

# 2 ∃ паттерн, 2 файла, 2 ключа
echo ______________________________
echo "TEST13A\t2 PATTERNS\t2 FILES\t∄∃"
for key1 in -i -v -c -l -n -h -s -o
do
  for key2 in -i -v -c -l -n -h -s -o
  do
    if 
    [ $key1 != $key2 ] 
    then  
    test "-e zz -e ss sonet patterns" $key1 $key2
    # read pause
    fi
  done
done

# 2 ∃ паттерн, 2 файла, 2 ключа
echo ______________________________
echo "TEST13B\t2 PATTERNS\t2 FILES\t∃∄"
for key1 in -i -v -c -l -n -h -s -o
do
  for key2 in -i -v -c -l -n -h -s -o
  do
    if 
    [ $key1 != $key2 ] 
    then  
    test "-e th -e zz sonet patterns" $key1 $key2
    # read pause
    fi
  done
done

# 2 ∃ паттерн, 2 файла, 2 ключа
echo ______________________________
echo "TEST13C\t2 PATTERNS\t2 FILES\t∄∄"
for key1 in -i -v -c -l -n -h -s -o
do
  for key2 in -i -v -c -l -n -h -s -o
  do
    if 
    [ $key1 != $key2 ] 
    then  
    test "-e yy -e zz sonet patterns" $key1 $key2
    # read pause
    fi
  done
done

# 1 ∃ ф-паттерн, 1 файл, 0 ключей
echo ______________________________
echo "TEST14\tWITHOUT KEYS\t FROM FILE"
test "sonet" "-f" "patterns"

# 1 ∃ ф-паттерн, 1 файл, 1 ключ
echo ______________________________
echo "TEST15\t1 KEY\tFROM FILE"
for key in -i -v -c -l -n -h -s -o
do
test "sonet" "-f patterns" "$key"
# read pause
done

# 1 ∃ ф-паттерн, 1 файл, 1 ключ
echo ______________________________
echo "TEST16\t2 KEY\tFROM FILE"
for key1 in -i -v -c -l -n -h -s -o
do
  for key2 in -i -v -c -l -n -h -s -o
  do
    if [ $key1 != $key2 ] 
    then
    test "sonet" "-f patterns" "$key1 $key2"
    # read pause
    fi
  done
done

# 1 ∃ ф-паттерн, 2 файл, 1 ключ
echo ______________________________
echo "TEST17\t1 KEY\tFROM FILE"
for key in -i -v -c -l -n -h -s -o
do
test "sonet" "-f patterns -f patterns2" "$key"
# read pause
done

# 1 2 файла, 2 ключа
echo ______________________________
echo "TEST18\t2 KEY\tFROM FILE"
for key1 in -i -v -c -l -n -h -s -o
do
  for key2 in -i -v -c -l -n -h -s -o
  do
    if [ $key1 != $key2 ] 
    then
    test "sonet" "-f patterns -f patterns2" "$key1 $key2"
    # read pause
    fi
  done
done

# 1 2 файл, 1 ключ
echo ______________________________
echo "TEST19\t1 KEY\tFROM FILE"
for key in -i -v -c -l -n -h -s -o
do
test "sonet sonet2" "-f patterns -f patterns2" "$key"
# read pause
done

# 1 2 файла, 2 ключа
echo ______________________________
echo "TEST20\t2 KEY\tFROM FILE"
for key1 in -i -v -c -l -n -h -s -o
do
  for key2 in -i -v -c -l -n -h -s -o
  do
    if [ $key1 != $key2 ] 
    then
    test "sonet sonet2" "-f patterns -f patterns2" "$key1 $key2"
    # read pause
    fi
  done
done

rm temp_1 temp_2

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
