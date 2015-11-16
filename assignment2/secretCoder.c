
#include "secretCoder.h"




char *getStringFromFile(char *fileName) {
    char *dest = 0;

    FILE *file = fopen(fileName, "rb");


    if (file == 0) {
        printf("Could not open file\n");
        return NULL;
    }

    fseek(file, 0L, SEEK_END);
    long length = ftell(file) + 1;
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


char *encodeWithD(char *messageFile, char *keyFile, int d, int *status) {

    char *key = filterInput(getStringFromFile(keyFile));
    char *message = getStringFromFile(messageFile);

    size_t length = strlen(message);
    // allocate enough memory for encoded string
    char *result = calloc(5 * length, 1);//because sizeof char is always 1


    srand(time(NULL));
    int previousKeyCharIndex = 0;


    for (int i = 0; message[i] != '\0'; i++) {

        //non-letters remain as is 
        if (!isalpha(message[i])) {
            char letterResult[2];
            snprintf(letterResult, 2, "%c", message[i]);
            strncat (result, letterResult, 1);
        } else {
            bool found = false;
            int random = rand() % strlen(key);

            for (int j = 0; key[j] != 0; j++) {
                int currentKeyCharIndex = (random + j) % strlen(key);
                char currentKeyChar = key[currentKeyCharIndex];

                if (currentKeyChar == tolower(message[i])) {
                    if ((abs(currentKeyCharIndex - previousKeyCharIndex)) > d) { //checking d condition 
             
                        found = true;
                        char letterResult[8];

                        previousKeyCharIndex = currentKeyCharIndex;

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
                *status = 0;
                return NULL;
            }
        }
    }
    *status = 1;
    printf("Result: %s\n", result);
    free(message);
    message = NULL;

    free(key);
    key=NULL;
    return result;
}


char *encode(char *messageFile, char *keyFile, int *status) {
    return encodeWithD(messageFile, keyFile, 0, status);
}

char *decode(char *encodedMessage, char *keyFile, int *status) {

    char *messageToDecode = encodedMessage;
    char *result = calloc(strlen(messageToDecode), 1);
    char *key = filterInput(getStringFromFile(keyFile));

    if (key == NULL) {
        printf("File could not be opened.\n"); //print an error message
         *status = 0;
        return NULL;
    }

    int count = 0;

    for (int i = 0; messageToDecode[i] != 0; ++i) {
        if (messageToDecode[i] == '[') {

            char *number;
            number = calloc(5, 1);
            int j, a;

            for (j = i + 1, a = 0; messageToDecode[j] != ']'; ++j, ++a) {
                number[a] = messageToDecode[j];
            }

            int numberAsInt = atoi(number);

            if ((size_t) abs(numberAsInt) > strlen(key)) {
                printf("This file is not the key the message was encoded with!\n");
                 *status = 0;
                return NULL;
            }

            result[count] = (numberAsInt >= 0) ? key[numberAsInt] : toupper(key[abs(numberAsInt)]);
            i += a + 1;

            free(number);
            number = NULL;
            count++;


        } else {

            result[count] = messageToDecode[i];
            count++;

        }
    }

     *status = 1;
    return result;
}
