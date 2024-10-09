#pragma once

void printArray(int arr[], int low, int high);

int linearSearch(int arr[], int low, int high, int target);
int linearSearchRecur(int arr[], int low, int high, int target);
int sentinelSearch(int arr[], int low, int high, int target);
int tranpositionSearch(int arr[], int low, int high, int target);
int searchMoveToFront(int arr[], int low, int high, int target);

void insertionSort(int arr[], int low, int high);
int binarySearch(int arr[], int low, int high, int target);
int binarySearchRecur(int arr[], int low, int high, int target);

int lowerBound(int arr[], int low, int high, int target);
int lowerBoundRecur(int arr[], int low, int high, int target);
int upperBound(int arr[], int low, int high, int target);
int upperBoundRecur(int arr[], int low, int high, int target);