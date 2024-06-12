#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <time.h>
#include <chrono>
#include <sstream>
#include <tuple>
#include <processthreadsapi.h>
#include "bubblesort.h"
#include "quicksort.h"
#include "mergesort.h"
#include "heapsort.h"

TEST_CASE("Array {7, 0, 6, 2, 9, 8, 5, 3, 1, 4} to sort", "[vector]"){
    std::vector<int> testArray = {7, 0, 6, 2, 9, 8, 5, 3, 1, 4};
    std::vector<int> resultArray = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    SECTION("Using bubble sort to sort given array"){
        std::vector<int> sortedArray = bubbleSort(testArray, testArray.size());

        REQUIRE(sortedArray == resultArray);
    }

    SECTION("Using quick sort to sort given array"){
        std::vector<int> sortedArray = quickSort(testArray, 0, testArray.size() - 1, true);

        REQUIRE(sortedArray == resultArray);
    }

    SECTION("Using merge sort to sort given array"){
        std::vector<int> sortedArray = mergeSort(testArray, testArray.size());

        REQUIRE(sortedArray == resultArray);
    }

    SECTION("Using heap sort to sort given array"){
        std::vector<int> sortedArray = heapSort(testArray, testArray.size());

        REQUIRE(sortedArray == resultArray);
    }
}

TEST_CASE("Empty array", "[vector]"){
    std::vector<int> testArray = {};

    SECTION("Using bubble sort to sort empty array"){
        std::vector<int> sortedArray = bubbleSort(testArray, testArray.size());

        REQUIRE(sortedArray == testArray);
    }

    SECTION("Using quick sort to sort empty array"){
        std::vector<int> sortedArray = quickSort(testArray, 0, testArray.size() - 1, true);

        REQUIRE(sortedArray == testArray);
    }

    SECTION("Using merge sort to sort empty array"){
        std::vector<int> sortedArray = mergeSort(testArray, testArray.size());

        REQUIRE(sortedArray == testArray);
    }

    SECTION("Using heap sort to sort empty array"){
        std::vector<int> sortedArray = heapSort(testArray, testArray.size());

        REQUIRE(sortedArray == testArray);
    }
}

TEST_CASE("Sorted array", "[vector]"){
    std::vector<int> testArray = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    SECTION("Using bubble sort to sort sorted array"){
        std::vector<int> sortedArray = bubbleSort(testArray, testArray.size());

        REQUIRE(sortedArray == testArray);
    }

    SECTION("Using quick sort to sort sorted array"){
        std::vector<int> sortedArray = quickSort(testArray, 0, testArray.size() - 1, true);

        REQUIRE(sortedArray == testArray);
    }

    SECTION("Using merge sort to sort sorted array"){
        std::vector<int> sortedArray = mergeSort(testArray, testArray.size());

        REQUIRE(sortedArray == testArray);
    }

    SECTION("Using heap sort to sort sorted array"){
        std::vector<int> sortedArray = heapSort(testArray, testArray.size());

        REQUIRE(sortedArray == testArray);
    }
}

TEST_CASE("Sorted array in reverse order", "[vector]"){
    std::vector<int> testArray = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    std::vector<int> resultArray = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    SECTION("Using bubble sort to sort sorted array in reverse order"){
        std::vector<int> sortedArray = bubbleSort(testArray, testArray.size());

        REQUIRE(sortedArray == resultArray);
    }

    SECTION("Using quick sort to sort sorted array in reverse order"){
        std::vector<int> sortedArray = quickSort(testArray, 0, testArray.size() - 1, true);

        REQUIRE(sortedArray == resultArray);
    }

    SECTION("Using merge sort to sort sorted array in reverse order"){
        std::vector<int> sortedArray = mergeSort(testArray, testArray.size());

        REQUIRE(sortedArray == resultArray);
    }

    SECTION("Using heap sort to sort sorted array in reverse order"){
        std::vector<int> sortedArray = heapSort(testArray, testArray.size());

        REQUIRE(sortedArray == resultArray);
    }
}

auto to_num(const std::string& s){
    std::istringstream is(s);
    int n;
    bool good = (is >> std::ws >> n) && (is >> std::ws).eof();

    return std::make_tuple(n, good);
}

double getCpuTime(){
    FILETIME a, b, c, d;
    if(GetProcessTimes(GetCurrentProcess(), &a, &b, &c, &d) != 0){
        return
            (double)(d.dwLowDateTime |
            ((unsigned long long)d.dwHighDateTime << 32)) * 0.0000001;
    }else{
        return 0;
    }
}

