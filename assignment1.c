/*
PG3400 - Home exam 1
By: Ekaterina Orlova
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/* All the above sorting functions operate with array of pointers, not modifying the initial data structure.
 * Therefore it is possible to keep track of original indices of integers in initial array. */

void bubbleSort(int **pointers, int size) {
    
    int i, j;
    intptr_t temp;

    size = size - 1;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size - i; j++) {
            if (*pointers[j] > *pointers[j + 1]) {
                temp = (intptr_t) pointers[j + 1];
                pointers[j + 1] = pointers[j];
                pointers[j] = (int *) temp;
            }
        }
    }
}

void insertionSort(int **pointers, int size) {
    
    int i, j;
    
    for (i = 1; i < size; i++) {
        int *value = pointers[i];
        for (j = i; j > 0 && *value < *pointers[j - 1]; j--) {
            pointers[j] = pointers[j - 1];
        }
        pointers[j] = value;
    }
}

/*MergeSort recursive implementation based on
 * Lusheng Wang's algorithm
 * http://www.cs.cityu.edu.hk/~lwang/ccs4335/mergesort.c */

void merge(int **first, int a, int **last, int b, int **array) {
    
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < a && j < b) {
        if (*first[i] <= *last[j]) {
            array[k] = first[i];
            i++;
            k++;
        }
        else {
            array[k] = last[j];
            j++;
            k++;
        }
    }
    //Move the remaining elements in first half to result array
    while (i < a) {
        array[k] = first[i];
        i++;
        k++;
    }
    //Move the remaining elements in the second half to result array
    while (j < b) {
        array[k] = last[j];
        j++;
        k++;
    }
}


void mergeSort(int **array, int size) {

    int i;
    int **first, **last;
    int n1, n2;

    if (size < 2)
        return;

    // Divide array into two
    n1 = size / 2;
    n2 = size - n1;
    first = (int **) malloc(sizeof(int *) * n1);
    last = (int **) malloc(sizeof(int *) * n2);

    for (i = 0; i < n1; i++) {
        first[i] = array[i];
    }
    for (i = 0; i < n2; i++) {
        last[i] = array[i + n1];
    }
    // Recursion
    mergeSort(first, n1);
    mergeSort(last, n2);

    //Merge small arrays into one
    merge(first, n1, last, n2, array);
    free(first);
    free(last);
    first = NULL;
    last = NULL;
}

int binarySearch(int **pointerArray, int *original, int length, int key) {
    int first, last, middle, initialIndex;

    first = 0;
    last = length - 1;
    middle = (first + last) / 2;

    while (first <= last) {

        if (*pointerArray[middle] < key) {

            first = middle + 1;
        }

        else if (*pointerArray[middle] == key) {

            printf("%d found at location %d.\n", key, middle + 1);

            // Pointer arithmetics to the rescue!
            // Obtain the original index by subtracting the pointer to the first element of original array from the pointer in the sorted array of pointers.

            initialIndex = pointerArray[middle] - original + 1;
            printf("Initial position of %d was at location %d.\n", key, initialIndex);
            break;
        }
        else
            last = middle - 1;

        middle = (first + last) / 2;
    }
    if (first > last)
        printf("Not found! %d is not present in the list.\n", key);

    return EXIT_SUCCESS;

}


int main(int argc, char *argv[]) {

    int count = 0;
    int numberToSearch, algorithmId;
    int *data = NULL;
    int *temp = NULL;
    int **pointers = NULL;


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


            pointers = malloc(count * sizeof(int *));
            for (int i = 0; i < count; i++) {
                pointers[i] = &data[i];
            }

            printf("Reading completed. File contains %d integers!\n", count);
            printf("Choose the sorting algorithm:\n");
            printf("1: Bubble sort\n");
            printf("2: Insertion sort\n");
            printf("3: Merge sort\n");

            scanf("%d", &algorithmId);

            switch (algorithmId) {
                case 1:
                    bubbleSort(pointers, count);
                    printf("Sorting with bubbleSort...\n");
                    break;
                case 2:
                    insertionSort(pointers, count);
                    printf("Sorting with insertionSort...\n");
                    break;
                case 3:
                    mergeSort(pointers, count);
                    printf("Sorting with mergeSort...\n");
                    break;
                case -1:
                    return EXIT_SUCCESS;
                default:
                    printf("This was not a valid choice.\n");
                    return EXIT_FAILURE;
            }

            printf("The list is now sorted.\n");
            printf("Initial array:\n"); //print an error message


            for (int i = 0; i < count; i++) {
                printf("%d ", data[i]);
            }
            printf("\n");


            printf("Sorted array:\n"); //print an error message

            for (int i = 0; i < count; i++) {
                printf("%d ", *pointers[i]);
            }
            printf("\n");


            do {
                printf("Enter a number to search for (0 for exit):\n");
                scanf("%d", &numberToSearch);
                if (numberToSearch != 0) {

                    binarySearch(pointers, data, count, numberToSearch);

                }
            } while (numberToSearch != 0);
        }
    }

    free (data);
    free (pointers);

    return EXIT_SUCCESS;
}