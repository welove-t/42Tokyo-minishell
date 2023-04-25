# 概要

**pushする前にテストすること！**
※最終的にはテスターを導入する予定

# テスト内容

## 引数なし

< Normal >
- ls
- uname

< Error >
- hoge

## 引数あり

< Normal >
- ls -l
- uname -a -v -r

< Error >
- hoge -l -p

## リダイレクション単数

< Normal >
- cat < Makefile
- ls -l > outfile
- cat Makefile >> outfile

< Error >
- hoge < Makefile
- cat < noting_file (存在しないファイル)
- hoge > outfile
- ls -l > lock_file (書き込み権限がないファイル)
- hoge >> outfile
- ls -l >> lock_file (書き込み権限がないファイル)

## リダイレクション複数

< Normal >
- cat < Makefile < includes/minishell.h < srcs/main.c
- ls -l > out1 > out2 > out3
- ls -l >> out1 >> out2 >> out3
- cat < Makefile > out1 >> out2

< Error >
- hoge < Makefile < includes/minishell.h < srcs/main.c
- cat < Makefile < noting_file < srcs/main.c
- hoge > out1 > out2 > out3
- ls -l > out1 > lock_file > out3
- hoge >> out1 >> out2 >> out3
- lsーl >> out1 >> lock_file >> out3
- hoge < Makefile > out1 >> out2
- cat < noting_file > out2 >> out2
- cat < Makefile > lock_file >> out2

## heredoc単体

< Normal >
- cat << EOF
	- a
	- b
	- EOF

< Error >
- hoge << EOF
	- a
	- b
	- EOF

## heredoc複数

< Normal >
- cat << EOF << END
	- a
	- b
	- EOF
	- c
	- d
	- END
- cat << EOF << END > out1 > out2
	- a
	- b
	- EOF
	- c
	- d
	- END

< Error >
- hoge << EOF << END
	- a
	- b
	- EOF
	- c
	- d
	- END
- cat << EOF << END > lock_file > out2
	- a
	- b
	- EOF
	- c
	- d
	- END

## パイプ単体

< Normal >
- ls -l | wc -l

< Error >
- hoge | ls -l
- ls -l | hoge

## パイプ複数

< Normal >
- cat Makefile | grep "SOURCES" | wc -l
- cat < Makefile | grep "SOURCES" > out1 | wc -l >> out1
- cat | cat | ls

< Error >
- cat | cat | hoge
- cat < noting_file | grep "SOURCES" > out1 | wc -l >> out1

## signal

### ○初期状態
- ctrl-C
- ctrl-D
- ctrl-\
### ○入力後
- ctrl-C
- ctrl-D
- ctrl-\
### ○入力待ち
cat後
- ctrl-C
- ctrl-D
- ctrl-\
### ○heredoc
cat << EOFで何か入力した後
- ctrl-C
- ctrl-D
- ctrl-\

### 何回か改行

### ビルトイン
