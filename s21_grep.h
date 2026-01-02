#ifndef S21_GREP_H
#define S21_GREP_H
#define _POSIX_C_SOURCE 200809L
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  char *pattern;
} Flags;
void parser(int argc, char *argv[], Flags *flags);
void file_index(int argc, char *argv[], Flags *flags);
void print_file(char *filename, Flags *flags);
int reg_comp(regex_t *reg, const char *pattern, Flags *flags);
void process_file_with_flags(FILE *file, Flags flags, char *filename);
int reg_exec(regex_t *reg, char *line);
int memory_pattern(int argc, char *argv[], Flags *flags);
#endif 