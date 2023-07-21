#include <stdio.h>
#include <stdlib.h>

#include "cat.h"

int main(int argc, char *argv[]) {
  int flag = 0;

  //  stdin
  if (argc < 2) {
    printf("«Ввод через stdin обрабатывать не обязательно».\n");
    printf("Simple Bash Utils. Chapter III. P. 13. :P");
    flag = 1;
  }

  struct options opt = {0, 0, 0, 0, 0, 0, 0};
  int count_hyp = 0;  //  счетчик дефисов

  if (!flag && (argc > 1)) {
    count_hyp = pars(argc, argv, &opt);
  }

  //  stdin
  if (!flag && (count_hyp == argc - 1)) {
    printf("«Ввод через stdin обрабатывать не обязательно».\n");
    printf("Simple Bash Utils. Chapter III. P. 13. :P");
    flag = 1;
  }

  if (count_hyp >= 0) {
    for (int i = ++count_hyp; i < argc; i++) {
      cat(argv[i], &opt);
    }
  }

  return flag;
}
