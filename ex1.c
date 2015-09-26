#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {


    int count = 0;
    int numberToSearch;
    int *temp = NULL;
    int *data = NULL;

    void bubbleSort(int *data, int count) {

        int i, j, temp;

        count = count - 1;

        for (i = 0; i < count; i++) {
            for (j = 0; j < count - i; j++) {
                if (data[j] > data[j + 1]) {
                    temp = data[j + 1];
                    data[j + 1] = data[j];
                    data[j] = temp;
                }

            }

        }

    }


    int binarySearch(int *array, int length, int key) {
        int first, last, middle, search;

                    printf("%d\n", key);


        first = 0;
        last = length - 1;
        middle = (first + last) / 2;

        while (first <= last) {

            if (array[middle] < key) {

                first = middle + 1;
            }

            else if (array[middle] == key) {

                printf("%d found at location %d.\n", key, middle + 1);
                break;
            }
            else
                last = middle - 1;

            middle = (first + last) / 2;
        }
        if (first > last)
            printf("Not found! %d is not present in the list.\n", key);
    }

    data = malloc(sizeof(int));

    if (data == NULL) {

        printf("Error allocating memory.\n"); //print an error message
        return EXIT_FAILURE;

    }

    if (argc != 2) {

        printf("Please enter a valid filename as a parameter.\n");
        return EXIT_FAILURE;

    } else {
        FILE *file = fopen(argv[1], "r");

        if (file == 0) {

            printf("Could not open file\n");
            return EXIT_FAILURE;

        } else {

            while (!feof(file)) {

                fscanf(file, "%d", &data[count]);
                temp = realloc(data, (count + 2) * sizeof(int));

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
            printf("Reading completed. File contains %d integers!\n", count + 1);

            bubbleSort(data, count);
            printf("The list is now sorted!\n");
            for (int i = 0; i < count; i++) {
                printf("%d\n", data[i]);
            }

            printf("Enter a number to search for:\n");

            scanf("%d", &numberToSearch);

            binarySearch(data, count, numberToSearch);


        }

    }

    return EXIT_SUCCESS;
}

