//
//  main.cpp
//  AOAhw2
//
//  Created by Tuğba Özkal on 30.10.2017.
//  Copyright © 2017 Tuğba Özkal. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string.h>
#include <string>
#include <ctime>

using namespace std;

struct Data{
    int population;
    int min_age;
    int max_age;
    string gender;
    int zip_code;
    string geo_id;
};

long  int calculateLineNumber(char *);
Data * readFromFile(char *,  long int);
void writeToFile(Data *,  long int);
long int partion(Data *,  long int,  long int);
Data * quick_sort(Data *,  long int,  long int);

int main(int argc, const char * argv[]) {
    long int linenumber = atol(argv[1]);
    char filename[30] = "population_by_zip_2010.csv";

    long int totalline = calculateLineNumber(filename);
    long int SIZE;
    
    if(linenumber <= totalline){
        SIZE = linenumber;
    }
    else{
        SIZE = totalline;
    }
    
    clock_t begin;
    clock_t end;
    
    Data * data = readFromFile(filename, SIZE);
    
    if(data){
        begin = clock();
        quick_sort(data, 0, SIZE - 1);
        end = clock();
        
        writeToFile(data, SIZE);
        
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        cout << endl << "Time elapsed: " << elapsed_secs << " seconds." << endl << endl;
    }
    
    return 0;
}

long  int calculateLineNumber(char * filename){
    long  int line = 0;
    ifstream file(filename);
    string buffer;
    while (file.good()){
        getline(file, buffer);
        line++;
    }
    file.close();
    return line;
}

Data * readFromFile(char * filename,  long int size){
    ifstream file(filename);
    if (!file.is_open()){
        return NULL;
    }
    
    Data * data = new Data[size];
    long int i = 0;
    string buffer;
    string population, min_age, max_age, gender, zip_code, geo_id;
    getline(file, buffer); // skip the first line

    while (file.good() && i < size){
        getline(file, population, ',');
        data[i].population = atoi(population.c_str());
        
        getline(file, min_age, ',');
        data[i].min_age = atoi(min_age.c_str());
        
        getline(file, max_age, ',');
        data[i].max_age = atoi(max_age.c_str());
        
        getline(file, gender, ',');
        data[i].gender = gender;
        
        getline(file, zip_code, ',');
        data[i].zip_code = atoi(zip_code.c_str());
        
        getline(file, geo_id);
        data[i].geo_id = geo_id;
        i++;
    }
    file.close();
    return data;
}

void writeToFile(Data * arr,  long int size){
    ofstream myfile;
    myfile.open("sorted.csv");
    myfile << "population" << ","
    << "minimum age" << ","
    << "maximum age" << ","
    << "gender" << ","
    << "zip_code" << ","
    << "geo_id" << endl;
    for(int i = 0; i < size; i++){
        myfile << arr[i].population << ","
        << arr[i].min_age  << ","
        << arr[i].max_age  << ","
        << arr[i].gender  << ","
        << arr[i].zip_code  << ","
        << arr[i].geo_id  << endl;
    }
    myfile.close();
    delete[] arr;
}

void swap(Data * A, Data * B){
    Data * temp;
    temp = A;
    A = B;
    B = temp;
}

long partion(Data * arr,  long int p,  long int r){
    int x = arr[r].population;
    string y = arr[r].geo_id;
    long int i = p - 1;
    for( long int j = p; j < r; j++){
        if(arr[j].population < x){
            i++;
            swap(arr[i], arr[j]);
        }
        else if(arr[j].population == x){
            if(arr[j].population == x && arr[j].geo_id <= y){
                i++;
                swap(arr[i], arr[j]);
            }
        }
    }
    swap(arr[i + 1], arr[r]);
    return i + 1;
}

Data * quick_sort(Data * arr, long int p, long int r){
    
    if(p < r){
         long int q = partion(arr, p, r);
        quick_sort(arr, p, q-1);
        quick_sort(arr, q+1, r);
    }
    return arr;
}


