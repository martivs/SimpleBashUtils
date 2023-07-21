#ifndef SRC_GREP_GREP_H_
#define SRC_GREP_GREP_H_
#include <getopt.h>
#include <stdlib.h>

#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L

struct options {
  int e;
  char **e_args;  //  аргументы -e
  int e_args_num;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  char **f_args;  //  аргументы -f
  int f_args_num;
  int f_arg_void;
  int o;

  char **forp;  //  паттерн (ЕЕ) и файлы
  int forp_num;
};

struct lines {
  int flag_file;
  int count_check;
  char *file_name;
  int num_line;
  char *line;
  size_t len;
  unsigned long offset;
};

void filling(struct option *aropt);

void grep(struct options *p_opt);

void run_by_files(struct lines *p_line, struct options *p_opt, int f_count);

void reg(struct lines *line, char *pattern, struct options *p_opt);

void print(struct lines *p_line, struct options *p_opt);

void print_c(int count_line, int count_v_line, char *file_name,
             struct options *p_opt);

void print_o(struct lines *p_line, int offset, int d, struct options *p_opt);

void free_line(struct lines *p_line);

int check_forp(struct options *p_opt);

#endif  //  SRC_GREP_GREP_H_
