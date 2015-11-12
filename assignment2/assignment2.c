/*
PG3400 - Home exam 1
By: Ekaterina Orlova
**/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

char *getStringFromFile(char *fileName) {

    char *dest;

    FILE *file = fopen(fileName, "rb");

    if (file == 0) {
        printf("Could not open file\n");
        return NULL;
    }

    fseek(file, 0L, SEEK_END);
    long s = ftell(file);
    rewind(file);
    dest = malloc(s);

    if (dest == NULL) {
        printf("Error allocating memory.\n");
        return NULL;
    }

    fread(dest, s, 1, file);
    fclose(file);
    file = NULL;

    return dest;
}


char *getMessageFromFile(char *fileName) {

    char *dest;

    FILE *file = fopen(fileName, "rb");

    if (file == 0) {
        printf("Could not open file\n");
        return NULL;
    }

    fseek(file, 0L, SEEK_END);
    long s = ftell(file);
    rewind(file);
    dest = malloc(s);

    if (dest == NULL) {
        printf("Error allocating memory.\n");
        return NULL;
    }

    fread(dest, s, 1, file);
    fclose(file);
    file = NULL;

    return dest;
}

char *encode(char *inputMessageFile, char *keyFile, int d) {

    char *buffer;

    buffer = getStringFromFile(keyFile);

    if (buffer == NULL) {
        printf("File could not be opened.\n"); //print an error message

        return NULL;
    }

    int i, j;

    for (i = 0; buffer[i] != '\0'; i++) {
        buffer[i] = tolower(buffer[i]);
        while (!((buffer[i] >= 'a' && buffer[i] <= 'z') ||
                 ((buffer[i] >= 'A' && buffer[i] <= 'Z') || buffer[i] == '\0'))) {
            for (j = i; buffer[j] != '\0'; j++) {
                buffer[j] = tolower(buffer[j + 1]);
            }
            buffer[j] = '\0';
        }
    }

    printf("Output String: ");
    printf("%s\n", buffer);


    char *bufferCopy;
    bufferCopy = malloc(sizeof(char) * strlen(buffer));
    strcpy(bufferCopy, buffer);
    printf("%s\n", bufferCopy);


    char *message = getMessageFromFile(inputMessageFile);
    printf("message: %s\n", message);
    size_t length = strlen(message);

    //allocate enough memory for encoded string
    char *result = calloc(4 * length, sizeof(char));

    if (result == NULL) {
        printf("Error allocating memory.\n");
        return NULL;
    }


    for (int i = 0; message[i] != '\0'; i++) {
        printf("encoding...: %c\n", message[i]);
        int previous;


        //non-letters remain as is 
        if (!isalpha(message[i])) {
            char letterResult[3];
            snprintf(letterResult, 3, "%c", message[i]);
            strncat (result, letterResult, 3);
        } else {

            bool found = false;

            while (!found) {

                for (int j = 0; bufferCopy[j] != 0; j++) {

                    //  printf("looking for i...: %c\n", bufferCopy[j]);


                    if (bufferCopy[j] == tolower(message[i])) {

                        //printf("%d\n", j);
                        //  printf("%d\n", d);
                        //printf("%d\n", previous);


                      //  if ((abs(j - previous)) > d) {

                            //printf("%d\n", j);
                            // printf("%d\n", previous);

                            found = true;
                            char letterResult[6];
                            bufferCopy[j] = ' '; //to ensure that same index is not used again for same letter
                            printf("found at index...: %d\n", j);

                            printf("%d\n", j - previous);
                            previous = j;

                            if (isupper(message[i])) {
                                snprintf(letterResult, 6, "[-%d]", j);
                            } else {
                                snprintf(letterResult, 6, "[%d]", j);
                            }
                            strncat(result, letterResult, 6);
                            break;

                      //  } else {
                       //     j++;
                       // }
                    }
                    printf("%d\n", j);
                }
                if (!found) {
                    strcpy(bufferCopy,
                           buffer);     //Then we try set in indexes that were removed even though those will be repeated
                }
            }
        }
        printf("%s\n", result);

    }

    printf("%s\n", bufferCopy);
    free(buffer);
    return result;
}


char *decode(char *inputCodeFile, char *keyFile) {

    char *messageToDecode = inputCodeFile;
    int count = 0;

    for (int i = 0; messageToDecode[i] != 0; ++i) {
        if (messageToDecode[i] == '[') {
            count++;
        }
    }

    char *key;

    key = getStringFromFile(keyFile);

    if (key == NULL) {
        printf("File could not be opened.\n"); //print an error message

        return NULL;
    }


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

 //   printf("%s\n", key);

    for (int i = 0; messageToDecode[i] != 0; ++i) {


        if (messageToDecode[i] == '[') {

            char number[3];
            int j, a;

            for (j = i + 1, a = 0; messageToDecode[j] != ']'; ++j, ++a) {
                number[a] = messageToDecode[j];

            }

            int numberAsInt = atoi(number);
            memset(number, 0, strlen(number));
            printf("%c\n", (numberAsInt >= 0) ? key[numberAsInt] : toupper(key[abs(numberAsInt)]));

            i += a + 1;

        } else {

            printf("%c\n", messageToDecode[i]);

        }
    }

}

int main() {


    char *message = encode("message.txt", "letItGo.txt", 1);
    decode(message, "letItGo.txt");
    free(message);

    return EXIT_SUCCESS;

/*

    char *buffer;

    buffer = getStringFromFile("bohemianRhapsody.txt");

    if (buffer == NULL) {
        printf("File could not be opened.\n"); //print an error message

        return EXIT_FAILURE;
    }

    int i, j;

    for (i = 0; buffer[i] != '\0'; i++) {
        buffer[i] = tolower(buffer[i]);
        while (!((buffer[i] >= 'a' && buffer[i] <= 'z') ||
                 ((buffer[i] >= 'A' && buffer[i] <= 'Z') || buffer[i] == '\0'))) {

            for (j = i; buffer[j] != '\0'; j++) {
                buffer[j] = tolower(buffer[j + 1]);
            }
            buffer[j] = '\0';
        }
    }
    printf("Output String: ");

    printf("Song: %s\n", buffer);


    char *message = "How are you, World?";
    printf("message: %s\n", message);
    size_t length = strlen(message);
    printf("%d\n", length);


    //char dest[200] = "";
    char *dest = calloc(4 * length, sizeof(char));


    for (int i = 0; message[i] != '\0'; i++) {
        printf("encoding...: %c\n", message[i]);

        //non-letters remain as is 
        if (!isalpha(message[i])) {
            char result[3];

            snprintf(result, 3, "%c", message[i]);

            strncat (dest, result, 3);
        } else {

            for (int j = 0; buffer[j] != 0; j++) {
                //  printf("looking for i...: %c\n", buffer[j]);


                if (buffer[j] == tolower(message[i])) {

                    char result[6];
                    printf("found at index...: %d\n", j);


                    if (isupper(message[i])) {
                        snprintf(result, 6, "[-%d]", j);
                    } else {
                        snprintf(result, 6, "[%d]", j);

                    }

                    strncat(dest, result, 6);

                    break;

                }
            }
        }
        printf("%s\n", dest);

    }

    free(buffer);


    return EXIT_SUCCESS;*/
}

