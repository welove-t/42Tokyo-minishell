# 課題の解釈

## 対応した機能

- リダイレクト
	- '<' '>' '<<' '>>'

## 対応していない機能

- '\' (バックスラッシュ) ・ ';'(セミコロン) ・ 閉じていない引用符
	- syntax errorとして対応（本家挙動とは異なる）
	- 課題には「Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).」と記載
	- 「機能を実装せよ」ではなく「解釈しないように」と記載されているため本家挙動ではなくエラー扱いとした


- $$などの


## 検討中
- パイプ終わり（例： ls |  ）のケース
	- 本家挙動はコマンド受付状態になる
