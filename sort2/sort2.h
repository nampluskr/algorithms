#pragma once

void printArray(int arr[], int low, int high);

// Elementary Sorting Algorithms
void bubbleSort(int arr[], int low, int high);
void bubbleSortRecursive(int arr[], int low, int high);
void bubbleSortOptimized(int arr[], int low, int high);
void cocktailSort(int arr[], int low, int high);
void combSort(int arr[], int low, int high);

void selectionSort(int arr[], int low, int high);

void insertionSort(int arr[], int low, int high);
void binaryInsertionSort(int arr[], int low, int high);
void shellSort(int arr[], int low, int high);
void shellSortKnuth(int arr[], int low, int high);

void cycleSort(int arr[], int low, int high);

// Efficient and Fast Sorting Algorithms
void quickSortLomuto(int arr[], int low, int high);
void quickSortHoare(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);

void mergeSort(int arr[], int low, int high);
void mergeSortBottomUp(int arr[], int low, int high);
void hybridSort(int arr[], int low, int high, int threshold);

void heapSort(int arr[], int low, int high);

// Linear Sorting Algorithms
void bucketSort(int arr[], int low, int high);
void countingSort(int arr[], int low, int high);
void radixSort10(int arr[], int low, int high);
void radixSort256(int arr[], int low, int high);