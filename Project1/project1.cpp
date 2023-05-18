/*
 * CSC-301
 * project1.cpp
 * Fall 2022
 * 
 * Author: Shrey Agrawal
 * Date: Due 02/20/23
 * 
 */

#include "project1.hpp"
#include <string>
#include <iostream>

using namespace std;

/*
 * selectionSort
 * Input: an instance of a vector class dynamic array holding values with data type double
 * Output: no output. It internally sorts the array.
 * The function is an implementation of the selectionSort algorithm learnt in class.
 * It searches an array, finds the smallest element in the array, 
 * and swaps it with the index of the first element in the unsorted part of the array.
 * 
 */
void selectionSort(vector<double> &arrayToSort) {

    double tmp;

    for(int i = 0; i < size(arrayToSort);i++){
        int min = i;
        for (int j = i; j < size(arrayToSort); j++){
            if (arrayToSort[min] > arrayToSort[j]){
                min = j;
            };
        }
        tmp = arrayToSort[i];
        arrayToSort[i] = arrayToSort[min];
        arrayToSort[min] = tmp;
    }
    return;
}

/*
 * insertionSort
 * Input: an instance of a vector class dynamic array holding values with data type double
 * Output: no output. It internally sorts the array.
 * The function is an implementation of the insertionSort algorithm learnt in class.
 * It finds the first element in the unsorted part of the array, and makes swaps as
 * neccesary to insert the element in the right place in the sorted part of the array.
 */
void insertionSort(vector<double> &arrayToSort) {
    double tmp;
    //unsorted part of array
    for (int i = 1; i<size(arrayToSort); i++){
        //sorted part of array
        for(int j = 0; j<i; j++){
            if (arrayToSort[i] < arrayToSort[j]){
                tmp = arrayToSort[i];
                arrayToSort[i] = arrayToSort[j];
                arrayToSort[j] = tmp;
            }
        }
    }
    return;
}

/*
 * bubbleSort
 * Input: an instance of a vector class dynamic array holding values with data type double
 * Output: no output. It internally sorts the array.
 * The function is an implementation of the bubbleSort algorithm learnt in class.
 * It compares adjacent elements in a list and swaps them if they are in the wrong order. 
 * The algorithm repeatedly iterates over the list, comparing each adjacent pair of elements,
 * and swapping them if they are in the wrong order. This repeats until no more swaps 
 * occur in an iteration, indicating that the list is sorted, and the algorithm terminates.
 */
void bubbleSort(vector<double> &arrayToSort) {

    bool bubble = true;
    double tmp;

    while(bubble){
        bubble = false;
        for (int i = 0; i<size(arrayToSort)-1;i++){
            if(arrayToSort[i]>arrayToSort[i+1]){
                tmp = arrayToSort[i];
                arrayToSort[i] = arrayToSort[i+1];
                arrayToSort[i+1] = tmp;
                bubble = true;
            }
        }
    }

    return;
}

/*
* mergeSortHelper
 * Input: the unsorted array from the previous function (which gets overwritten),
 * the left subarray, the right subarray. All of them are an instance
 * of a vector class dynamic array holding values with data type double.
 * Output: sorted array
 * The function iterates through both left and right subarrays
 * comparing the elements at the current indices. The smaller element 
 * is added to arrayToSort, and that index is incremented. Once one of 
 * the sub-arrays has been fully copied, the function adds the remaining 
 * elements from the other sub-array to arrayToSort. 
 * 
*/

void mergeSortHelper(vector<double> &arrayToSort, vector<double> &left, vector<double> &right){
    int i = 0, j = 0, k = 0;
    while (i < size(left) && j < size(right)) {
        if (left[i] <= right[j]) {
            arrayToSort[k] = left[i];
            i++;
        } else {
            arrayToSort[k] = right[j];
            j++;
        }
        k++;
    }
    //copy over the rest of the left subarray if it was bigger than the right subarray
    while (i < size(left)) {
        arrayToSort[k] = left[i];
        i++;
        k++;
    }
    //copy over the rest of the right subarray if it was bigger than the left subarray
    while (j < size(right)) {
        arrayToSort[k] = right[j];
        j++;
        k++;
    }
}


