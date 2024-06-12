#ifndef _QUICKSORT_H
#define _QUICKSORT_H
#include <vector>

int partition(std::vector<int>& array, int low, int high){
    int pivot = array[high];
    int i = {low - 1};

    for(int j {low}; j <= high - 1; j++){
        if(array[j] < pivot){
            i++;
            std::swap(array[i], array[j]);
        }
    }

    std::swap(array[i + 1], array[high]);

    return (i + 1);
}

std::vector<int> quickSort(std::vector<int>& array, int low, int high){
    if(low < high){
        int pivot = partition(array, low, high);

        quickSort(array, low, pivot - 1);
        quickSort(array, pivot + 1, high);

        
    }
    return array;
}



#endif