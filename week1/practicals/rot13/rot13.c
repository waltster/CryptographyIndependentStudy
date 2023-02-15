#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int rotation = 13;

    if(argc < 2 || argc > 3) {
        printf("%s: <message> [rotation]\n", argv[0]);
        exit(1);
    } else if(argc == 3) {
        rotation = atoi(argv[2]);
    }

    char *message = argv[1];
    char ascii_uppercase_begin = 65;
    char ascii_uppercase_end = 90;
    char ascii_lowercase_begin = 97;
    char ascii_lowercase_end = 122;
    char *new_message = (char*)malloc(strlen(message));
    memset(new_message, 0, strlen(message));

    printf("Message before rotation: %s\n", message);

    for(int i = 0; i < strlen(message); i++) {
        char c = message[i];

        // This condition is true if the character is a letter is uppercase
        if(c >= ascii_uppercase_begin && c <= ascii_uppercase_end) {
            // Get the location in the alphabet.
            int loc = c - ascii_uppercase_begin; 
            loc += rotation;
            loc = loc % 26;
            new_message[i] = (char)(loc + ascii_uppercase_begin);
        } 
        // This condition is true if the character is a letter and is lowercase
        else if(c >= ascii_lowercase_begin && c <= ascii_lowercase_end) {
            // Get the location in the alphabet.
            int loc = c - ascii_lowercase_begin;
            loc += rotation;
            loc = loc % 26; 
            new_message[i] = (char)(loc + ascii_lowercase_begin);
        } 
        // This condition is true if the character is not alphabetical
        else {
            new_message[i] = c;
        }
    }

    printf("Message after rotation: %s\n", new_message);
}
