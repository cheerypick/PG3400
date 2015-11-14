/*
PG3400 - Home exam 1
By: Ekaterina Orlova
**/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

char *getStringFromFile(char *fileName) {
    char *dest = 0;

    FILE *file = fopen(fileName, "rb");

    if (file == 0) {
        printf("Could not open file\n");
        return NULL;
    }

    fseek(file, 0L, SEEK_END);
    long length = ftell(file) + 1;
    printf("Length is: %lu\n", length);
    fseek(file, 0, SEEK_SET);
    dest = calloc(length, 1);

    if (dest == NULL) {
        printf("Error allocating memory.\n");
        return NULL;
    }

    fread(dest, 1, length, file);
    fclose(file);
    file = NULL;

    return dest;
}

char *filterInput(char *key) {

    int i, j;

    for (i = 0; key[i] != '\0'; i++) {
        key[i] = tolower(key[i]);
        while (!((key[i] >= 'a' && key[i] <= 'z') ||
                 ((key[i] >= 'A' && key[i] <= 'Z') || key[i] == '\0'))) {

            for (j = i; key[j] != '\0'; j++) {
                key[j] = tolower(key[j + 1]);
            }
            key[j] = '\0';
        }
    }
    return key;

}

char* encode(char *messageFile, char *keyFile, int d) {

    char *key = filterInput(getStringFromFile(keyFile));
    char *message = getStringFromFile(messageFile);

    size_t length = strlen(message);
    // allocate enough memory for encoded string
    char *result = calloc(5 * length, 1);//because sizeof char is always 1

    srand(time(NULL));
 

    for (int i = 0; message[i] != '\0'; i++) {
        printf("\nEncoding...: %c\n", message[i]);
        int previous = 0;

        //non-letters remain as is 
        if (!isalpha(message[i])) {
            char letterResult[2];
            snprintf(letterResult, 2, "%c", message[i]);
            strncat (result, letterResult, 1);
        } else {
            bool found = false;
            int random = rand() % strlen(key);
            printf("Random: %ul\n", random);

            for (int j = 0; key[j] != 0; j++) {
                int currentKeyCharIndex = (random + j) % strlen(key);
                char currentKeyChar = key[currentKeyCharIndex];
                printf("%c", currentKeyChar);

                if (currentKeyChar == tolower(message[i])) {
                    if ((abs(currentKeyCharIndex - previous)) > d) {
                        found = true;
                        char letterResult[8];
         
                        previous = currentKeyCharIndex;

                        if (isupper(message[i])) {
                            snprintf(letterResult, 8, "[-%d]", currentKeyCharIndex);
                        } else {
                            snprintf(letterResult, 8, "[%d]", currentKeyCharIndex);
                        }
                        strncat(result, letterResult, 8);
                        break;
                    }
                }

            }

            if (!found) {
                printf("It's not possible to satisfy d condition\n");
                return NULL;
            }
        }
    }
    printf("Result: %s\n", result);
    return result;
}

char *decode(char *inputCodeFile, char *keyFile) {

    char *messageToDecode = inputCodeFile;

    printf("%s\n", messageToDecode);

    int count = 0;

    for (int i = 0; messageToDecode[i] != 0; ++i) {
        if (messageToDecode[i] == '[') {
            count++;
        }
    }

    char *key = filterInput(getStringFromFile(keyFile));

    if (key == NULL) {
        printf("File could not be opened.\n"); //print an error message
        return NULL;
    }

            char number[3];


    for (int i = 0; messageToDecode[i] != 0; ++i) {
        if (messageToDecode[i] == '[') {

            int j, a;

            for (j = i + 1, a = 0; messageToDecode[j] != ']'; ++j, ++a) {
                number[a] = messageToDecode[j];
            }

            int numberAsInt = atoi(number);

            if ((size_t)abs(numberAsInt) > strlen(key)) {
                printf("Wrong file!\n" );
                return NULL;
            }
            memset(number, 0, strlen(number));
            printf("%c\n", (numberAsInt >= 0) ? key[numberAsInt] : toupper(key[abs(numberAsInt)]));

            i += a + 1;

        } else {
            printf("%c\n", messageToDecode[i]);
        }
    }
    return key;
}


int main() {
    
    char *encoded = encode("message.txt", "ex.txt", 2);

    char *decoded = decode(encoded, "ex.txt");

    printf("Decoded: %s\n", decoded);

    //char *message = encode("message.txt", "bohemianRhapsody.txt", 10);
    //if( message ) decode(message, "bohemianRhapsody.txt");

    return EXIT_SUCCESS;

}