/*
 * mergeSort
 * Input: an instance of a vector class dynamic array holding values with data type double
 * Output: subarray's until each subarray is size 1, then continued by mergeSortHelper function
 * Divide and conquer approach where the array is divided into 2 halves, until
 * each subarray has only 1 element. The left side is divided first until the
 * base case, and then the right side is divided until the base case. After this,
 * the mergeSortHelper function is called (defined above) which does the comparisions,
 * merges accordingly, to finally create a sorted array.
 */
void mergeSort(vector<double> &arrayToSort) {
    int s = size(arrayToSort);
    int mid = s/2;

    // to check if only 1 or less elements is left in the array, and exit
    if (s<=1){
        return;
    }

    //creating the left subarray containing the start to mid elements:
    vector <double> left(mid);

    //creating the right subarray containing the mid to the end elements:
    vector <double> right(s-mid);

    //populating the left subarray with the elements:
    for (int i = 0; i < mid; i++) {
        left[i] = arrayToSort[i];
    }

    //populating the right subarray with the elements:
    for (int i = mid; i < s; i++) {
        right[i - mid] = arrayToSort[i];
    }

    //recursively creating all the left subarrays until we break when only 1 element in each subarray
    mergeSort(left);
    //after the left subarray is of size 1, we repeat for right subarray:
    mergeSort(right);
    
    //calling the merge function to start working up, and directly change the input array to be updated
    mergeSortHelper(arrayToSort, left, right);

}



/*
 * quickSortHelper
 * 
 * Note that i is inclusive (i.e., is the first element of subarray).
 * Note that j is not inclusive (i.e., off the end of the subarray).
 * 
 * Input: array to sort, the first index of the array, and the size of the array
 * Output: no output. the array is sorted internally and updated
 * This function is a divide and conquer approach to sort an unsorted array.
 * The function work by dividing the input array into two subarrays, with 
 * elements in the left subarray being less than or equal to the pivot 
 * element and elements in the right subarray being greater than the pivot element. 
 * The function in the end swaps elements within the array until it is divided 
 * and then swaps the pivot element with the last element of the left subarray. 
 * It then calls itself recursively on the left and right subarrays to sort them, 
 * until all subarrays have one or less elements.
 * 
 */
void quickSortHelper(vector<double> &arrayToSort, int i, int j) {
    double tmp;
    double tmp2;
    // Break if the selected section of the array has one or less elements,
    //since in that case it is already sorted.
    if (j - i <= 1) {
        return;
    }

    // Lets choose our pivot in the array to be the first element everytime.
    double pivot = arrayToSort[i];
    int left = i;
    int right = j - 1;

    // Go through the subarray from start to end and also backwards. 
    while (left <= right) {
        while (left <= right && arrayToSort[left] <= pivot) {
            left++;
        }
        while (left <= right && arrayToSort[right] > pivot) {
            right--;
        }
        //when done scanning the subarray, swap the values that are out of place.
        if (left < right) {
            tmp = arrayToSort[left];
            arrayToSort[left] = arrayToSort[right];
            arrayToSort[right] = tmp;
        }
    }

    // Swap the pivot value with the value at the right index.
    tmp2 = arrayToSort[i];
    arrayToSort[i] = arrayToSort[right];
    arrayToSort[right] = tmp2;

    // Recursively call the function with updated indexes to 
    // sort the left and right subarrays.
    quickSortHelper(arrayToSort, i, right);
    quickSortHelper(arrayToSort, right + 1, j);
}

/*
 * quickSort
 * Input: an instance of a vector class dynamic array holding values with data type double
 * Output: no output. It calls the quickSortHelper function
 * This function calls the quickSortHelper function passing it the array to sort,
 * the first index of the array, and the size of the array as arguments
 */
void quickSort(vector<double> &arrayToSort) {
    quickSortHelper(arrayToSort, 0, arrayToSort.size());
    return;
}