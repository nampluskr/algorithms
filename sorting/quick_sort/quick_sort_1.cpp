#include <cstdio>

/*
1. int arr[]: input -> arr
*/

void quickSort(int arr[], int first, int last)
{
    int pivot;
    int i;
    int j;
    int temp;

    if (first < last)
    {
        pivot = first;
        i = first;
        j = last;

        while (i < j)
        {
            while (arr[i] <= arr[pivot] && i < last)
            {
                i++;
            }
            while (arr[j] > arr[pivot])
            {
                j--;
            }
            if (i < j)
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        temp = arr[pivot];
        arr[pivot] = arr[j];
        arr[j] = temp;

        quickSort(arr, first, j - 1);
        quickSort(arr, j + 1, last);
    }
}

int arr[9] = { 7, 6, 9, 8, 3, 5, 4, 2, 1 };

void quickSelect(int first, int last, int k)
{
    int pivot;
    int i;
    int j;
    int temp;

    if (first < last)
    {
        pivot = first;
        i = first;
        j = last;

        while (i < j)
        {
            while (arr[i] <= arr[pivot] && i < last)
            {
                i++;
            }
            while (arr[j] > arr[pivot])
            {
                j--;
            }
            if (i < j)
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        temp = arr[pivot];
        arr[pivot] = arr[j];
        arr[j] = temp;

        if (k == pivot) return;
        else if (k < pivot) quickSelect(first, pivot - 1, k);
        else quickSelect(pivot + 1, last, k);
    }
}


void print(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int n = 9, k, kth;

    // quickSort(arr, 0, n - 1);
    // print(arr, n);

    k = 4;
    quickSelect(0, n - 1, k - 1);
    print(arr, n);
    printf("%dth: %d\n", k, arr[k - 1]);

    return 0;
}