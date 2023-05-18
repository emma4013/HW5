#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trienode.h"

void printWord(char *word) {
    if (word) {
        printf("'%s'\n", word);
    } else {
        printf("Not found in current dictionary.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s FILE\n", argv[0]);
        return 1;
    }

    FILE *dict = fopen(argv[1], "r");
    if (!dict) {
        printf("Error opening dictionary file.\n");
        return 1;
    }

    trieNode *root = build_tree(dict);
    fclose(dict);

    printf("Enter 'exit' to quit.\n");

    char input[MAXLEN];
    char prevPattern[MAXLEN] = "";
    int hasT9onym = 0;
    int printNext = 0;

    while (1) {
        printf("Enter Key Sequence (or '#' for next word):\n> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;  // End-of-file reached
        }

        input[strcspn(input, "\n")] = '\0';  // Remove newline character

        if (strcmp(input, "exit") == 0) {
            break;  // Exit the program
        }

        if (strcmp(input, "#") == 0) {
            if (printNext) {
                // Print next word with the same numeric value
                if (hasT9onym) {
                    char *nextWord = get_word(root, prevPattern);
                    printWord(nextWord);
                } else {
                    printf("There are no more T9onyms.\n");
                }
            } else {
                printf("Invalid input. Please enter a valid Key Sequence.\n");
            }
        } else {
            // Print word corresponding to the pattern
            char *word = get_word(root, input);
            printWord(word);
            strncpy(prevPattern, input, sizeof(prevPattern));
            hasT9onym = (word != NULL);
            printNext = 1;
        }
    }

    free_tree(root);

    return 0;
}