#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "grep.h"

int main(int argc, char *argv[]) {
  int flag = 0;

  if (argc < 3) {
    printf(
        "usage: s21_grep [-eivclnhsfo] [-A num] [-B num] [-C[num]]\n [-e "
        "pattern] [-f file]");
    flag = 1;
  }

  struct options opt = {0, NULL, 0,    0, 0, 0, 0,    0, 0,
                        0, 0,    NULL, 0, 0, 0, NULL, 0};

  //  аргументы -e
  opt.e_args = malloc((argc / 2 + 1) * sizeof(char *));
  if (opt.e_args == NULL) flag = 1;

  //  аргументы -f
  opt.f_args = malloc((argc / 2 + 1) * sizeof(char *));
  if (opt.f_args == NULL) flag = 1;

  //  паттерн (если есть) и файлы
  opt.forp = malloc(argc * sizeof(char *));  //  file or patterns
  if (opt.forp == NULL) flag = 1;

  if (!flag) {                //  флаг 1
    struct option aropt[11];  //  массив для гетопт_лонг
    filling(aropt);           //  заполняем его

    int ch = 0;       //  буфер для гетоптлонг
    int e_count = 0;  //  счетчик паттернов -е
    int f_count = 0;  //  счетчик паттерна и имен файлов
    int forp_count = 0;  //  счетчик паттернов и (или) имен файлов

    opterr = 0;  //  заглушка — блокировка сообщений от гетоптлонг

    //  '-' перед шортотпс позволит перехватить case: 1 —
    //  имена паттернов (e||f == 0) или файлов (e||f == 1)
    while (!flag &&
           (ch = getopt_long(argc, argv, "-e:ivclnhsf:o", aropt, NULL)) != -1) {
      switch (ch) {
        case 'e':
          opt.e = 1;
          opt.e_args[e_count++] = optarg;
          break;
        case 'i':
          opt.i = 1;
          break;
        case 'v':
          opt.v = 1;
          break;
        case 'c':
          opt.c = 1;
          break;
        case 'l':
          opt.l = 1;
          break;
        case 'n':
          opt.n = 1;
          break;
        case 'h':
          opt.h = 1;
          break;
        case 's':
          opt.s = 1;
          break;
        case 'f':
          opt.f = 1;
          opt.f_args[f_count++] = optarg;
          break;
        case 'o':
          opt.o = 1;
          break;
        case 1:  //  перехват паттернов и имен файлов
          opt.forp[forp_count++] = optarg;
          break;
        case '?':
          //  если не заглушен opterr, это все ↓ (кроме flag = 1) не нужно
          if (optopt == 'e') {
            printf("s21_grep: option requires an argument -- e");
          } else {
            if (optopt == 'f') {
              printf("s21_grep: option requires an argument -- f");
            } else {
              printf("s21_grep: invalid option -- %c", optopt);
            }
          }
          flag = 1;  //  чтобы не расписывал «инвалид опшнс» для каждой буквы!
          break;
        default:
          break;
      }
    }  //  конец свича и вайла

    //  конец аргументов, паттернов и имен файлов
    if (!(opt.e || opt.f) && forp_count > 1)  //  если -e или -f выключены
      opt.e_args[e_count++] =
          opt.forp[0];  //  сделаем единств. паттерн аргументом -e

    opt.e_args[e_count] = NULL;
    opt.e_args_num = e_count;  //  количество аргументов -e
    opt.f_args[f_count] = NULL;
    opt.f_args_num = f_count;  //  количество аргументов -f
    opt.forp[forp_count] = NULL;
    opt.forp_num = forp_count;  // количество файлов (м.б -1)

    //  отмены
    if (opt.v || opt.c || opt.l) opt.o = 0;
    if (opt.c) opt.n = 0;
    // if (opt.l) opt.c = 0;
  }  // конец флаг 1

  if (!flag && !opt.forp_num) {
    printf(
        "usage: s21_grep [-eivclnhsfo] [-A num] [-B num] [-C[num]]\n [-e "
        "pattern] [-f file]");
    flag = 1;
  }

  if (!flag && !(opt.e_args_num || opt.f_args_num)) {
    printf(
        "usage: s21_grep [-eivclnhsfo] [-A num] [-B num] [-C[num]]\n [-e "
        "pattern] [-f file]");
    flag = 1;
  }

  if (!flag) grep(&opt);  //  🚀 Поехали!

  if (opt.e_args != NULL) free(opt.e_args);
  if (opt.f_args != NULL) free(opt.f_args);
  if (opt.forp != NULL) free(opt.forp);

  return flag;
}
