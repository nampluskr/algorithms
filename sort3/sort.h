#pragma once

#include <cstdio>

void swap(int&a, int&b) { int temp = a; a = b; b = temp; }
int min(int a, int b) { return (a < b)? a: b; }
int max(int a, int b) { return (a < b)? b: a; }

// Strategy Interface
struct SortingMethod {
    virtual ~SortingMethod() = default; // or {}

    virtual void sort(int arr[], int low, int high) = 0;
};

// Context Class
struct Sorting {
    SortingMethod* method;

    void setSortingMethod(SortingMethod* method) { this->method = method; }
    void sortArray(int arr[], int low, int high) { method->sort(arr, low, high); }
    void printArray(int arr[], int low, int high) {
        printf(">> ");
        for (int i = low; i < high; i++)
            printf("%d, ", arr[i]);
        printf("%d\n", arr[high]);
    }
};

// Concrete Stretegies
struct BubbleSort: SortingMethod {
    void sort(int arr[], int low, int high) override {
        bool isSwapped;
        for (int i = high; i > low ; i--) {
            isSwapped = false;
            for (int j = low; j < i; j++) {
                if (arr[j] > arr[j + 1])
                    swap(arr[j], arr[j + 1]);
                    isSwapped = true;
            }
            if (!isSwapped) break;
        }
    }
};

struct SelectionSort: SortingMethod {
    void sort(int arr[], int low, int high) override {
        for (int i = low; i < high; i++) {
            int minIndex = i;
            for (int j = i + 1; j <= high; j++)
                if (arr[j] < arr[minIndex])
                    minIndex = j;
            if (minIndex != i) swap(arr[minIndex], arr[i]);
        }
    }
};

struct InsertionSort: SortingMethod {
    void sort(int arr[], int low, int high) override {
        for (int i = low + 1; i <= high; i++) {
            int key = arr[i];
            int j;
            for (j = i - 1; j >= low && arr[j] > key; j--)
                arr[j + 1] = arr[j];
            arr[j + 1] = key;
        }
    }
};

// Interface
enum PARTITION { LOMUTO, HOARE };
struct pii { int high, low; };

struct Partition {
    virtual ~Partition() = default;
    virtual pii partition(int arr[], int low, int high) = 0;
};

struct LomutoPartition: Partition {
    pii partition(int arr[], int low, int high) override {
        swap(arr[(low + high) / 2], arr[high]);
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot)
                swap(arr[++i], arr[j]);
        }
        swap(arr[++i], arr[high]);
        return { i - 1, i + 1 };    // default: i
    }
};

struct HoarePartition: Partition {
    pii partition(int arr[], int low, int high) override {
        int pivot = arr[(low + high) / 2];  // default
        int i = low - 1, j = high + 1;

        while (true) {
            do i++; while (arr[i] < pivot);
            do j--; while (arr[j] > pivot);

            if (i < j) swap(arr[i], arr[j]);
            else break;
        }
        return { j, j + 1 };    // default: j
    }
};

struct QuickSort: SortingMethod {
    Partition* selected;
    QuickSort(PARTITION name) { 
        if (name == LOMUTO) selected = new LomutoPartition();
        else if (name == HOARE) selected = new HoarePartition();
    }
    ~QuickSort() { delete selected; }

    void sort(int arr[], int low, int high) override {
        if (high <= low) return;

        pii pivotIndex = selected->partition(arr, low, high);
        sort(arr, low, pivotIndex.high);
        sort(arr, pivotIndex.low, high);
    }
};

struct MergeSort: SortingMethod {
    void merge(int arr[], int low, int mid, int high) {
        int n1 = mid - low + 1;
        int n2 = high - mid;
        int arr1[n1], arr2[n2];

        for (int i = 0; i < n1; i++) arr1[i] = arr[low + i];
        for (int j = 0; j < n2; j++) arr2[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = low;
        while (i < n1 && j < n2) {
            if (arr1[i] <= arr2[j]) arr[k] = arr1[i++];
            else arr[k] = arr2[j++];
            k++;
        }
        while (i < n1) arr[k++] = arr1[i++];
        while (j < n2) arr[k++] = arr2[j++];
    }   

    void sort(int arr[], int low, int high) override {
        if (high <= low) return;

        int mid = low + (high - low) / 2;
        sort(arr, low, mid);
        sort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
};