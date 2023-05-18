all: t9 tnine

t9: t9.c trie.o
	gcc -Wall -Wextra -std=c99 -o t9 t9.c trie.o

tnine: tnine.c trie.o
	gcc -Wall -Wextra -std=c99 -o tnine tnine.c trie.o

trie.o: trie.c trienode.h
	gcc -Wall -Wextra -std=c99 -c trie.c -o trie.o

clean:
	rm -f t9 tnine trie.o
