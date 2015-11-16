/*
PG3400 - Home exam 1
By: Ekaterina Orlova
**/
#include "secretCoder.h"


char *findFirstWordByLength(char *stringToSearch, int minLength) {
    
    char *word = calloc(minLength+3, 1);
    int i, a;
    word[0] = '\n';


    for (i = 0, a = 1; stringToSearch[i] != '\0'; ++i) {

        if (isalpha(stringToSearch[i])) {
            word[a] = stringToSearch[i];
            a++;
        }
        else {
            if (a > minLength) {
                word[a] = '\n';
                return word;

            } else {
                word[0] = '\n';
                word[1] = '\0';
                a = 1;
            }
        }
    }
    free(word);
    word = NULL;
    return NULL;
}

bool hasTxtExtension(char const *name) {
    size_t len = strlen(name);
    return len > 4 && strcmp(name + len - 4, ".txt") == 0;
}

int main(int argc, char *argv[]) {

     if (argc != 2) {

        printf("Please enter a d condition as a parameter.\n");
        return EXIT_FAILURE;

    }

    int dCondition =  atoi(argv[1]);

    printf("Minimum distance between adjacent codes will be set to %d\n", dCondition);

    int statusEncode;
    int statusDecode;

    char *encoded = encodeWithD("message.txt", "letItGo.txt", dCondition, &statusEncode);
    char *decoded;



    if (statusEncode) {

        printf("Decoded message with known key: %s\n", decode(encoded, "letItGo.txt", &statusDecode));


        //Hacking the whole dictionary - bruteforce FTW!

        DIR *d;
        struct dirent *dir;
        d = opendir("./");
        if (d) {
            while ((dir = readdir(d)) != NULL) {
                if (hasTxtExtension(dir->d_name)) {
                    printf("Trying to decode with following file: %s\n", dir->d_name);
                    char *fileName = dir->d_name;
                    decoded = decode(encoded, fileName, &statusDecode);

                    if (decoded) {

                        char *word = findFirstWordByLength(decoded, 5);
                        printf("Searching for this word in dictionary: %s\n", word);

                        char *dictionary = getStringFromFile("/usr/share/dict/words");

                        char *stringFound = strstr(dictionary, word);
                        if (stringFound) {
                            printf("Found a possible message: %s\n", decoded);
                            break;
                        }
                        free(word);
                        free(dictionary);
                        word = NULL;
                    }

                }
            }

            closedir(d);
        }


        free(decoded);
        decoded = NULL;


    }

    free(encoded);
    encoded = NULL;
    return EXIT_SUCCESS;

}

