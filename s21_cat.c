#include "s21_cat.h"
int main(int argc, char* argv[]) {
  Flags flags = {0};
  parser(argc, argv, &flags);
  files_index(argc, argv, &flags);
  return 0;
}

void parser(int argc, char* argv[], Flags* flags) {
  int opt;

  while ((opt = getopt_long(argc, argv, "+benstvTE", longopt, NULL)) != -1) {
    switch (opt) {
      case 'b':
        flags->b = 1;
        break;
      case 'e':
        flags->e = 1;
        flags->v = 1;
        break;
      case 'E':
        flags->E = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 't':
        flags->t = 1;
        flags->v = 1;
        break;
      case 'T':
        flags->T = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      default:
        fprintf(stderr, "error\n");
        break;
    }
  }
}

void files_index(int argc, char* argv[], Flags* flags) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      continue;
    }
    print_file(argv[i], flags);
  }
}

void print_file(char* filename, Flags* flags) {
  int flag = 1;
  FILE* file = fopen(filename, "r");

  if (!file) {
    fprintf(stderr, "Error: cannot open file %s\n", filename);
    flag = 0;
  }

  if (flag) {
    process_file_with_flags(file, *flags);
    fclose(file);
  }
}
void process_files_with_flags_s(int* empty_line_count, int* skip) {
  (*empty_line_count)++;
  if (*empty_line_count > 2) {
    *skip = 1;
  }
}
void process_file_with_flags(FILE* file, Flags flags) {
  int c;
  int line_number = 1;
  int line_start = 1;
  int empty_line_count = 0;
  while ((c = fgetc(file)) != EOF) {
    int print = 0;
    int skip = 0;
    if (flags.s && c == '\n') {
      process_files_with_flags_s(&empty_line_count, &skip);
    } else {
      empty_line_count = 0;
    }
    if (!skip) {
      if (line_start) {
        if (flags.b && c != '\n') {
          printf("%6d\t", line_number++);
        }
        if (flags.b && c == '\n' && (flags.e || flags.E)) {
          printf("%6s\t", "");
        }
        if (flags.n && !flags.b) {
          printf("%6d\t", line_number++);
        }
        line_start = 0;
      }
      if (flags.v && ((c < 32 && c != '\n' && c != '\t') || c == 127)) {
        if (c == 127)
          printf("^?");
        else
          printf("^%c", c + 64);
        print = 1;
      }
      if ((flags.t || flags.T) && c == '\t') {
        printf("^I");
        print = 1;
      }
      if (c == '\n') {
        if (flags.e || flags.E) printf("$");
        printf("\n");
        line_start = 1;
        print = 1;
      }

      if (!print) printf("%c", c);
    }
  }
}
