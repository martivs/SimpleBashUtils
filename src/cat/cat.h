#ifndef SRC_CAT_CAT_H_
#define SRC_CAT_CAT_H_

struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int z;
};

int pars(int argc, char **argv, struct options *p_opt);
int pars_gnu(char *str, struct options *p_opt);
int pars_mac(int i, char **argv, struct options *p_opt);

int cat(char *file_name, struct options *p_opt);

#endif  //  SRC_CAT_CAT_H_

/*  ======= * Т Р А Б Л Ы * =======

    cat [OPTION] [FILE]...

    s21_cat (без аргументов)                            CHECK!
    s21_cat -b -e -t (без файлов)                       CHECK

    s21_cat * (все файлы)                               CHECK!
    s21_cat *.xxx (все файлы .xxx)                      CHECK!
    s21_cat *.* (все файлы .xxx)                        CHECK!
    s21_cat xxx.* (все файлы .xxx)                      CHECK!

    s21_cat -test (имя файла с дефисом)                 CHECK!
    s21_cat -stest (без пробела)                        CHECK!
    s21_cat -b-s test (без пробела между опциями)       CHECK!
    s21_cat Test (если есть директория, а файла нет)

*/
