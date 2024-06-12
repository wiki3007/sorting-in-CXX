#ifndef _MERGESORT_H
#define _MERGESORT_H
#include <vector>

void merge(std::vector<int>& array, int const left, int const mid, int const right){
   int const subArrayOne = mid - left + 1;
   int const subArrayTwo = right - mid;

   std::vector<int> leftArray(subArrayOne);
   std::vector<int> rightArray(subArrayTwo);

   for(int i = 0; i < subArrayOne; i++){
        leftArray[i] = array[left + i];
   }

   for(int j = 0; j < subArrayTwo; j++){
        rightArray[j] = array[mid + 1 + j];
   }

   int indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0, indexOfMergedArray = left;

   while(indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo){
        if(leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]){
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }else{
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }

        indexOfMergedArray++;
   }

   while(indexOfSubArrayOne < subArrayOne){
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
   }

   while(indexOfSubArrayTwo < subArrayTwo){
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
   }

   std::vector<int>().swap(leftArray);
   std::vector<int>().swap(rightArray);
}

std::vector<int> mergeSort(std::vector<int>& array, int n){
    for(int currentSize = 1; currentSize <= n; currentSize = 2 * currentSize){
          for(int leftStart = 0; leftStart < n - 1; leftStart += 2 * currentSize){
               int mid = std::min(leftStart + currentSize - 1, n - 1);
               int rightEnd = std::min(leftStart + 2 * currentSize - 1, n - 1);

               merge(array, leftStart, mid, rightEnd);
          }
    }

    return array;
}


#endif