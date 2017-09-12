" symlink this file into your ~/.vim/syntax/src.vim
" ln -fs ~/I/syntax.vim ~/.vim/syntax/src.vim

syntax match Comment	"\v#.*$"
syntax match Number		"\v([0-9]+(\.[0-9]+)?([eE][\+\-]?[0-9]+)?)"
syntax match Special	"\v0x[0-9A-Fa-f]+"
syntax match Operator	"\v[\+\-\*\/]"

syntax region String	start="'" end="'"

syntax match Special	"\v[\(\)\[\]\:\=]"

syntax match Constant	"\v[A-Z]+\s"
syntax match Keyword	"\v(sym|env|op)"
