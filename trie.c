// Emma Tran
// 5-17-23
// CSE 374 HW 5

/* trie implements a trie, made of trieNodes. This includes
   code to build, search, and delete a trie
   CSE374, HW5, 22wi 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

// Function prototypes
trieNode* put_word(trieNode* treeRoot, char* word);
int* wordInt(char* word);
int get_num(char word);
trieNode* make_node();

// Inserts a word into the trie and 
// returns the updated root node of the trie
trieNode* put_word(trieNode* treeRoot, char* word) {
    trieNode* curr = treeRoot;
    int* number = wordInt(word);

    // Traverses the trie based on the characters in the word
    for (int i = 0; word[i] != '\0'; i++) {
        int j = number[i];
        if (curr->branches[j] == NULL) {
            curr->branches[j] = make_node();
        }
        curr = curr->branches[j];
    }

    // Finds the first available branch for the remaining characters
    while (curr->word != NULL) {
        int avail = 0;
        while (curr->branches[avail] != NULL) {
            avail++;
        }
        curr->branches[avail] = make_node();
        curr = curr->branches[avail];
    }

    // Allocates memory for the word and store it in the current node
    curr->word = (char*)malloc(strlen(word) + 1);
    strncpy(curr->word, word, strlen(word) + 1);
    free(number);

    return treeRoot;
}

// Converts a word to an array of corresponding numbers
// and returns an array of integers representing the word
int* wordInt(char* word) {
    int* numWord = malloc(sizeof(int) * strlen(word));
    for (int i = 0; i < strlen(word); i++) {
        numWord[i] = get_num(word[i]);
    }
    return numWord;
}

// Converts a character to a corresponding number
// and returns the corresponding number based on the character
int get_num(char word) {
    int iword = (int)word;
    if (iword < 100) {
        return 1;
    } else if (iword < 103 && iword >= 100) {
        return 2;
    } else if (iword < 106 && iword >= 103) {
        return 3;
    } else if (iword < 109 && iword >= 106) {
        return 4;
    } else if (iword < 112 && iword >= 109) {
        return 5;
    } else if (iword < 116 && iword >= 112) {
        return 6;
    } else if (iword < 119 && iword >= 116) {
        return 7;
    } else if (iword < 122 && iword >= 119) {
        return 8;
    } else {
        return 0;
    }
}

// Builds a trie from a dictionary file
// and returns the root node of the constructed trie
trieNode* build_tree(FILE* dict) {
    char word[MAXLEN];
    trieNode* treeRoot = make_node();

    // Reads each word from the dictionary file and insert it into the trie
    while (fgets(word, MAXLEN, dict) != NULL) {
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }
        treeRoot = put_word(treeRoot, word);
    }
    return treeRoot;
}

// Retrieves a word from the trie based on the given pattern
// Parameters:
// - root: The root node of the trie
// - pattern: The pattern to search for
// Returns: The found word or an error message if not found
char* get_word(trieNode* root, char* pattern) {
    trieNode* curr = root;
    for (int i = 0; pattern[i] != '\0'; i++) {
        if (pattern[i] != '#') {
            if (pattern[i] < '1' || pattern[i] > '9') {
                return "Not found in current dictionary.";
            }

            // Convert the pattern character to an index and traverse the trie
            int x = (pattern[i] - '0') - 1;
            if (curr->branches[x] == NULL) {
                return "Not found in current dictionary.";
            }
            curr = curr->branches[x];
        } else if (pattern[i] == '#') {
            if (curr->branches[0] == NULL) {
                return "There are no more T9onyms";
            }
            curr = curr->branches[0];
        }
    }
    if (curr->word == NULL) {
        return "Not found in current dictionary.";
    } else {
        return curr->word;
    }
}

// Frees the memory allocated for the trie
void free_tree(trieNode* root) {
    if (root == NULL) {
        return;
    }

    // Frees the memory recurisvely for each node in the trie
    for (int i = 0; i < BRANCHES; i++) {
        free_tree(root->branches[i]);
    }

    free(root->word);
    free(root);
}

// Creates a new trie node and initializes it
// Returns the newly created trie node
trieNode* make_node() {
    trieNode* node = (trieNode*)malloc(sizeof(trieNode));
    if (node != NULL) {
        for (int i = 0; i < BRANCHES; i++) {
            node->branches[i] = NULL;
        }
    }
    node->word = NULL;
    return node;
}
