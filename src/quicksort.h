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

std::vector<int> quickSort(std::vector<int>& array, int low, int high, bool pivotType){
    if(low < high){
        if(pivotType){
            std::vector<int> stack(high - low + 1);
            int top = -1;

            stack.insert(stack.begin() + (++top), low);
            stack.insert(stack.begin() + (++top), high);

            while(top >= 0){
                high = stack[top--];
                low = stack[top --];

                int p = partition(array, low, high);

                if(p - 1 > low){
                    stack.insert(stack.begin() + (++top), low);
                    stack.insert(stack.begin() + (++top), p - 1);
                }

                if(p + 1 < high){
                    stack.insert(stack.begin() + (++top), p + 1);
                    stack.insert(stack.begin() + (++top), high);
                }
            }
        }else{
            std::vector<int> stack(high - low + 1);
            int top = -1;

            stack.insert(stack.begin() + (++top), low);
            stack.insert(stack.begin() + (++top), high);

            while(top >= 0){
                high = stack[top--];
                low = stack[top --];

                int p = high;

                if(p - 1 > low){
                    stack.insert(stack.begin() + (++top), low);
                    stack.insert(stack.begin() + (++top), p - 1);
                }

                if(p + 1 < high){
                    stack.insert(stack.begin() + (++top), p + 1);
                    stack.insert(stack.begin() + (++top), high);
                }
            }
        }
        
    }
    return array;
}



#endif