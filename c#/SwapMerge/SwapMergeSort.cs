using System;

namespace SwapMerge
{
    static class Util<T> where T : IComparable<T> {
        public static void SwapIndices(T[] array, int i1, int i2) {
            T tmp = array[i1];
            array[i1] = array[i2];
            array[i2] = tmp;
        }

        public static void BinaryInsertSort(T[] array, int start, int end) {
            for (int i = start; i < end; i++) {
                T num = array[i];
                int lo = start, hi = i;

                while (lo < hi) {
                    int mid = lo + ((hi - lo) / 2); // avoid int overflow!

                    if (num.CompareTo(array[mid]) < 0) { // do NOT move equal elements to right of inserted element; this maintains stability!
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
    }

    public static class SwapMergeSort<T> where T : IComparable<T> {
        private static void MoveDown(T[] array, int start, int dest) {
            for (int i = dest; i < start; i++) {
                Util<T>.SwapIndices(array, i, start);
            }
        }

        private static void Merge(T[] array, int leftStart, int rightStart, int end) {
            int left = leftStart;
            int right = rightStart;

            while (left < right) {
                if (left >= end || right >= end) {
                    break;
                }
                // else if (array[left] <= array[right]) {
                else if (array[left].CompareTo((T)array[right]) <= 0) {
                    left += 1;
                }
                else {
                    MoveDown(array, right, left);
                    left += 1;
                    right += 1;
                }
            }
        }

        private static void MergeRun(T[] array, int start, int mid, int end) {
            if(start == mid) return;

            MergeRun(array, start, (mid+start)/2, mid);
            MergeRun(array, mid, (mid+end)/2, end);

            if(end - start < 32) {
                return;
            }
            else if(end - start == 32) {
                Util<T>.BinaryInsertSort(array, start, Math.Min(array.Length, end + 1));
            }
            else {
                Merge(array, start, mid, end);
            }
        }

        public static void SwapMerge(T[] array) {
            if (array.Length < 32) {
                Util<T>.BinaryInsertSort(array, 0, array.Length);
                return;
            }

            int start = 0;
            int end = array.Length;
            int mid = start + ((end - start) / 2);

            MergeRun(array, start, mid, end);
        }
    }
}
