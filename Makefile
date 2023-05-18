# Emma Tran
# 5-17-23
# CSE 374 HW 5

# Builds the executable t9 when invoked with just the 'make' command
all: t9

# Target for builting the t9 executable
t9: trie.o tnine.o
	gcc -Wall -std=c11 -g -o t9 trie.o tnine.o

# Target for building trie.o object file and
# it depends on the trie.c and trienode.h files
trie.o: trie.c trienode.h
	gcc -Wall -std=c11 -g -c trie.c trienode.h

# Target for building the tnine.o object file
# and it depends on tnine.c and trienode.h files
tnine.o: tnine.c trienode.h
	gcc -Wall -std=c11 -g -c tnine.c trienode.h

# Cleans Target
clean:
	rm -f *.o t9 *~