: '
このテストケースの試し方。
1.同じ階層に、test1.sh と a.out を配置する
2. ./tes.sh を実行する
'

# テストケース
arg=1
answer=1
./a.out $arg
ret=$?
if [ $ret -eq $answer ]; then
  echo "\033[32mTest case $arg: Exit status should be $answer: $ret (OK)\033[0m"
else
  echo "\033[31mTest case $arg: Exit status should be $answer: $ret (NG)\033[0m"
fi

arg=-1
answer=255
./a.out $arg
ret=$?
if [ $ret -eq $answer ]; then
  echo "\033[32mTest case $arg: Exit status should be $answer: $ret (OK)\033[0m"
else
  echo "\033[31mTest case $arg: Exit status should be $answer: $ret (NG)\033[0m"
fi

arg=-1
answer=255
./a.out $arg
ret=$?
if [ $ret -eq $answer ]; then
  echo "\033[32mTest case $arg: Exit status should be $answer: $ret (OK)\033[0m"
else
  echo "\033[31mTest case $arg: Exit status should be $answer: $ret (NG)\033[0m"
fi

arg=256
answer=0
./a.out $arg
ret=$?
if [ $ret -eq $answer ]; then
  echo "\033[32mTest case $arg: Exit status should be $answer: $ret (OK)\033[0m"
else
  echo "\033[31mTest case $arg: Exit status should be $answer: $ret (NG)\033[0m"
fi

arg=-256
answer=0
./a.out $arg
ret=$?
if [ $ret -eq $answer ]; then
  echo "\033[32mTest case $arg: Exit status should be $answer: $ret (OK)\033[0m"
else
  echo "\033[31mTest case $arg: Exit status should be $answer: $ret (NG)\033[0m"
fi

arg=999
answer=231
./a.out $arg
ret=$?
if [ $ret -eq $answer ]; then
  echo "\033[32mTest case $arg: Exit status should be $answer: $ret (OK)\033[0m"
else
  echo "\033[31mTest case $arg: Exit status should be $answer: $ret (NG)\033[0m"
fi

arg=99999999999999999999
answer=255
./a.out $arg
ret=$?
if [ $ret -eq $answer ]; then
  echo "\033[32mTest case $arg: Exit status should be $answer: $ret (OK)\033[0m"
else
  echo "\033[31mTest case $arg: Exit status should be $answer: $ret (NG)\033[0m"
fi

arg=Hello
answer=255
./a.out $arg
ret=$?
if [ $ret -eq $answer ]; then
  echo "\033[32mTest case $arg: Exit status should be $answer: $ret (OK)\033[0m"
else
  echo "\033[31mTest case $arg: Exit status should be $answer: $ret (NG)\033[0m"
fi

arg=42Tokyo
answer=255
./a.out $arg
ret=$?
if [ $ret -eq $answer ]; then
  echo "\033[32mTest case $arg: Exit status should be $answer: $ret (OK)\033[0m"
else
  echo "\033[31mTest case $arg: Exit status should be $answer: $ret (NG)\033[0m"
fi

arg1="42"
arg2="41"
arg3="40"
answer=1
./a.out $arg1 $arg2 $arg3
ret=$?
if [ $ret -eq $answer ]; then
  echo "\033[32mTest case $arg1 $arg2 $arg3: Exit status should be $answer: $ret (OK)\033[0m"
else
  echo "\033[31mTest case $arg1 $arg2 $arg3: Exit status should be $answer: $ret (NG)\033[0m"
fi

arg1="42"
arg2="hello"
answer=1
./a.out $arg1 $arg2
ret=$?
if [ $ret -eq $answer ]; then
  echo "\033[32mTest case $arg1 $arg2: Exit status should be $answer: $ret (OK)\033[0m"
else
  echo "\033[31mTest case $arg1 $arg2: Exit status should be $answer: $ret (NG)\033[0m"
fi

arg1="hello"
arg2="42"
answer=255
./a.out $arg1 $arg2
ret=$?
if [ $ret -eq $answer ]; then
  echo "\033[32mTest case $arg1 $arg2: Exit status should be $answer: $ret (OK)\033[0m"
else
  echo "\033[31mTest case $arg1 $arg2: Exit status should be $answer: $ret (NG)\033[0m"
fi


# スクリプト全体の終了ステータスは、最後に実行されたコマンドの終了ステータスとする
exit 0