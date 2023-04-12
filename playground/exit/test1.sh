#!/bin/bash

# テストケース
declare -a testcases=(
  "1"
  "2"
  "255"
)

for arg in "${testcases[@]}"; do
  ./a.out $arg
  ret=$?
  if [ "$arg" = "exit" ]; then
    real=$ret
  else
    real=$arg
  fi
    echo ""
    echo "testcase: \"$arg\""
  if [ $ret -eq $real ]; then
    echo -e "\033[32mTest case: Exit status should be $real: $ret (OK)\033[0m"
  else
    echo -e "\033[31mTest case: Exit status should be $real: $ret (NG)\033[0m"
  fi

done