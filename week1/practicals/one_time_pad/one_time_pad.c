#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ASCII_UPPERCASE_A 65
#define ASCII_UPPERCASE_Z 90
#define ASCII_LOWERCASE_A 97
#define ASCII_LOWERCASE_Z 122

// Test if a character is alphabetic by evaluating its ASCII code.
bool is_alphabetic(char c) {
    if((c >= ASCII_UPPERCASE_A && c <= ASCII_UPPERCASE_Z) || 
       (c >= ASCII_LOWERCASE_A && c <= ASCII_LOWERCASE_Z)) {
        return true;
    }

    return false;
}

// Test if a character is uppercase by evaluting its ASCII code.
bool is_uppercase(char c) {
    if(c >= ASCII_UPPERCASE_A && c <= ASCII_UPPERCASE_Z) {
        return true;
    }

    return false;
}

// Get the integer position in the alphabet for character c.
// Note: does not provide any kind of error-checking for non-character inputs
char get_alphabet_pos(char c) {
    if (is_uppercase(c)) {
        return (c - ASCII_UPPERCASE_A);
    }

    return (c - ASCII_LOWERCASE_A);
}

// Encrypt message with provided key into provided buffer
void encrypt(char *message, char *key, char *new_message) {
    for (int i = 0; i < strlen(message); i++) {
        // Retrieve both M(i) and K(i)
        char mi_raw = message[i];
        char ki_raw = key[i];

        // If for some reason there is a non-numeric character, continue.
        if(!is_alphabetic(mi_raw)) {
            new_message[i] = message[i];
            continue;
        }

        char mi = get_alphabet_pos(mi_raw);
        char ki = get_alphabet_pos(ki_raw);

        // C(i) = (M(i) + K(i)) mod 26
        char ci = ((mi + ki) % 26);
        
        // Preserve case of the letter.
        ci += (is_uppercase(mi_raw) ? ASCII_UPPERCASE_A : ASCII_LOWERCASE_A);

        new_message[i] = ci;
    }
}

// Decrypt message with provided key into provided buffer
void decrypt(char *message, char *key, char *new_message) {
    for (int i = 0; i < strlen(message); i++ ){
        char ci_raw = message[i];
        char ki_raw = key[i];

        if (!is_alphabetic(ci_raw)) {
            new_message[i] = message[i];
            continue;
        }

        char ci = get_alphabet_pos(ci_raw);
        char ki = get_alphabet_pos(ki_raw);

        // 1. Perform C(i) - K(i) and add 26 if it is negative
        char mi = ((ci - ki) < 0 ? (ci - ki + 26) : (ci - ki));

        // 2. Mod 26 the result
        mi %= 26;

        // 3. Make it ASCII
        mi += (is_uppercase(ci) ? ASCII_UPPERCASE_A : ASCII_LOWERCASE_A);

        new_message[i] = mi;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("%s: <option> <message> <key>\n", argv[0]);
        printf("  -e : Encrypt a message\n");
        printf("  -d : Decrypt a message\n");
        exit(1);
    }

    char *operation = argv[1];
    char *message = argv[2];
    char *key = argv[3];
    char *new_message = (char*)malloc(strlen(message));
    memset(new_message, 0, strlen(message));

    if (strlen(message) > strlen(key)) {
        fprintf(stderr, "Error: The length of OTP provided must be at least as "
                        "long as the message itself\n");
        exit(1);
    }    

    // Provide functionality depending on the flags
    if (strncmp(operation, "-e", 2) == 0) {
        encrypt(message, key, new_message);
    } else if (strncmp(operation, "-d", 2) == 0){
        decrypt(message, key, new_message);
    } else {
        fprintf(stderr, "Unknown option: %s", argv[1]);
        exit(1);
    }

    printf("Message after OTP: %s\n", new_message);
}
