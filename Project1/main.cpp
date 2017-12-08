//
//  main.cpp
//  AOAhw1
//
//  Created by Tuğba Özkal on 4.10.2017.
//  Copyright © 2017 Tuğba Özkal. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#define CHARLENGTH 30

using namespace std;

struct Cards{
    char name[CHARLENGTH];
    char branch[CHARLENGTH];
    char rarity[CHARLENGTH];
    char set[CHARLENGTH];
    char type[CHARLENGTH];
    int cost;
};

class CardManager{
public:
    long unsigned int calculateLineNumber(char *);      // This is for calculate the total line numbers of file.
    Cards * readFromFile(char *, long unsigned int);    // This is for reading datas from file.
    void writeToFile(Cards *, char *, long unsigned int);   // This is for writing datas to a new file.
    void printCardList(Cards *, long unsigned int);     // This is for printing all sorted or unsorted datas on screen.
    Cards * filter_insertion_sort(Cards *, long unsigned int);  // Filter sorting by using insertion
    Cards * full_insertion_sort(Cards *, long unsigned int);    // Full sorting by using insertion
    Cards * filter_merge_sort(Cards *, unsigned long int, unsigned long int);   // Filter sorting by using merge
    Cards * full_merge_sort(Cards *, unsigned long int, unsigned long int);     // Full sorting by using merge
    Cards * filter_merge(Cards *, unsigned long int, unsigned long int, unsigned long int); // Merging for filter sorting
    Cards * full_merge(Cards *, unsigned long int, unsigned long int, unsigned long int);   // Merging for full sorting
};

void swap(Cards *, Cards *);    // This is for swapping data lines. This function is used in insertion sortings.

int main(int argc, const char * argv[]) {
    
    // Allocate memory for all need
    char * sortType = new char[CHARLENGTH];     // This is about full sorting or filter sorting
    char * sortAlgo = new char[CHARLENGTH];     // This is about sorting algorithms
    char * fileName = new char[CHARLENGTH];     // This takes file name value which will be sorted from the argv
    char * sortedFileName = new char[CHARLENGTH];   // This takes sorted file name which should be name of sorted file
    unsigned long int SIZE = 0;     // SIZE describes the file has 10k lines, 100k lines or 1M lines.
    clock_t * begin = new clock_t[4];   // This is for keeping start time of sorting
    clock_t * end = new clock_t[4];     // This is for keeping end time of sorting
    int check = -1;     // There is 4 probabilities: insertion filter, insertion full, merge filter and merge full. So I create two arrays for keeping starting time and end time, And they have 4 divisions. I used the check for which division is online.
    
    strcpy(sortType, argv[1]);
    strcpy(sortAlgo, argv[2]);
    strcpy(fileName, argv[3]);
    strcpy(sortedFileName, argv[4]);
    
    CardManager manager;
    
    SIZE = manager.calculateLineNumber(fileName);
    Cards * arr = manager.readFromFile(fileName, SIZE);
    
    if(strcmp(sortType, "-filter") == 0){
        if(strcmp(sortAlgo, "-i") == 0){
            begin[0] = clock();
            manager.filter_insertion_sort(arr, SIZE);
            end[0] = clock();
            check = 0;
        }
        else if(strcmp(sortAlgo, "-m") == 0){
            begin[1] = clock();
            manager.filter_merge_sort(arr, 0, SIZE - 1);
            end[1] = clock();
            check = 1;
        }
        else{
            cout << "Invalid algorithms name." << endl;
        }
    }
    else if(strcmp(sortType, "-full") == 0){
        if(strcmp(sortAlgo, "-i") == 0){
            begin[2] = clock();
            manager.full_insertion_sort(arr, SIZE);
            end[2] = clock();
            check = 2;
        }
        else if(strcmp(sortAlgo, "-m") == 0){
            begin[3] = clock();
            manager.full_merge_sort(arr, 0, SIZE - 1);
            end[3] = clock();
            check = 3;
        }
        else{
            cout << "Invalid sorting algorithm name." << endl;
        }
    }
    else{
        cout << "Invalid sorting type name." << endl;
    }
    
    if(check >= 0){
        double elapsed_secs = double(end[check] - begin[check]) / CLOCKS_PER_SEC;
        cout << "Time elapsed: " << elapsed_secs << " seconds." << endl;
    }
    
    manager.writeToFile(arr, sortedFileName, SIZE);
    
    
    // Deallocated all dynamic memories.
    delete[] sortType;
    delete[] sortAlgo;
    delete[] fileName;
    delete[] sortedFileName;
    delete[] begin;
    delete[] end;
    
    return 0;
}