int main(int argc, char* argv[]){
    int flag {-1};

    while(true){
        std::cout << "1. Sort array from file.\n";
        std::cout << "2. Do the unit tests.\n";
        std::cout << "3. Benchmark sorting algorithms.\n";
        std::cout << "4. Quit.\n\n";

        std::cin >> flag;

        if(flag == 1){
            std::vector<int> array, sortedArray;
            std::ifstream inf{"input.txt"};
            std::string line, filename{""};
            int n, sortFlag {-1};
            bool good;

            if(inf){
                while(std::getline(inf, line)){
                    try{
                        std::tie(n, good) = to_num(line);
                        if(!good){
                            throw(line);
                        }
                    }
                    catch(std::string wrongLine){
                        std::cout << "\nError: non-integer line " << line << " has occured in 'input.txt' file.\n";
                        return 1;
                    }

                    array.push_back(std::stoi(line));
                }
            }else{
                std::cout << "\n'input.txt' file doesn't exists!\n\n";
                continue;
            }

            inf.close();

            std::cout << "\n1. Sort array with bubble sort algorithm.\n";
            std::cout << "2. Sort array with quick sort algorithm.\n";
            std::cout << "3. Sort array with merge sort algorithm.\n";
            std::cout << "4. Sort array with heap sort algorithm.\n\n";

            std::cin >> sortFlag;

            if(sortFlag == 1){
                sortedArray = bubbleSort(array, array.size());
                filename = "outputBubbleSort.txt";
            }

            if(sortFlag == 2){
                sortedArray = quickSort(array, 0, array.size() - 1, true);
                filename = "outputQuickSort.txt";
            }

            if(sortFlag == 3){
                sortedArray = mergeSort(array, array.size());
                filename = "outputMergeSort.txt";
            }

            if(sortFlag == 4){
                sortedArray = heapSort(array, array.size());
                filename = "outputHeapSort.txt";
            }

            if(sortFlag != 1 && sortFlag != 2 && sortFlag != 3 && sortFlag != 4){
                std::cout << "Incorrect option!\n\n";
                continue;
            }

            std::ofstream outf{filename, std::ios::trunc};

            if(outf){
                for(int i = 0; i < sortedArray.size(); i++){
                    outf << sortedArray[i] << "\n";
                }
            } else{
                std::cout << "\nSomething wrong with creating " << filename << "\n\n";
                continue;
            }

            outf.close();
        }

        if(flag == 2){
            int result = Catch::Session().run(argc, argv);
        }

        if(flag == 3){
            int benchmarkFlag{-1}, caseFlag{-1};
            std::string filename;
            srand((unsigned) time(NULL));

            std::cout << "\n1. Benchmark bubble sort algorithm.\n";
            std::cout << "2. Benchmark quick sort algorithm.\n";
            std::cout << "3. Benchmark merge sort algorithm.\n";
            std::cout << "4. Benchmark heap sort algorithm.\n\n";

            std::cin >> benchmarkFlag;

            if(benchmarkFlag == 1){
                filename = "bubbleBenchmark.txt";

                std::ofstream outf{filename, std::ios::trunc};

                if(outf){
                    std::cout << "\n1. Best case (array is already sorted).\n";
                    std::cout << "2. Average case (array is unsorted ).\n";
                    std::cout << "3. Worst case (array is sorted in reverse order).\n";

                    std::cin >> caseFlag;

                    if(caseFlag == 1){
                        for(int i = 100000; i <= 10000000; i+=100000){
                            std::vector<int> array, sortedArray;
                            double cpuStart, cpuEnd;

                            for(int j = 0; j < i; j++){
                                array.push_back(j);
                            }

                            auto start = std::chrono::high_resolution_clock::now();
                            cpuStart = getCpuTime();
                            sortedArray = bubbleSort(array, array.size());
                            cpuEnd = getCpuTime();
                            auto stop = std::chrono::high_resolution_clock::now();

                            double cpuTimeTaken = (cpuEnd - cpuStart);
                            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                            std::cout << "\nFor i=" << i << "\n";
                            std::cout << "Execution time [ms]: " << duration.count() << "\n";
                            std::cout << "CPU execution time [s]: " << cpuTimeTaken << "\n\n";
                            outf << duration.count() << "," << cpuTimeTaken << "\n";
                        }
                    }

                    if(caseFlag == 2){
                        for(int i = 1000; i <= 50000; i+=1000){
                            std::vector<int> array, sortedArray;
                            double cpuStart, cpuEnd;

                            for(int j = 0; j < i; j++){
                                array.push_back(rand() % i);
                            }

                            auto start = std::chrono::high_resolution_clock::now();
                            cpuStart = getCpuTime();
                            sortedArray = bubbleSort(array, array.size());
                            cpuEnd = getCpuTime();
                            auto stop = std::chrono::high_resolution_clock::now();

                            double cpuTimeTaken = (cpuEnd - cpuStart);
                            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                            std::cout << "\nFor i=" << i << "\n";
                            std::cout << "Execution time [ms]: " << duration.count() << "\n";
                            std::cout << "CPU execution time [s]: " << cpuTimeTaken << "\n\n";
                            outf << duration.count() << "," << cpuTimeTaken << "\n";
                        }
                    }

                    if(caseFlag == 3){
                        for(int i = 1000; i <= 50000; i+=1000){
                            std::vector<int> array, sortedArray;
                            double cpuStart, cpuEnd;

                            for(int j = i - 1; j >= 0; j--){
                                array.push_back(j);
                            }

                            auto start = std::chrono::high_resolution_clock::now();
                            cpuStart = getCpuTime();
                            sortedArray = bubbleSort(array, array.size());
                            cpuEnd = getCpuTime();
                            auto stop = std::chrono::high_resolution_clock::now();

                            double cpuTimeTaken = (cpuEnd - cpuStart);
                            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                            std::cout << "\nFor i=" << i << "\n";
                            std::cout << "Execution time [ms]: " << duration.count() << "\n";
                            std::cout << "CPU execution time [s]: " << cpuTimeTaken << "\n\n";
                            outf << duration.count() << "," << cpuTimeTaken << "\n";
                        }
                    }

                    if(caseFlag != 1 && caseFlag != 2 && caseFlag != 3){
                        std::cout << "Incorrect option!\n\n";
                        continue;
                    }
                } else{
                    std::cout << "\nSomething wrong with creating " << filename << "\n\n";
                    continue;
                }

                outf.close();

                
            }

            if(benchmarkFlag == 2){
                filename = "quickBenchmark.txt";

                std::ofstream outf{filename, std::ios::trunc};

                if(outf){
                    std::cout << "\n1. Best case (array is already sorted).\n";
                    std::cout << "2. Average case (array is unsorted ).\n";
                    std::cout << "3. Worst case (array is sorted in reverse order).\n";

                    std::cin >> caseFlag;

                    if(caseFlag == 1){
                        for(int i = 1000; i <= 50000; i+=1000){
                            std::vector<int> array, sortedArray;
                            double cpuStart, cpuEnd;

                            for(int j = 0; j < i; j++){
                                array.push_back(j);
                            }

                            auto start = std::chrono::high_resolution_clock::now();
                            cpuStart = getCpuTime();
                            sortedArray = quickSort(array, 0, array.size() - 1, true);
                            cpuEnd = getCpuTime();
                            auto stop = std::chrono::high_resolution_clock::now();

                            double cpuTimeTaken = (cpuEnd - cpuStart);
                            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                            std::cout << "\nFor i=" << i << "\n";
                            std::cout << "Execution time [ms]: " << duration.count() << "\n";
                            std::cout << "CPU execution time [s]: " << cpuTimeTaken << "\n\n";
                            outf << duration.count() << "," << cpuTimeTaken << "\n";
                        }
                    }

                    if(caseFlag == 2){
                        for(int i = 1000; i <= 50000; i+=1000){
                            std::vector<int> array, sortedArray;
                            double cpuStart, cpuEnd;

                            for(int j = 0; j < i; j++){
                                array.push_back(rand() % i);
                            }

                            auto start = std::chrono::high_resolution_clock::now();
                            cpuStart = getCpuTime();
                            sortedArray = quickSort(array, 0, array.size() - 1, true);
                            cpuEnd = getCpuTime();
                            auto stop = std::chrono::high_resolution_clock::now();

                            double cpuTimeTaken = (cpuEnd - cpuStart);
                            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                            std::cout << "\nFor i=" << i << "\n";
                            std::cout << "Execution time [ms]: " << duration.count() << "\n";
                            std::cout << "CPU execution time [s]: " << cpuTimeTaken << "\n\n";
                            outf << duration.count() << "," << cpuTimeTaken << "\n";
                        }
                    }

                    if(caseFlag == 3){
                        for(int i = 1000; i <= 50000; i+=1000){
                            std::vector<int> array, sortedArray;
                            double cpuStart, cpuEnd;

                            for(int j = i - 1; j >= 0; j--){
                                array.push_back(j);
                            }

                            auto start = std::chrono::high_resolution_clock::now();
                            cpuStart = getCpuTime();
                            sortedArray = quickSort(array, 0, array.size() - 1, false);
                            cpuEnd = getCpuTime();
                            auto stop = std::chrono::high_resolution_clock::now();

                            double cpuTimeTaken = (cpuEnd - cpuStart);
                            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                            std::cout << "\nFor i=" << i << "\n";
                            std::cout << "Execution time [ms]: " << duration.count() << "\n";
                            std::cout << "CPU execution time [s]: " << cpuTimeTaken << "\n\n";
                            outf << duration.count() << "," << cpuTimeTaken << "\n";
                        }
                    }

                    if(caseFlag != 1 && caseFlag != 2 && caseFlag != 3){
                        std::cout << "Incorrect option!\n\n";
                        continue;
                    }
                } else{
                    std::cout << "\nSomething wrong with creating " << filename << "\n\n";
                    continue;
                }

                outf.close();
            }

            if(benchmarkFlag == 3){
                filename = "mergeBenchmark.txt";

                std::ofstream outf{filename, std::ios::trunc};

                if(outf){
                    std::cout << "\n1. Best case (array is already sorted).\n";
                    std::cout << "2. Average case (array is unsorted ).\n";
                    std::cout << "3. Worst case (array is sorted in reverse order).\n";

                    std::cin >> caseFlag;

                    if(caseFlag == 1){
                        for(int i = 100000; i <= 5000000; i+=100000){
                            std::vector<int> array, sortedArray;
                            double cpuStart, cpuEnd;

                            for(int j = 0; j < i; j++){
                                array.push_back(j);
                            }

                            auto start = std::chrono::high_resolution_clock::now();
                            cpuStart = getCpuTime();
                            sortedArray = mergeSort(array, array.size());
                            cpuEnd = getCpuTime();
                            auto stop = std::chrono::high_resolution_clock::now();

                            double cpuTimeTaken = (cpuEnd - cpuStart);
                            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                            std::cout << "\nFor i=" << i << "\n";
                            std::cout << "Execution time [ms]: " << duration.count() << "\n";
                            std::cout << "CPU execution time [s]: " << cpuTimeTaken << "\n\n";
                            outf << duration.count() << "," << cpuTimeTaken << "\n";
                        }
                    }

                    if(caseFlag == 2){
                        for(int i = 100000; i <= 5000000; i+=100000){
                            std::vector<int> array, sortedArray;
                            double cpuStart, cpuEnd;

                            for(int j = 0; j < i; j++){
                                array.push_back(rand() % i);
                            }

                            auto start = std::chrono::high_resolution_clock::now();
                            cpuStart = getCpuTime();
                            sortedArray = mergeSort(array, array.size());
                            cpuEnd = getCpuTime();
                            auto stop = std::chrono::high_resolution_clock::now();

                            double cpuTimeTaken = (cpuEnd - cpuStart);
                            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                            std::cout << "\nFor i=" << i << "\n";
                            std::cout << "Execution time [ms]: " << duration.count() << "\n";
                            std::cout << "CPU execution time [s]: " << cpuTimeTaken << "\n\n";
                            outf << duration.count() << "," << cpuTimeTaken << "\n";
                        }
                    }

                    if(caseFlag == 3){
                        for(int i = 100000; i <= 5000000; i+=100000){
                            std::vector<int> array, sortedArray;
                            double cpuStart, cpuEnd;

                            for(int j = i - 1; j >= 0; j--){
                                array.push_back(j);
                            }

                            auto start = std::chrono::high_resolution_clock::now();
                            cpuStart = getCpuTime();
                            sortedArray = mergeSort(array, array.size());
                            cpuEnd = getCpuTime();
                            auto stop = std::chrono::high_resolution_clock::now();

                            double cpuTimeTaken = (cpuEnd - cpuStart);
                            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                            std::cout << "\nFor i=" << i << "\n";
                            std::cout << "Execution time [ms]: " << duration.count() << "\n";
                            std::cout << "CPU execution time [s]: " << cpuTimeTaken << "\n\n";
                            outf << duration.count() << "," << cpuTimeTaken << "\n";
                        }
                    }

                    if(caseFlag != 1 && caseFlag != 2 && caseFlag != 3){
                        std::cout << "Incorrect option!\n\n";
                        continue;
                    }
                } else{
                    std::cout << "\nSomething wrong with creating " << filename << "\n\n";
                    continue;
                }

                outf.close();

                
            }

            if(benchmarkFlag == 4){
                filename = "heapBenchmark.txt";

                std::ofstream outf{filename, std::ios::trunc};

                if(outf){
                    std::cout << "\n1. Best case (array is already sorted).\n";
                    std::cout << "2. Average case (array is unsorted ).\n";
                    std::cout << "3. Worst case (array is sorted in reverse order).\n";

                    std::cin >> caseFlag;

                    if(caseFlag == 1){
                        for(int i = 100000; i <= 5000000; i+=100000){
                            std::vector<int> array, sortedArray;
                            double cpuStart, cpuEnd;

                            for(int j = 0; j < i; j++){
                                array.push_back(j);
                            }

                            auto start = std::chrono::high_resolution_clock::now();
                            cpuStart = getCpuTime();
                            sortedArray = heapSort(array, array.size());
                            cpuEnd = getCpuTime();
                            auto stop = std::chrono::high_resolution_clock::now();

                            double cpuTimeTaken = (cpuEnd - cpuStart);
                            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                            std::cout << "\nFor i=" << i << "\n";
                            std::cout << "Execution time [ms]: " << duration.count() << "\n";
                            std::cout << "CPU execution time [s]: " << cpuTimeTaken << "\n\n";
                            outf << duration.count() << "," << cpuTimeTaken << "\n";
                        }
                    }

                    if(caseFlag == 2){
                        for(int i = 100000; i <= 5000000; i+=100000){
                            std::vector<int> array, sortedArray;
                            double cpuStart, cpuEnd;

                            for(int j = 0; j < i; j++){
                                array.push_back(rand() % i);
                            }

                            auto start = std::chrono::high_resolution_clock::now();
                            cpuStart = getCpuTime();
                            sortedArray = heapSort(array, array.size());
                            cpuEnd = getCpuTime();
                            auto stop = std::chrono::high_resolution_clock::now();

                            double cpuTimeTaken = (cpuEnd - cpuStart);
                            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                            std::cout << "\nFor i=" << i << "\n";
                            std::cout << "Execution time [ms]: " << duration.count() << "\n";
                            std::cout << "CPU execution time [s]: " << cpuTimeTaken << "\n\n";
                            outf << duration.count() << "," << cpuTimeTaken << "\n";
                        }
                    }

                    if(caseFlag == 3){
                        for(int i = 100000; i <= 5000000; i+=100000){
                            std::vector<int> array, sortedArray;
                            double cpuStart, cpuEnd;

                            for(int j = i - 1; j >= 0; j--){
                                array.push_back(j);
                            }

                            auto start = std::chrono::high_resolution_clock::now();
                            cpuStart = getCpuTime();
                            sortedArray = heapSort(array, array.size());
                            cpuEnd = getCpuTime();
                            auto stop = std::chrono::high_resolution_clock::now();

                            double cpuTimeTaken = (cpuEnd - cpuStart);
                            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                            std::cout << "\nFor i=" << i << "\n";
                            std::cout << "Execution time [ms]: " << duration.count() << "\n";
                            std::cout << "CPU execution time [s]: " << cpuTimeTaken << "\n\n";
                            outf << duration.count() << "," << cpuTimeTaken << "\n";
                        }
                    }

                    if(caseFlag != 1 && caseFlag != 2 && caseFlag != 3){
                        std::cout << "Incorrect option!\n\n";
                        continue;
                    }
                } else{
                    std::cout << "\nSomething wrong with creating " << filename << "\n\n";
                    continue;
                }

                outf.close();


                
            }

            if(flag != 1 && flag != 2 && flag != 3 && flag != 4){
                std::cout << "Incorrect option!\n\n";
                continue;
            }
        }

        if(flag == 4){
            break;
        }

        if(flag != 1 && flag != 2 && flag != 3 && flag != 4){
            std::cout << "Incorrect option!\n\n";
        }
    }
    
    return 0;
}
