/*
PG3400 - Home exam 1
By: Ekaterina Orlova
**/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>



int main() {
    char *buffer;
    FILE *fh = fopen("bohemianRhapsody.txt", "rb");
    if (fh != NULL) {
        fseek(fh, 0L, SEEK_END);
        long s = ftell(fh);
        rewind(fh);
        buffer = malloc(s);
        if (buffer != NULL) {
            fread(buffer, s, 1, fh);
            // we can now close the file
            fclose(fh);
            fh = NULL;

            int i, j;

            for (i = 0; buffer[i] != '\0'; i++) {
                buffer [i] = tolower(buffer[i]);
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

            char dest[200] = "";

            for (int i = 0; message[i] != '\0'; i++) {
                printf("encoding...: %c\n", message[i]);

                //non-letters remain as is 
                if (!isalpha(message[i])) {
                    char result[3];

                    snprintf(result, 3, "%c", message[i]);

                    strncat (dest, result, 3);
                } else {

                for(int j = 0; buffer[j] != 0; j++) {
                    printf("looking for i...: %c\n", buffer[j]);


                    if (buffer[j] == tolower(message[i])) {

                        char result[6];
                        printf("found at index...: %d\n", j);


                        if(isupper(message[i])) {
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

        }
        if (fh != NULL) fclose(fh);
    }


    return EXIT_SUCCESS;
}

