#include <stdio.h>
#include <math.h>
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


#define PI 3.14159

int add(int a, int b) {
    return (a + b);
}

int main() {
    int arr[5] = {1, 3, 5, 7, 9};
    int idx = binary_search(arr, 5, 7);
    printf("%d\n", idx);
}
