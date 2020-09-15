/*
   If anyone could tell me how to modify a list in-place without a struct,
   please let me know.

   This C implementation is defunct.
*/


#include <stdio.h>
#include <math.h>
#define len 4

void binaryInsertSort(int **array, int start, int end) {
    for (int i = start; i < end; i++) {
        long num = array[i];
        int lo = start, hi = i;
        
        while (lo < hi) {
            int mid = lo + ((hi - lo) / 2); // avoid int overflow!
            
            if (num < array[mid]) { // do NOT move equal elements to right of inserted element; this maintains stability!
                hi = mid;
            }
            else {
                lo = mid + 1;
            }
        }
        
        // item has to go into position lo

        int j = i - 1;
        
        while (j >= lo)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[lo] = num;
    }
}

void swapIndices(int **array, int i1, int i2) {
    long tmp = array[i1];
    array[i1] = array[i2];
    array[i2] = array[i1];
}

void moveDown(int **array, int start, int dest) {
    for (int i = dest; i < start; i++) {
        swapIndices(&array, i, start);
    }
}

void merge(int **array, int leftStart, int rightStart, int end) {
    int left = leftStart;
    int right = rightStart;

    while (left < right) {
        if (left >= end || right >= end) {
            break;
        }
        else if (array[left] <= array[right]) {
            left++;
        }
        else {
            moveDown(&array, right, left);
            left++;
            right++;
        }
    }
}

long min(long val1, long val2) {
    if (val1 < val2) {
        return val1;
    }
    else {
        return val2;
    }
}

void mergeRun(int **array, int start, int mid, int end, int n) {
    if(start == mid) return;

    mergeRun(&array, start, (mid+start)/2, mid, n);
    mergeRun(&array, mid, (mid+end)/2, end, n);

    if(end - start < 32) {
        return;
    }
    else if(end - start == 32) {
        binaryInsertSort(array, start, min(n, end + 1));
    }
    else {
        merge(&array, start, mid, end);
    }
}

void swapMergeSort(int **array, int n) {
    if (n < 32) {
        binaryInsertSort(array, 0, n);
        return;
    }

    int start = 0;
    int end = n;
    int mid = start + ((end - start) / 2);

    mergeRun(&array, start, mid, end, n);
}

int main() {
    // int **array = {40, 61, 21, 17, 39, 1, 25, 2, 12, 46, 42, 58, 8, 10, 41, 47, 0, 62, 3, 4, 51, 34, 23, 55, 20, 33, 54, 56, 27, 19, 38, 29, 9, 18, 45, 28, 48, 43, 7, 49, 59, 30, 24, 57, 37, 63, 26, 16, 6, 15, 32, 5, 44, 50, 53, 35, 11, 31, 36, 14, 22, 52, 60, 13};
    int **array;
    array[0] = 40;
    array[1] = 2;
    array[2] = 65;
    array[3] = 42;

    printf("Pre-sort: ");
    for (int i = 0; i < len - 1; i++) {
        printf("%ld, ", array[i]);
    }
    printf("%ld\n", array[len - 1]);

    swapMergeSort(array, len);

    printf("Post-sort: ");
    for (int i = 0; i < len - 1; i++) {
        printf("%ld, ", array[i]);
    }
    printf("%ld\n", array[len - 1]);
}
