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

        printf("Sorting with bubbleSort...\n");

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
            printf("Sorting with insertionSort...\n");


    for (int i = 1; i < size; i++) {
        int *value = pointers[i];
        int j;
        for (j = i; j > 0 && *value < *pointers[j - 1]; j--) {
            pointers[j] = pointers[j - 1];
        }
        pointers[j] = value;
    }
}

void merge(int *A, int a, int *B, int b, int *C) {
    int i, j, k;
    i = 0;
    j = 0;
    k = 0;
    while (i < a && j < b) {
        if (A[i] <= B[j]) {
            C[k] = A[i];
            i++;
            k++;
        }
        else {
            /* copy B[j] to C[k] and move the pointer j and k forward */
            C[k] = B[j];
            j++;
            k++;
        }
    }
    /* move the remaining elements in A into C */
    while (i < a) {
        C[k] = A[i];
        i++;
        k++;
    }
    /* move the remaining elements in B into C */
    while (j < b) {
        C[k] = B[j];
        j++;
        k++;
    }
}


void mergeSort(int *A, int n) {
    int i;
    int *A1, *A2;
    int n1, n2;

    if (n < 2)
        return;   /* the array is sorted when n=1.*/

    /* divide A into two array A1 and A2 */
    n1 = n / 2;   /* the number of elements in A1 */
    n2 = n - n1;  /* the number of elements in A2 */
    A1 = (int *) malloc(sizeof(int) * n1);
    A2 = (int *) malloc(sizeof(int) * n2);

    /* move the first n/2 elements to A1 */
    for (i = 0; i < n1; i++) {
        A1[i] = A[i];
    }
    /* move the rest to A2 */
    for (i = 0; i < n2; i++) {
        A2[i] = A[i + n1];
    }
    /* recursive call */
    mergeSort(A1, n1);
    mergeSort(A2, n2);

    /* conquer */
    merge(A1, n1, A2, n2, A);
    free(A1);
    free(A2);
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
                    break;
                case 2:
                    insertionSort(pointers, count);
                    break;
                case 3:
                    mergeSort(data, count);
                    break;
                case -1:
                    return EXIT_SUCCESS;
                default:
                    printf("Enter valid option(1,2,3). To exit, enter -1");
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

    return EXIT_SUCCESS;
}