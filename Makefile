CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

SRC = s21_grep.c

all: s21_grep

s21_cat: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f s21_grep

rebuild: clean all

format:
	clang-format -i $(SRC)