#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

void convert(const char *word, char *sequence) {
    int i;
    for (i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        if (c >= 'a' && c <= 'c') {
            sequence[i] = '2';
        } else if (c >= 'd' && c <= 'f') {
            sequence[i] = '3';
        } else if (c >= 'g' && c <= 'i') {
            sequence[i] = '4';
        } else if (c >= 'j' && c <= 'l') {
            sequence[i] = '5';
        } else if (c >= 'm' && c <= 'o') {
            sequence[i] = '6';
        } else if (c >= 'p' && c <= 's') {
            sequence[i] = '7';
        } else if (c >= 't' && c <= 'v') {
            sequence[i] = '8';
        } else if (c >= 'w' && c <= 'z') {
            sequence[i] = '9';
        } else {
            sequence[i] = '0';  // Treat non-alphabetic characters as '0'
        }
    }
    sequence[i] = '\0';
}

// Helper function to create a new trieNode
trieNode* createNode() {
    trieNode* new = (trieNode*)malloc(sizeof(trieNode));
    if (new) {
        new->word = NULL;
        for (int i = 0; i < BRANCHES; i++) {
            new->branches[i] = NULL;
        }
    }
    return new;
}

// Given a word list (dict), build a trie that holds each word.
// Returns a pointer to the root node.
trieNode* build_tree(FILE* dict) {
    trieNode* root = createNode();

    char word[MAXLEN];
    while (fgets(word, MAXLEN, dict)) {
        word[strcspn(word, "\n")] = '\0'; // Remove newline character from the word

        // Convert the word to T9 key sequence
        char sequence[MAXLEN];
        convert(word, sequence);

        trieNode* current = root;
        int i = 0;
        while (sequence[i]) {
            int index = sequence[i] - '0';
            if (!current->branches[index]) {
                current->branches[index] = createNode();
            }
            current = current->branches[index];
            i++;
        }

        if (!current->word) {
            current->word = strdup(word);
        } else {
            // Handle case where multiple words have the same key sequence
            trieNode* new = createNode();
            new->word = strdup(word);
            current->branches[0] = new;
        }
    }

    return root;
}

// Given a pattern, return the word stored in the appropriate trieNode
char* get_word(trieNode* root, char* pattern) {
    trieNode* current = root;
    int i = 0;
    while (pattern[i]) {
        int index = pattern[i] - '0';
        if (!current->branches[index]) {
            return NULL; // Word not found
        }
        current = current->branches[index];
        i++;
    }

    return current->word;
}

// Deletes the entire tree branching from root
void free_tree(trieNode* root) {
    if (!root) {
        return;
    }

    for (int i = 0; i < BRANCHES; i++) {
        free_tree(root->branches[i]);
    }

    free(root->word);
    free(root);
}