Cards * CardManager::readFromFile(char * fileName, long unsigned int size){
    FILE *txt = fopen(fileName, "r");
    Cards * card = new Cards[size];
    fseek(txt, 0, SEEK_SET);
    for(int i = 0; i < size; i++){
        fscanf(txt, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%d\n", card[i].name, card[i].branch, card[i].rarity, card[i].set, card[i].type, &card[i].cost);
    }
    
    fclose(txt);
    
    //printCardList(card, size);
    
    return card;
}

void CardManager::writeToFile(Cards * card, char * sortedFileName, long unsigned int size){
    ofstream txt;
    txt.open (sortedFileName);
    for (int i = 0; i < size; i++){
        txt << card[i].name << "\t" << card[i].branch << "\t" << card[i].rarity << "\t" << card[i].set << "\t" << card[i].type << "\t" << card[i].cost << endl;
    }
    txt.close();
    
    delete[] card;
}


long unsigned int CardManager::calculateLineNumber(char * txt){
    long unsigned int size = 0;
    ifstream f(txt);
    char c;
    while (f.get(c)){
        if (c == '\n'){
            ++size;
        }
    }
    return size;
}


void CardManager::printCardList(Cards * card, long unsigned int size){
    for(int i = 0; i < size; i++){
        cout << i + 1 << ". " << card[i].name << "\t" << card[i].branch << "\t" << card[i].rarity << "\t" << card[i].set << "\t" << card[i].type << "\t" << card[i].cost << endl;
    }
}


void swap(Cards * a, Cards * b){
    Cards * temp;
    temp = a;
    a = b;
    b = temp;
}


Cards * CardManager::filter_insertion_sort(Cards * arr, long unsigned int size){
    
    for (int i = 1; i < size; i++) {
        for (int j = i; j > 0; j--) {
            if (strcmp(arr[j].type, arr[j - 1].type) < 0){
                swap(arr[j - 1], arr[j]);
            }
        }
    }
    //printCardList(arr, size);
    
    return arr;
}


Cards * CardManager::full_insertion_sort(Cards * arr, long unsigned int size){
    for (int i = 1; i < size; i++) {
        for (int j = i; j > 0; j--) {
            if (strcmp(arr[j].branch, arr[j - 1].branch) < 0){
                swap(arr[j - 1], arr[j]);
            }
            else if (strcmp(arr[j].branch, arr[j - 1].branch) == 0){
                if (arr[j].cost < arr[j - 1].cost){
                    swap(arr[j - 1], arr[j]);
                }
                else if(arr[j].cost == arr[j - 1].cost){
                    if (strcmp(arr[j].name, arr[j - 1].name) < 0){
                        swap(arr[j - 1], arr[j]);
                    }
                }
            }
        }
    }
    
    //printCardList(arr, size);
    
    return arr;
}


Cards * CardManager::filter_merge_sort(Cards * arr, unsigned long int l, unsigned long int r){
    if (l < r){
        unsigned long int m = l+(r-l)/2;
        
        filter_merge_sort(arr, l, m);
        filter_merge_sort(arr, m+1, r);
        
        filter_merge(arr, l, m, r);
    }
    return arr;
}

Cards * CardManager::filter_merge(Cards * arr, unsigned long int first, unsigned long int mid, unsigned long int last){
    unsigned long int i, j, k;
    unsigned long int n1 = mid - first + 1;
    unsigned long int n2 =  last - mid;
    
    Cards * L = new Cards[n1];
    Cards * R = new Cards[n2];
    
    for (i = 0; i < n1; i++){
        L[i] = arr[first + i];
    }
    for (j = 0; j < n2; j++){
        R[j] = arr[mid + 1+ j];
    }
    
    i = 0;
    j = 0;
    k = first;
    while (i < n1 && j < n2){
        if (strcmp(L[i].type, R[j].type) <= 0){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
    return arr;
}


Cards * CardManager::full_merge_sort(Cards * arr, unsigned long int l, unsigned long int r){
    if (l < r){
        unsigned long int m = l+(r-l)/2;
        
        full_merge_sort(arr, l, m);
        full_merge_sort(arr, m+1, r);
        
        full_merge(arr, l, m, r);
    }
    return arr;
    return arr;
}

Cards * CardManager::full_merge(Cards * arr, unsigned long int first, unsigned long int mid, unsigned long int last){
    unsigned long int i, j, k;
    unsigned long int n1 = mid - first + 1;
    unsigned long int n2 =  last - mid;
    
    Cards * L = new Cards[n1];
    Cards * R = new Cards[n2];
    
    for (i = 0; i < n1; i++){
        L[i] = arr[first + i];
    }
    for (j = 0; j < n2; j++){
        R[j] = arr[mid + 1+ j];
    }
    
    i = 0;
    j = 0;
    k = first;
    while (i < n1 && j < n2){
        if (strcmp(L[i].branch, R[j].branch) < 0){
            arr[k] = L[i];
            i++;
        }
        else if (strcmp(L[i].branch, R[j].branch) == 0 && L[i].cost < R[j].cost ){
            arr[k] = L[i];
            i++;
        }
        else if (strcmp(L[i].branch, R[j].branch) == 0 && L[i].cost == R[j].cost && strcmp(L[i].name, R[j].name) <= 0){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
    return arr;
}
