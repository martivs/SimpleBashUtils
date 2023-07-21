#include "cat.h"

#include <stdio.h>
#include <string.h>

//  вернет число групп опций (в т.ч. 0)
//  или -1, если обнаружил нелегальную опцию
int pars(int argc, char **argv, struct options *p_opt) {
  int count_hyph = 0;  //  счетчик строк с дефисом
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      count_hyph++;  //  группа опций ++
      if (pars_gnu(argv[i], p_opt)) {
        if (pars_mac(i, argv, p_opt)) {
          count_hyph = -1;  //  illegal options check
          i = argc;
        }
      }
    } else {
      i = argc;
    }
  }  //  стоп парсер при первом же отсутствии '-'

  //  -b отменяет -n
  if (p_opt->b == 1) p_opt->n = 0;

  return count_hyph;
}

int pars_gnu(char *str, struct options *p_opt) {
  int flag = 0;

  if (!strcmp(str, "--number-nonblank")) {
    p_opt->b = 1;
  } else {
    if (!strcmp(str, "-E")) {
      p_opt->e = 1;
    } else {
      if (!strcmp(str, "--number")) {
        p_opt->n = 1;
      } else {
        if (!strcmp(str, "--squeeze-blank")) {
          p_opt->s = 1;
        } else {
          if (!strcmp(str, "-T")) {
            p_opt->t = 1;
          } else {
            flag = 1;
          }
        }
      }
    }
  }

  return flag;
}

int pars_mac(int i, char **argv, struct options *p_opt) {
  int flag = 0;

  for (size_t j = 1; j < strlen(argv[i]); j++) {
    switch (argv[i][j]) {
      case 'b':
        p_opt->b = 1;
        break;
      case 'e':
        p_opt->e = 1;
        p_opt->v = 1;  //  -e предполагает и -v
        p_opt->z = 1;
        break;
      case 'n':
        p_opt->n = 1;
        break;
      case 's':
        p_opt->s = 1;
        break;
      case 't':
        p_opt->t = 1;
        p_opt->v = 1;  //  -t предполагает и -v
        p_opt->z = 1;
        break;
      default:
        printf("s21_cat: illegal option -- %c\n", argv[i][j]);
        printf("usage: s21_cat [-benst] [file ...]\n");
        j = strlen(argv[i]);  //  перестаем перебирать
        flag = 1;
    }
  }

  return flag;
}

int cat(char *file_name, struct options *p_opt) {
  int flag = 0;

  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    printf("s21_cat: %s: No such file\n", file_name);
    flag = 1;
  }

  if (!flag) {
    char buf;      //  буфер для считываемого символа
    int line = 1;  //  счетчик строк
    int flag_new_line = 1;  //  флаг перехода через '\n' (>2 если пустые подряд)
    while ((buf = fgetc(file)) != EOF) {
      //  -s
      if ((buf == '\n') && (flag_new_line > 1) && p_opt->s) continue;

      //  -n
      if (flag_new_line && p_opt->n) {
        printf("%6d\t", line++);
      }

      //  -b
      if ((flag_new_line) && (buf != '\n') && p_opt->b) {
        printf("%6d\t", line++);
      }

      //  -e, -t, -v
      if ((buf == '\n') && (p_opt->e)) {
        printf("%c%c", '$', '\n');
      } else {
        if ((buf == '\t') && (p_opt->t)) {
          printf("%c%c", '^', 'I');
        } else {
          if (((buf < 9) || (buf > 10)) && (buf < 32) && p_opt->v) {
            printf("%c%c", '^', buf + 64);
          } else {
            if ((buf == 127) && p_opt->z) {
              printf("%c%c", '^', '?');
            } else {
              putchar(buf);
            }
          }
        }
      }

      if (buf == '\n')
        flag_new_line++;
      else
        flag_new_line = 0;
    }
  }

  if (file != NULL) fclose(file);

  return flag;
}
