#r "SwapMerge/bin/Debug/netstandard2.0/SwapMerge.dll"

using System;
using SwapMerge;

void PrintArray(Array array) {
    // Console.WriteLine("[{0}]", string.Join(", ", array));
    foreach(var item in array)
        Console.Write(item.ToString() + " ");
    Console.WriteLine();
}

void ShuffleArray(Array array) {
    Random random = new Random();
    for (int i = 0; i < array.Length - 1; i++) {
        int newi = random.Next(array.Length);
        object tmp = array.GetValue(i);
        array.SetValue(array.GetValue(newi), i);
        array.SetValue(tmp, newi);
    }
}

int[] array = Enumerable.Range(1, 256).ToArray();
PrintArray(array);

ShuffleArray(array);
PrintArray(array);

SwapMergeSort<int>.SwapMerge(array);
PrintArray(array);
