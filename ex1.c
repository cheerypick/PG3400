#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int *data, int size) {

    int i, j, temp;

    size = size - 1;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size - i; j++) {
            if (data[j] > data[j + 1]) {
                temp = data[j + 1];
                data[j + 1] = data[j];
                data[j] = temp;
            }

        }

    }

}

void insertionSort(int *data, int size) {

    for (int i = 1; i < size; i++) {
        int value = data[i];
        int j;
        for (j = i; j > 0 && value < data[j - 1]; j--) {
            data[j] = data[j - 1];
        }
        data[j] = value;
    }

}

void merge (int *A, int a, int *B, int b, int *C)
{
    int i,j,k;
    i = 0;
    j = 0;
    k = 0;
    while (i < a && j < b) {
        if (A[i] <= B[j]) {
            /* copy A[i] to C[k] and move the pointer i and k forward */
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
        C[k]= A[i];
        i++;
        k++;
    }
    /* move the remaining elements in B into C */
    while (j < b)  {
        C[k]= B[j];
        j++;
        k++;
    }
}


void mergeSort(int *A, int n)
{
    int i;
    int *A1, *A2;
    int n1, n2;

    if (n < 2)
        return;   /* the array is sorted when n=1.*/

    /* divide A into two array A1 and A2 */
    n1 = n / 2;   /* the number of elements in A1 */
    n2 = n - n1;  /* the number of elements in A2 */
    A1 = (int*)malloc(sizeof(int) * n1);
    A2 = (int*)malloc(sizeof(int) * n2);

    /* move the first n/2 elements to A1 */
    for (i =0; i < n1; i++) {
        A1[i] = A[i];
    }
    /* move the rest to A2 */
    for (i = 0; i < n2; i++) {
        A2[i] = A[i+n1];
    }
    /* recursive call */
    mergeSort(A1, n1);
    mergeSort(A2, n2);

    /* conquer */
    merge(A1, n1, A2, n2, A);
    free(A1);
    free(A2);
}

int binarySearch(int *array, int length, int key) {
    int first, last, middle;

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
        return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {


    int count = 0;
    int numberToSearch, algorithmId;
    int *data = NULL;
    int *temp = NULL;


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

            printf("Reading completed. File contains %d integers!\n", count);
            printf("Choose the sorting algorithm:\n");
            printf("1: Bubble sort\n");
            printf("2: Insertion sort\n");
            printf("3: Merge sort\n");

            scanf("%d", &algorithmId);

            switch (algorithmId) {
                case 1:
                    insertionSort(data, count);
                    break;
                case 2:
                    bubbleSort(data, count);
                    break;
                case 3:
                    mergeSort(data, count);
                    break;
                case -1:
                    return EXIT_SUCCESS;
                default:
                    printf("enter choice as 1 or 2 or to exit enter -1");
            }

            printf("The list is now sorted!\n");

            for (int i = 0; i < count; i++) {
                printf("%d\n", data[i]);
            }

            do {
                printf("Enter a number to search for:\n");
                scanf("%d", &numberToSearch);
                if ( numberToSearch != 0)
                {
                    binarySearch(data, count, numberToSearch);
                }
            } while (numberToSearch != 0);


        }

    }

    return EXIT_SUCCESS;
}


