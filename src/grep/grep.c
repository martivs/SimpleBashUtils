#include "grep.h"

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void filling(struct option *aropt) {
  aropt[0].name = "regexp";
  aropt[0].has_arg = required_argument;
  aropt[0].flag = NULL;
  aropt[0].val = 'e';

  aropt[1].name = "ignore-case";
  aropt[1].has_arg = no_argument;
  aropt[1].flag = NULL;
  aropt[1].val = 'i';

  aropt[2].name = "invert-match";
  aropt[2].has_arg = no_argument;
  aropt[2].flag = NULL;
  aropt[2].val = 'v';

  aropt[3].name = "count";
  aropt[3].has_arg = no_argument;
  aropt[3].flag = NULL;
  aropt[3].val = 'c';

  aropt[4].name = "files-with-matches";
  aropt[4].has_arg = no_argument;
  aropt[4].flag = NULL;
  aropt[4].val = 'l';

  aropt[5].name = "line-number";
  aropt[5].has_arg = no_argument;
  aropt[5].flag = NULL;
  aropt[5].val = 'n';

  aropt[6].name = "no-filename";
  aropt[6].has_arg = no_argument;
  aropt[6].flag = NULL;
  aropt[6].val = 'h';

  aropt[7].name = "no-messages";
  aropt[7].has_arg = no_argument;
  aropt[7].flag = NULL;
  aropt[7].val = 's';

  aropt[8].name = "file";
  aropt[8].has_arg = required_argument;
  aropt[8].flag = NULL;
  aropt[8].val = 'f';

  aropt[9].name = "only-matching";
  aropt[9].has_arg = no_argument;
  aropt[9].flag = NULL;
  aropt[9].val = 'o';

  aropt[10].name = NULL;
  aropt[10].has_arg = 0;
  aropt[10].flag = NULL;
  aropt[10].val = 0;
}

void grep(struct options *p_opt) {
  int forp_count = 0;  //  cчетчик для пробега по форп
  if (!(p_opt->e ||
        p_opt->f))  // если -e и -f выключены, первый аргумент — паттерн
    forp_count++;   //  он у нас уже в e_args

  //  идем по файлам, в которых ищем
  for (; p_opt->forp[forp_count] != NULL; forp_count++) {
    int flag_file = 0;  //  поднимем, если не откроется
    FILE *file = fopen(p_opt->forp[forp_count], "r");

    if (file == NULL) {
      flag_file = 1;
      if (!p_opt->s) {
        printf("s21_grep: %s: No such file\n", p_opt->forp[forp_count]);
      }
    }

    if (!flag_file) {
      //  структура с инфой о строке и переменными для гетлайна
      struct lines line = {0, 0, p_opt->forp[forp_count], 0, NULL, 0, 0};
      //  общее количество совп. строк в файле
      int count_line = 0;
      int count_v_line = 0;
      int flag_file_void = 0;
      //  идем по строчкам файла (записываем в line)
      while (getline(&line.line, &line.len, file) != -1) {
        flag_file_void++;
        line.num_line++;
        //  идем по e_args
        for (int e_count = 0; p_opt->e_args[e_count] != NULL; e_count++) {
          reg(&line, p_opt->e_args[e_count], p_opt);
          /* line.offset = 0; */ } // подстройка под кривой греп на маке!
          //  идем по f_args
          for (int f_count = 0; p_opt->f_args[f_count] != NULL; f_count++) {
            run_by_files(&line, p_opt, f_count);
          /*line.offset = 0; */ } // подстройка под кривой греп на маке!

          //  если есть матчи в строке
          if (line.count_check > 0) {
            count_line++;
          } else {
            count_v_line++;
          }

          //  если нет матчей и -v
          if (p_opt->v && !p_opt->c && !p_opt->l && !line.count_check)
            print(&line, p_opt);

          //  если есть матчи и -l, -с, -v и -o выключены
          if (!(p_opt->c || p_opt->l || p_opt->o || p_opt->v) &&
              line.count_check)
            print(&line, p_opt);

          free_line(&line);
      }  //  конец вайла по строке

      free(line.line);

      //  вывод только количества строк -c
      if (p_opt->c)
        print_c(count_line, count_v_line, p_opt->forp[forp_count], p_opt);

      //  вывод только совп. файлов -l
      if (p_opt->l && flag_file_void) {
        if (count_line && !p_opt->v) {
          printf("%s\n", p_opt->forp[forp_count]);
        } else {
          if (count_v_line && p_opt->v) {
            printf("%s\n", p_opt->forp[forp_count]);
          }
        }
      }
    }

    if (file != NULL) fclose(file);
  }
}

//  ищет pattern в str
void reg(struct lines *p_line, char *pattern, struct options *p_opt) {
  regex_t preg;  //  cкомпилированное расширенное регулярное выражение
  int regcomp_code;  //  код от regcomp

  if (p_opt->i) {  //  регистр имеет значение
    regcomp_code =
        regcomp(&preg, pattern, REG_ICASE | REG_EXTENDED | REG_NEWLINE);
  } else {
    regcomp_code = regcomp(&preg, pattern, REG_EXTENDED | REG_NEWLINE);
  }

  if (regcomp_code) {
    printf("regcomp: Something wrong ¯\\_(ツ)_/¯\n");
  } else {
    regmatch_t pmatch;
    int flag_reg = 0;
    // unsigned long offset = 0;  //  смещение по строке (жадный алгоритм)
    while (!flag_reg) {
      if (!regexec(&preg, p_line->line + p_line->offset, 1, &pmatch,
                   0 /*REG_NOTEOL*/)) {
        p_line->count_check++;  //  число совпадений в строке ++
        p_line->offset += pmatch.rm_eo;  //  едем дальше по строке

        if (p_opt->o && !p_opt->v)  //  вывлдим матчи, если -о включена
          print_o(p_line, p_line->offset, (int)(pmatch.rm_eo - pmatch.rm_so),
                  p_opt);

        if (p_opt->forp_num > 1)  //  для -o когда > 1 файла
          p_line->flag_file = 1;  //  (этот файл уже выведен)
      } else {
        flag_reg = 1;
      }
    }
  }  //  stop while

  if (!regcomp_code) regfree(&preg);
}

