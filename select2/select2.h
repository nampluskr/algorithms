#pragma once

// Brute Force O(N)
int bruteForceSelect(int arr[], int low, int high, int k);
int insertionSelect(int arr[], int low, int high, int k);

// Quick Select O(N)
int quickSelectLomuto(int arr[], int low, int high, int k);
int quickSelectLomutoIter(int arr[], int low, int high, int k);

int quickSelectHoare(int arr[], int low, int high, int k);
int quickSelectHoareIter(int arr[], int low, int high, int k);

int medianSelect(int arr[], int low, int high);

// Heap Select O(N)
int heapSelect(int arr[], int low, int high, int k);
