#ifndef _HEAPSORT_H
#define _HEAPSORT_H
#include <vector>

void heapify(std::vector<int>& array, int N, int i){
    int largest {i};
    int l {2 * i + 1};
    int r {2 * i + 2};

    if(l < N && array[l] > array[largest])
        largest = l;

    if(r < N && array[r] > array[largest])
        largest = r;
    
    if(largest != i){
        std::swap(array[i], array[largest]);
        heapify(array, N, largest);
    }
}

std::vector<int> heapSort(std::vector<int>& array, int N){
    for(int i = N / 2 - 1; i >= 0; i--)
        heapify(array, N, i);

    for(int i = N - 1; i > 0; i--){
        std::swap(array[0], array[i]);
        heapify(array, i , 0);
    }

    return array;
}


#endif