void run_by_files(struct lines *p_line, struct options *p_opt, int f_count) {
  static int fail = -1;  //  не открывать ∄ файл много раз
  int flag_file = 0;     //  поднимем, если не откроется

  FILE *file = NULL;

  if (fail != f_count) {
    file = fopen(p_opt->f_args[f_count], "r");
    if (file == NULL) {
      fail = f_count;
      flag_file = 1;
      if (!p_opt->s) {
        printf("s21_grep: %s: No such file\n", p_opt->f_args[f_count]);
      }
    }
  }

  if (!flag_file && (fail != f_count)) {
    char *f_line = NULL;
    size_t f_line_len = 0;
    //  идет по паттернам из файла (записывает в f_line)
    while (getline(&f_line, &f_line_len, file) != -1) {
      // грохнет '\n' в конце строки
      if (f_line[0] != '\n') {
        for (int i = 0; f_line[i] != '\0'; i++) {
          if (f_line[i] == '\n') {
            f_line[i] = '\0';
          }
        }
      } else {
        p_opt->f_arg_void = 1;
      }
      reg(p_line, f_line, p_opt);

      free(f_line);
      f_line = NULL;
    }
    free(f_line);
  }

  if (file != NULL) fclose(file);
}

//  печатает строку из файла
void print(struct lines *p_line, struct options *p_opt) {
  if (!p_opt->h && check_forp(p_opt)) printf("%s:", p_line->file_name);

  if (p_opt->n) printf("%d:", p_line->num_line);

  printf("%s", p_line->line);

  if (p_line->line[strlen(p_line->line) - 1] != '\n') printf("%c", '\n');
}

//  печатает только совпадающие части совпавшей строки
void print_o(struct lines *p_line, int offset, int d, struct options *p_opt) {
  if (!p_opt->f_arg_void) {
    //  если первое совпадение в этом файле
    //  и условие – лдин ли файл, в котором ищием
    if (!p_line->flag_file && !p_opt->h && check_forp(p_opt))
      printf("%s:", p_line->file_name);

    //  номер строки, если нужен
    if (p_opt->n && (p_line->count_check == 1)) printf("%d:", p_line->num_line);

    //  вывод совпадения
    for (int i = offset - d; i < (offset); i++) {
      printf("%c", p_line->line[i]);
      if (i == (offset - 1)) {
        printf("\n");
      }
    }
  } else {
    print(p_line, p_opt);
  }
}

//  печатает только количество строк
void print_c(int count_line, int count_v_line, char *file_name,
             struct options *p_opt) {
  if (!check_forp(p_opt)) {  //  ищем в одном файле
    if (count_line) {        // есть совпадения
      if (!p_opt->v) {
        if (!p_opt->l) {
          printf("%d\n", count_line);
        } else {
          printf("%d\n", 1);
        }
      }
      if (p_opt->v) {
        if (!p_opt->l) {
          printf("%d\n", count_v_line);
        } else {
          printf("%d\n", 1);
        }
      }
    }
    if (!count_line) {  //  нет совпадений
      if (!p_opt->v) {
        printf("%d\n", 0);
      }
      if (p_opt->v) {
        if (!p_opt->l) {
          printf("%d\n", count_v_line);
        } else {
          printf("%d\n", 1);
        }
      }
    }
  }

  if (check_forp(p_opt)) {  // ищем > чем в одном файле
    if (count_line) {
      if (!p_opt->v) {
        if (!p_opt->h) {
          printf("%s:", file_name);
        }
        if (!p_opt->l) {
          printf("%d\n", count_line);
        } else {
          printf("%d\n", 1);
        }
      }
      if (p_opt->v) {
        if (!p_opt->h) {
          printf("%s:", file_name);
        }
        if (!p_opt->l) {
          printf("%d\n", count_v_line);
        } else {
          printf("%d\n", 1);
        }
      }
    }

    if (!count_line) {  //  нет совпадений
      if (!p_opt->v) {
        if (!p_opt->h) {
          printf("%s:", file_name);
        }
        printf("%d\n", count_line);
      }
      if (p_opt->v) {
        if (!p_opt->h) {
          printf("%s:", file_name);
        }
        printf("%d\n", count_v_line);
      }
    }
  }
}

//  чистит структуру с инофй о строке
void free_line(struct lines *p_line) {
  p_line->count_check = 0;
  p_line->flag_file = 0;
  free(p_line->line);
  p_line->line = NULL;
  p_line->len = 0;
  p_line->offset = 0;
}

// файлов в которых ищем больше одного?
int check_forp(struct options *p_opt) {
  return (!(p_opt->e || p_opt->f) && (p_opt->forp_num > 2)) ||
         ((p_opt->e || p_opt->f) && (p_opt->forp_num > 1));
}
