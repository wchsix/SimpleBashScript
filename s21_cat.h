#ifndef S21_CAT_H
#define S21_CAT_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <getopt.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int T;
  int E;
} Flags;
void parser(int argc, char *argv[], Flags *flags);
void files_index(int argc, char *argv[], Flags *flags);
void print_file(char *filename, Flags *flags);
void process_file_with_flags(FILE *file, Flags flags);
void process_files_with_flags_s(int *empty_line_count, int *skip);
static struct option longopt[] = {{"number-nonblank", 0, 0, 'b'},
                                  {"number", 0, 0, 'n'},
                                  {"squeeze-blank", 0, 0, 's'},
                                  {0, 0, 0, 0}};
#endif 