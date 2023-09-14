all: bibly pick find

bibly: bibly.c info.h token.h lexer.h parser.h cite.h
	gcc bibly.c -o bibly -O3 -s

pick: pick.c strutil.h
	gcc pick.c -o pick -O3 -s

find: find.c strutil.h
	gcc find.c -o find -O3 -s

clean:
	rm bibly pick find

