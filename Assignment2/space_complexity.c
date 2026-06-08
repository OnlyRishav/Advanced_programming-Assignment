#include <stdio.h>
#include <stdlib.h>

void constant_space(int arr[], int size)
{
    int i;
    int sum = 0;

    for(i = 0; i < size; i++)
    {
        sum = sum + arr[i];
    }

    printf("  sum = %d\n", sum);
    printf("  extra variables used = 2 (i and sum)\n");
    printf("  no matter how big the array is, we only use 2 extra variables\n");
    printf("  so space complexity is O(1)\n");
}

void linear_space(int arr[], int size)
{
    int i;
    int *copy;

    copy = (int*)malloc(size * sizeof(int));

    for(i = 0; i < size; i++)
    {
        copy[i] = arr[i];
    }

    printf("  copied %d elements into new array\n", size);
    printf("  extra memory used = %d integers\n", size);
    printf("  memory grows as input size grows\n");
    printf("  so space complexity is O(n)\n");

    free(copy);
}

void quadratic_space(int size)
{
    int i, j;
    int **matrix;

    matrix = (int**)malloc(size * sizeof(int*));

    for(i = 0; i < size; i++)
    {
        matrix[i] = (int*)malloc(size * sizeof(int));
    }

    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            matrix[i][j] = i + j;
        }
    }

    printf("  created a %d x %d matrix\n", size, size);
    printf("  total cells = %d x %d = %d\n", size, size, size * size);
    printf("  memory grows as n squared when input size grows\n");
    printf("  so space complexity is O(n2)\n");

    for(i = 0; i < size; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int main()
{
    int sizes[4];
    sizes[0] = 4;
    sizes[1] = 8;
    sizes[2] = 16;
    sizes[3] = 32;

    int s;
    int i;

    printf("==============================================\n");
    printf("       Space Complexity Analysis Program      \n");
    printf("==============================================\n\n");

    printf("Space complexity means how much EXTRA MEMORY\n");
    printf("a program needs as the input size grows.\n\n");

    printf("We will test three types:\n");
    printf("  O(1)  - constant space  - always uses same amount of memory\n");
    printf("  O(n)  - linear space    - memory grows same as input\n");
    printf("  O(n2) - quadratic space - memory grows as n squared\n");
    printf("\n");

    for(s = 0; s < 4; s++)
    {
        int n = sizes[s];

        int *arr = (int*)malloc(n * sizeof(int));

        for(i = 0; i < n; i++)
        {
            arr[i] = i + 1;
        }

        printf("----------------------------------------------\n");
        printf("Input size n = %d\n", n);
        printf("----------------------------------------------\n\n");

        printf("[1] O(1) Constant Space  (just sum the array)\n");
        constant_space(arr, n);
        printf("\n");

        printf("[2] O(n) Linear Space  (make a copy of the array)\n");
        linear_space(arr, n);
        printf("  memory used = %d x 4 bytes = %d bytes\n", n, n * 4);
        printf("\n");

        printf("[3] O(n2) Quadratic Space  (make a n x n matrix)\n");
        quadratic_space(n);
        printf("  memory used = %d x %d x 4 bytes = %d bytes\n", n, n, n * n * 4);
        printf("\n");

        free(arr);
    }

    printf("==============================================\n");
    printf("Summary Table\n");
    printf("==============================================\n\n");

    printf("%-6s  %-15s  %-15s  %-15s\n",
           "n", "O(1) bytes", "O(n) bytes", "O(n2) bytes");
    printf("--------------------------------------------------\n");

    for(s = 0; s < 4; s++)
    {
        int n = sizes[s];
        int o1  = 8;
        int on  = n * 4;
        int on2 = n * n * 4;

        printf("%-6d  %-15d  %-15d  %-15d\n", n, o1, on, on2);
    }

    printf("\n");
    printf("==============================================\n");
    printf("What we can see:\n");
    printf("==============================================\n\n");
    printf("O(1)  -> memory stays at 8 bytes (just 2 int variables)\n");
    printf("O(n)  -> memory doubles when n doubles\n");
    printf("O(n2) -> memory goes up 4 times when n doubles\n");
    printf("\n");
    printf("This is same pattern as time complexity but\n");
    printf("here we are counting MEMORY not TIME.\n");
    printf("\n");

    return 0;
}
