// tnine.c
// Emma Tran
// 5-17-23
// CSE 374 HW 5

/* tnine is a program that drives a trie / t9 program. This code
   builds a trie according to trienode.h and runs an interactive
   session where the user can retrieve words using T9 sequences.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

// Runs decoding interaction with the user
void run_session(trieNode* wordTrie);

int main(int argc, char** argv) {
    // File pointer to the dictionary file
    FILE* dictionary = NULL; 
    // Pointer to the trie data structure
    trieNode* wordTrie = NULL; 

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [DICTIONARY]\n", argv[0]);
        return EXIT_FAILURE;
    } else {
        // Opens the dictionary file in read mode
        dictionary = fopen(argv[1], "r"); 
        if (!dictionary) {
            fprintf(stderr, "Error: Cannot open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    // Builds the trie using the dictionary
    wordTrie = build_tree(dictionary);
    // Runs the interactive session to retrieve words using T9 sequences
    run_session(wordTrie);
    // Cleans up by freeing memory and closing the dictionary file
    free_tree(wordTrie);
    fclose(dictionary);

    return EXIT_SUCCESS;
}

// Runs an interactive session where the user can retrieve words using T9 sequences
void run_session(trieNode* wordTrie) {
    // Acts as a buffer to store user input
    char userInput[MAXLEN]; 
    // Acts as a buffer to store the previous user input
    char prev[MAXLEN]; 

    printf("Enter \"exit\" to quit.\n");
    while (1) {
        printf("Enter Key Sequence (or \"#\" for next word):\n>");
        // Reads user input
        scanf("%s", userInput); 

        // Exits the interactive session if user inputs "exit"
        if (strncmp(userInput, "exit", 4) == 0) {
            break; 
        } else if (strncmp(userInput, "#", 1) == 0) {
            int i = strlen(prev);
            // Adds '#' to the end of the previous sequence
            prev[i + 1] = '\0'; 
            prev[i] = '#';
        } else {
            int j = strlen(userInput);
            // Copies user input to the previous sequence buffer
            strncpy(prev, userInput, j + 1); 
        }
        // Prints the word associated with the T9 sequence
        printf("%s\n", get_word(wordTrie, prev)); 
    }
}