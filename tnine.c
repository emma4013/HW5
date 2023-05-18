#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trienode.h"

void printWord(const char *word) {
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
    while (1) {
        printf("Enter Key Sequence (or '#' for next word):\n> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;  // End-of-file reached
        }

        input[strcspn(input, "\n")] = '\0';  // Remove newline character

        if (strcmp(input, "exit") == 0) {
            break;  // Exit the program
        }

        int len = strlen(input);
        int index = 0;
        int printNext = 0;
        while (index < len) {
            char pattern[MAXLEN];
            int patternIndex = 0;
            while (index < len && input[index] != '#') {
                pattern[patternIndex++] = input[index++];
            }
            pattern[patternIndex] = '\0';

            if (printNext && patternIndex == 0) {
                // Print next word with the same numeric value
                if (hasT9onym) {
                    char *nextWord = get_word(root, prevPattern);
                    printWord(nextWord);
                } else {
                    printf("There are no more T9onyms.\n");
                }
                printNext = 0;
            } else {
                // Print word corresponding to the pattern
                char *word = get_word(root, pattern);
                printWord(word);
                strncpy(prevPattern, pattern, sizeof(prevPattern));
                hasT9onym = (word != NULL);
            }

            if (index < len && input[index] == '#') {
                index++;
                printNext = 1;
                if (patternIndex == 0) {
                    // Print next word with the same numeric value
                    if (hasT9onym) {
                        char *nextWord = get_word(root, prevPattern);
                        printWord(nextWord);
                    } else {
                        printf("There are no more T9onyms.\n");
                    }
                }
            }
        }
    }

    free_tree(root);

    return 0;
}
