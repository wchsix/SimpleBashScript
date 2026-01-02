#include "s21_grep.h"
int main(int argc, char* argv[]) {
  Flags flags = {0};
  int status = 0;
  flags.pattern = NULL;
  parser(argc, argv, &flags);
  if (!flags.pattern) {
    status = memory_pattern(argc, argv, &flags);
  }
  if (status == 0 && flags.pattern != NULL) {
    file_index(argc, argv, &flags);
  }
  if (flags.pattern) {
    free(flags.pattern);
  }

  return status;
}

void parser(int argc, char* argv[], Flags* flags) {
  int opt;
  while ((opt = getopt(argc, argv, "e:ivcln")) != -1) {
    switch (opt) {
      case 'e':
        flags->e = 1;
        if (flags->pattern != NULL) {
          free(flags->pattern);
        }
        flags->pattern = malloc(strlen(optarg) + 1);
        if (flags->pattern != NULL) {
          strcpy(flags->pattern, optarg);
        } else
          fprintf(stderr, "error\n");
        break;
      case 'i':
        flags->i = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'c':
        flags->c = 1;
        break;
      case 'l':
        flags->l = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      default:
        fprintf(stderr, "error\n");
        exit(1);
        break;
    }
  }
}

int memory_pattern(int argc, char* argv[], Flags* flags) {
  int status = 0;
  if (optind < argc) {
    flags->pattern = malloc(strlen(argv[optind]) + 1);
    if (flags->pattern != NULL) {
      strcpy(flags->pattern, argv[optind]);
      optind++;
    } else {
      fprintf(stderr, "error\n");
      status = 1;
    }
  } else {
    fprintf(stderr, "error\n");
    status = 1;
  }
  return status;
}

void file_index(int argc, char* argv[], Flags* flags) {
  for (int i = optind; i < argc; i++) {
    if (argv[i][0] != '-') {
      print_file(argv[i], flags);
    }
  }
}
void print_file(char* filename, Flags* flags) {
  FILE* file = fopen(filename, "r");
  int flag = 1;

  if (!file) {
    fprintf(stderr, "error %s\n", filename);
    flag = 0;
  }

  if (flag) {
    process_file_with_flags(file, *flags, filename);
    fclose(file);
  }
}
void process_file_with_flags(FILE* file, Flags flags, char* filename) {
  regex_t reg;
  int line_number = 0;
  int match_count = 0;
  int file_has_match = 0;
  int error = reg_comp(&reg, flags.pattern, &flags);
  if (!error) {
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, file)) != -1) {
      line_number++;
      int res = reg_exec(&reg, line);
      if (flags.v) {
        res = !res;
      }
      if (res) {
        match_count++;
        file_has_match = 1;
        if (!flags.c && !flags.l) {
          if (flags.n) {
            printf("%d:%s", line_number, line);
          } else {
            printf("%s", line);
          }
        }
      }
    }
    if (flags.c) {
      printf("%d\n", match_count);
    }
    if (flags.l && file_has_match) {
      printf("%s\n", filename);
    }
    free(line);
    regfree(&reg);
  }
}
int reg_comp(regex_t* reg, const char* pattern, Flags* flags) {
  int error;
  if (flags->i) {
    error = regcomp(reg, pattern, REG_EXTENDED | REG_ICASE);
  } else {
    error = regcomp(reg, pattern, REG_EXTENDED);
  }
  if (error != 0) {
    fprintf(stderr, "!error\n");
  }
  return error;
}

int reg_exec(regex_t* reg, char* line) {
  int res = regexec(reg, line, 0, NULL, 0);
  int match = 0;
  if (res == 0) {
    match = 1;
  }

  return match;
}