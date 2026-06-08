#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void constant_time(int arr[], int size)
{
    int x = arr[0];
    x = x + 1;
}

void linear_time(int arr[], int size)
{
    int i;
    int sum = 0;
    for(i = 0; i < size; i++)
    {
        sum = sum + arr[i];
    }
}

void quadratic_time(int arr[], int size)
{
    int i, j;
    int count = 0;
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            count = count + 1;
        }
    }
}

int main()
{
    int sizes[5];
    sizes[0] = 1000;
    sizes[1] = 2000;
    sizes[2] = 4000;
    sizes[3] = 8000;
    sizes[4] = 16000;

    int s;
    int i;

    printf("==============================================\n");
    printf("       Time Complexity Analysis Program       \n");
    printf("==============================================\n\n");

    printf("What this program does:\n");
    printf("  O(1)  - constant time  - does not depend on input size\n");
    printf("  O(n)  - linear time    - grows with input size\n");
    printf("  O(n2) - quadratic time - grows very fast with input size\n");
    printf("\n");

    printf("%-10s  %-20s  %-20s  %-20s\n",
           "Size", "O(1) time (ns)", "O(n) time (ns)", "O(n2) time (ns)");
    printf("----------------------------------------------------------------------\n");

    for(s = 0; s < 5; s++)
    {
        int n = sizes[s];

        int *arr = (int*)malloc(n * sizeof(int));

        for(i = 0; i < n; i++)
        {
            arr[i] = i + 1;
        }

        clock_t start, end;
        long time_o1, time_on, time_on2;

        start = clock();
        constant_time(arr, n);
        end = clock();
        time_o1 = (long)(end - start);

        start = clock();
        linear_time(arr, n);
        end = clock();
        time_on = (long)(end - start);

        start = clock();
        quadratic_time(arr, n);
        end = clock();
        time_on2 = (long)(end - start);

        printf("%-10d  %-20ld  %-20ld  %-20ld\n",
               n, time_o1, time_on, time_on2);

        free(arr);
    }

    printf("\n");
    printf("==============================================\n");
    printf("What we can see from the results:\n");
    printf("==============================================\n");
    printf("\n");
    printf("O(1)  -> time stays almost same no matter what size\n");
    printf("O(n)  -> time increases as size increases\n");
    printf("O(n2) -> time increases a lot when size doubles\n");
    printf("\n");
    printf("For example if size goes from 1000 to 2000 (2x bigger):\n");
    printf("  O(1)  = same time\n");
    printf("  O(n)  = roughly 2x more time\n");
    printf("  O(n2) = roughly 4x more time\n");
    printf("\n");

    return 0;
}
