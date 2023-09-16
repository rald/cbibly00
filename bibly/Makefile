all: bibly pick find

bibly: bibly.c info.h token.h lexer.h parser.h cite.h
	gcc bibly.c -o bibly -g --std=c89

pick: pick.c strutil.h
	gcc pick.c -o pick -g --std=c89
find: find.c strutil.h
	gcc find.c -o find -g --std=c89

clean:
	rm bibly pick find

