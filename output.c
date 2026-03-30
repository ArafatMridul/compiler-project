#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

static int binary_search(int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

static void array_sort_int(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + 1 < n - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}

static int array_find_int(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

static void array_map_int(int arr[], int n, int (*op)(int)) {
    for (int i = 0; i < n; i++) {
        arr[i] = op(arr[i]);
    }
}

static int array_filter_int(int arr[], int n, int (*pred)(int)) {
    int write_idx = 0;
    for (int i = 0; i < n; i++) {
        if (pred(arr[i])) {
            arr[write_idx++] = arr[i];
        }
    }
    return write_idx;
}

static int array_reduce_int(int arr[], int n, int (*op)(int, int), int init) {
    int acc = init;
    for (int i = 0; i < n; i++) {
        acc = op(acc, arr[i]);
    }
    return acc;
}


int add(int a, int b) {
    return a + b;
}

int square(int x) {
    return x * x;
}

int is_even(int x) {
    return 1 - x % 2;
}

int main() {
    int arr[6] = {5, 2, 9, 1, 4, 6};
    array_sort_int(arr, 6);
    int idx = array_find_int(arr, 6, 4);
    array_map_int(arr, 6, square);
    int sum = array_reduce_int(arr, 6, add, 0);
    int kept = array_filter_int(arr, 6, is_even);
    printf("idx=%d sum=%d kept=%d first=%d\n", idx, sum, kept, arr[0]);
}
