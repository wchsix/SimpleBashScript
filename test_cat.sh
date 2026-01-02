#!/bin/bash

S21_CAT=./s21_cat
ORIG_CAT=cat

TEST_DIR=tests
TMP1=tmp_s21.txt
TMP2=tmp_orig.txt

FLAGS=(
  ""
  "-b"
  "-n"
  "-s"
  "-e"
  "-t"
  "-v"
  "-bn"
  "-nb"
  "-be"
  "-et"
  "-stv"
)

FILES=(
  "$TEST_DIR/test_1_cat.txt"
  "$TEST_DIR/test_2_cat.txt"
  "$TEST_DIR/test_3_cat.txt"
  "$TEST_DIR/test_4_cat.txt"
)

PASSED=0
FAILED=0

echo "===== s21_cat integration tests ====="

for flag in "${FLAGS[@]}"; do
  for file in "${FILES[@]}"; do

    $S21_CAT $flag "$file" > $TMP1
    $ORIG_CAT $flag "$file" > $TMP2

    if diff $TMP1 $TMP2 > /dev/null; then
      echo "SUCCES: $flag $file"
      ((PASSED++))
    else
      echo "FAIL: $flag $file"
      ((FAILED++))
    fi

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
