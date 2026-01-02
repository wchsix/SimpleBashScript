CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

SRC = s21_cat.c

all: s21_cat

s21_cat: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f s21_cat

rebuild: clean all

format:
	clang-format -i $(SRC)