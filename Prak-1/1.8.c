#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_DIMS 5
#define EPS 0.0001

int total_size(int dims, int sizes[]) {
    int total = 1;
    int i;
    for (i = 0; i < dims; i++)
        total *= sizes[i];
    return total;
}

void print_indices(int index, int dims, int sizes[]) {
    int coords[MAX_DIMS];
    int i;
    for (i = dims - 1; i >= 0; i--) {
        coords[i] = index % sizes[i];
        index /= sizes[i];
    }
    printf("(");
    for (i = 0; i < dims; i++) {
        printf("%d", coords[i]);
        if (i < dims - 1) printf(", ");
    }
    printf(")");
}

void fill_array(float *array, int total) {
    int i;
    for (i = 0; i < total; i++)
        array[i] = (float)(rand() % 20);
}

void print_array(float *array, int total) {
    int i;
    printf("\nArray values:\n");
    for (i = 0; i < total; i++)
        printf("%.2f ", array[i]);
    printf("\n");
}

void find_value(float *array, int dims, int sizes[], float value) {
    int total = total_size(dims, sizes);
    int found = 0;
    int i;

    for (i = 0; i < total; i++) {
        if (fabs(array[i] - value) < EPS) {
            print_indices(i, dims, sizes);
            printf(" ");
            found = 1;
        }
    }

    if (!found)
        printf("Value not found.");

    printf("\n");
}

int main() {
    int dims, i;
    int sizes[MAX_DIMS];
    float *array;
    float value;

    srand((unsigned int)time(NULL));

    printf("MULTIDIMENSIONAL ARRAY PROGRAM\n");
    printf("------------------------------\n");

    printf("Enter number of dimensions (1-%d): ", MAX_DIMS);
    scanf("%d", &dims);

    if (dims < 1 || dims > MAX_DIMS)
        return 1;

    for (i = 0; i < dims; i++) {
        printf("Enter size of dimension %d: ", i + 1);
        scanf("%d", &sizes[i]);
        if (sizes[i] <= 0)
            return 1;
    }

    int total = total_size(dims, sizes);
    array = (float *)malloc(total * sizeof(float));
    if (array == NULL)
        return 1;

    fill_array(array, total);

    printf("Enter value to search (0-19): ");
    scanf("%f", &value);

    if (total > 0)
        array[0] = value;

    print_array(array, total);

    printf("Found at indices:\n");
    find_value(array, dims, sizes, value);

    free(array);
    return 0;
}
