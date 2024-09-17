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

