#!/bin/bash

echo "=== compiling and running minHeap.c ==="
gcc -o minHeap minHeap.c
./minHeap

echo ""
echo "=== compiling and running heapSort.c ==="
gcc -o heapSort heapSort.c
./heapSort

echo ""
echo "=== compiling and running heapSortBenchmark.c ==="
gcc -O2 -o heapSortBenchmark heapSortBenchmark.c
./heapSortBenchmark

echo ""
echo "=== plotting heapsort_results.csv ==="
python3 plotHeapSort.py

echo ""
echo "=== done ==="