#ifndef _BUBBLESORT_H
#define _BUBBLESORT_H
#include <vector>

std::vector<int> bubbleSort(std::vector<int> array, int n){
    bool swapped;
    std::vector<int> sortedArray = array;

    for(int i = 0; i < n - 1; i++){
        swapped = false;
        for(int j = 0; j < n - i - 1; j++){
            if(sortedArray[j] > sortedArray[j + 1]){
                std::swap(sortedArray[j], sortedArray[j + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }
    
    return sortedArray;
}

#endif