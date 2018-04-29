//
//  main.cpp
//  sorting_algorithms
//
//  Created by Tuğba Özkal on 17.09.2017.
//  Copyright © 2017 Tuğba Özkal. All rights reserved.
//

#include <iostream>
#include <math.h>

using namespace std;

#define n 5
#define mn 8
#define mne 11


void swap(int *, int *);
int * bubble_sort(int[]);
int * insertion_sort(int[]);
int * merge_sort(int*, int, int);
void merge(int*, int, int, int);
void merge1(int*, int, int, int);
void merge_sort1(int*, int, int);
int * quick_sort(int*, int, int);
int partion(int*, int, int);


int main(int argc, const char * argv[]) {
    //int arr[n] = {5, 4, 3, 2, 1};
    //int arr2[n] = {5, 4, 3, 2, 1};
    //int arr3[mn] = {5, 4, 8, 3, 2, 1, 7, 6};
    int arr4[mn] = {5, 4, 8, 3, 2, 1, 7, 6};
    int arr5[mn] = {8, 5, 3, 6, 1, 7, 4, 2};
    int arr6[mn] = {1, 5, 3, 7, 8, 2, 4, 6};
    int arr7[mne] = {8, 1, 10, 7, 2, 11, 3, 9, 6, 5, 4};

    /*
    cout << "Before:    ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    
    int * bubble_arr = bubble_sort(arr);

    cout << endl << "After Bubble Sorting:    ";
    for (int i = 0; i < n; i++) {
        cout << bubble_arr[i] << " ";
    }
     
     */
    /*
    int * insertion_arr = insertion_sort(arr2);
    
    cout << endl << "After Insertion Sorting:    ";
    for (int i = 0; i < n; i++) {
        cout << insertion_arr[i] << " ";
    }
    */
    
    /*
    int * merge_arr = merge_sort(arr3, 0, 8);
    
    cout << endl << "After Merge Sorting:    ";
    for (int i = 0; i < mn; i++) {
        cout << merge_arr[i] << " ";
    }
    */
    
    
    int * quick_arr = quick_sort(arr7, 0, 10);
    
    cout << endl << "After Quick Sorting:    ";
    for (int i = 0; i < mne; i++) {
        cout << quick_arr[i] << " ";
    }
    
    return 0;
}

void swap(int * i, int * j){
    int * temp;
    temp = i;
    i = j;
    j = temp;
}

int * bubble_sort(int arr[n]){
    int counter = 0;
    
    cout << endl << endl << "Bubble Sorting";
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n-i+1; j++) {
            if (arr[j - 1] > arr[j]){
                counter++;
                swap(arr[j-1], arr[j]);
                //temp = arr[j - 1];
                //arr[j - 1] = arr[j];
                //arr[j] = temp;
                cout << endl << counter << ". ";
                for (int i = 0; i < n; i++) {
                    cout << arr[i] << " ";
                }
            }
        }
    }
    return arr;
}


int * insertion_sort(int arr[n]){
    int counter = 0;
    
    cout << endl << endl << "Insertion Sorting";
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0; j--) {
            if (arr[j] < arr[j - 1]){
                counter++;
                swap(arr[j - 1], arr[j]);
                //temp = arr[j];
                //arr[j] = arr[j - 1];
                //arr[j - 1] = temp;
                cout << endl << counter << ". ";
                for (int x = 0; x < n; x++) {
                    cout << arr[x] << " ";
                }
            }
        }
    }
    return arr;
}


void merge_sort1(int * arr, int p, int r){
    int q;
    if (p < r){

        q = (p + r) / 2;
        merge_sort(arr, p, q);
        merge_sort(arr, q + 1, r);
        merge(arr, p, q, r);
    }
    //return arr;
}

void merge1(int * arr, int p, int q, int r){
    int i, j;
    int n1 = (q - p) + 1;
    int n2 = (r - q);
    
    int left[n1 + 1], right[n2 + 1];
    
    for(i = 1; i < n1; i++){
        left[i] = arr[p + i - 1];
    }
    
    for(j = 1; j < n2; j++){
        right[j] = arr[q + j];
    }
    
    left[n1] = INFINITY;
    right[n2] = INFINITY;
    
    cout << "Left ";
    for (int x = 0; x <= n1; x++) {
        cout << left[x] << " ";
    }
    cout << endl;
    
    cout << "Right ";
    for (int x = 0; x <= n2; x++) {
        cout << right[x] << " ";
    }
    cout << endl;
    
    i = 1, j = 1;
    
    for (int k = p; k <= r; k++){
        if (left[i] <= right[j]){
            arr[k] = left[i];
            i++;
        }
        else{
            arr[k] = right[j];
            j++;
        }
    }
    
    //return arr;
}

void merge(int arr[], int first, int mid, int last){
    int i, j, k;
    int n1 = mid - first + 1;
    int n2 =  last - mid;
    
    /* create temp arrays */
    int L[n1], R[n2];
    
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++){
        L[i] = arr[first + i];
    }
    for (j = 0; j < n2; j++){
        R[j] = arr[mid + 1 + j];
    }
    
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = first; // Initial index of merged subarray
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    /* Copy the remaining elements of L[], if there
     are any */
    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    
    /* Copy the remaining elements of R[], if there
     are any */
    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
 sub-array of arr to be sorted */
int * merge_sort(int arr[], int l, int r){
    if (l < r){
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
        
        // Sort first and second halves
        merge_sort(arr, l, m);
        merge_sort(arr, m+1, r);
        
        merge(arr, l, m, r);
    }
    return arr;
}

int partion(int arr[], int p, int r){
    int x = arr[r];
    int i = p - 1;
    for(int j = p; j < r; j++){
        if(arr[j] <= x){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[r]);
    return i + 1;
}

int * quick_sort(int arr[], int p, int r){
    if(p < r){
        int q = partion(arr, p, r);
        quick_sort(arr, p, q-1);
        quick_sort(arr, q+1, r);
    }
    return arr;
}














