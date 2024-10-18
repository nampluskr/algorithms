inline void swap(int& a, int& b) { int temp = a; a = b; b = temp; }

int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int pivot_index = right;
    right--;

    while (1) {
        while (arr[left] < pivot) left++;
        while (arr[right] > pivot) right--;

        if (left >= right) break;
        else {
            swap(arr[left], arr[right]);
            left++;
        }
    }
    swap(arr[left], arr[pivot_index]);

    return left;
}

int main()
{
    int arr[] = { 6, 5, 9, 3, 4, 1, 2, 7, 8,};
    int n = 9;


    
    return 0;
}