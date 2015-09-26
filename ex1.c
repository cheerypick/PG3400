#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

    	printf("Hello\n");

    int count = 0;
    int *temp = NULL;
    int *data = NULL;

    data = malloc(sizeof(int));

    	printf("Hello2\n");

    if (data == NULL) {

        printf("Error allocating memory.\n"); //print an error message
        return EXIT_FAILURE;

    }

    if (argc != 2) {

        printf("Please enter a valid filename as a parameter.\n");
        return EXIT_FAILURE;

    } else {

    	printf("Hello\n");
        FILE *file = fopen(argv[1], "r");


        if (file == 0) {

            printf("Could not open file\n");
            return EXIT_FAILURE;

        } else {

            while (!feof(file)) {

                fscanf(file, "%d", &data[count]);
                temp = realloc(data, (count + 2) * sizeof(int));
                printf("%d is stored to the array\n", data[count]);

                if (temp != NULL) {
                    data = temp;
                } else {
                    free(data);
                    printf("Error allocating memory!\n");
                    return 1;
                }

                count++;

            }

            fclose(file);

        }

    }

}