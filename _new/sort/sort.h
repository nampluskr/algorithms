#pragma once

inline void swap(int& a, int& b) { int temp = a; a = b; b = temp; }
inline int min(int a, int b) { return (a < b)? a: b; }
inline int max(int a, int b) { return (a < b)? b: a; }


// Bubble sort and its variations
void bubbleSortIter(int arr[], int n);
void bubbleSortRecur(int arr[], int n);
void bubbleSortOptimized(int arr[], int n);
void cocktailSort(int arr[], int n);
void combSort(int arr[], int n);


// Insertion sort and its variations
void insertionSort(int arr[], int n);
void hybridSort(int arr[], int n);
void binaryInsertionSort(int arr[], int n);
void shellSort(int arr[], int n);
void shellSortKnuth(int arr[], int n);


// Selection sort and its variations
void selectionSort(int arr[], int n);
// Selection Sort with Optimized Comparisons
// Heap Selection Sort
// Quick Selection


// Quick sort and its variations
// int lomutoPartition(int arr[], int low, int high);
// int hoarePartition(int arr[], int low, int high);
// void lomutoQuickSortRecur(int arr[], int low, int high);
// void hoareQuickSortRecur(int arr[], int low, int high);
void lomutoQuickSort(int arr[], int n);
void hoareQuickSort(int arr[], int n);

int MED3(int arr[], int low, int mid, int high);
int choosePivotIndex(int arr[], int low, int high);

// int medianOfFive(int arr[], int low, int high);
int medianOfMedians(int arr[], int low, int high);

// Merge sort and its variations
// void merge(int arr[], int low, int mid, int high);
// void mergeSortRecur(int arr[], int low, int high);
void mergeSort(int arr[], int n);   // Top-down
void bottomUpMergeSort(int arr[], int n);

// void naturalMergeSort(int arr[], int n);

// Linear Sorting Algorithms
void countingSort(int arr[], int n, int maxNumber);
void radixSort10(int arr[], int n);
void radixSort256(int arr[], int n);
