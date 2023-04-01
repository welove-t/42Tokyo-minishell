assert()
{
	# テストしようとしている内容をprint
	# $1の値を左寄せで30文字にフォーマットし、最後にコロンを付けて出力します。
	# printf 'arg1 = %s' "$1"
	printf '%-30s:' "\"$1\""

	# bashの出力をcmpに保存
	echo -n -e "$1" | bash >cmp 2>&-

	# bashのexit statusをexpectedに代入
	# 直前に実行されたコマンドの終了ステータスを変数expectedに代入しています。
	expected=$?

	# minishellの出力をoutに保存
	echo -n -e "$1" | ./minishell >out 2>&-

	# minishellのexit statusをactualに代入
	actual=$?

	# bashとminishellの出力を比較
	diff cmp out >/dev/null && echo -n '	diff OK' || echo -n '	diff NG'

	# bashとminishellの出力を比較
	if [ "$actual" = "$expected" ]; then
		echo -n '	status OK'
	else
		echo -n "	status NG, expected $expected but got $actual"
	fi
	echo
}

# ここの中身を変更する
# Empty line (EOF)
assert 'test'