#!/bin/bash

S21_GREP=./s21_grep
ORIG_GREP=grep

TEST_DIR=tests
TMP1=tmp_s21.txt
TMP2=tmp_orig.txt

# Шаблоны для поиска
PATTERNS=(
  "int"
  "return"
  "char"
  "INT"
  "king"
)

# Флаги для теста
FLAGS=(
  ""
  "-e"
  "-i"
  "-v"
  "-c"
  "-l"
  "-n"
)

# Тестовые файлы
FILES=(
  "$TEST_DIR/test_0_grep.txt"
  "$TEST_DIR/test_1_grep.txt"
  "$TEST_DIR/test_2_grep.txt"
  "$TEST_DIR/test_3_grep.txt"
  "$TEST_DIR/test_4_grep.txt"
  "$TEST_DIR/test_5_grep.txt"
  "$TEST_DIR/test_6_grep.txt"

)

PASSED=0
FAILED=0

echo "===== s21_grep integration tests ====="

for pattern in "${PATTERNS[@]}"; do
  for flag in "${FLAGS[@]}"; do
    for file in "${FILES[@]}"; do


      $S21_GREP $flag "$pattern" "$file" > $TMP1 2>/dev/null

      $ORIG_GREP $flag "$pattern" "$file" > $TMP2 2>/dev/null

      if diff -u $TMP1 $TMP2 > /dev/null; then
        echo "SUCCES: $flag '$pattern' $file"
        ((PASSED++))
      else
        echo "FAIL: $flag '$pattern' $file"
        ((FAILED++))
      fi

    done
  done
done

rm -f $TMP1 $TMP2

echo "====================================="
echo "PASSED: $PASSED"
echo "FAILED: $FAILED"

if [ $FAILED -eq 0 ]; then
  exit 0
else
  exit 1
fi