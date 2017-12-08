//
//  p3dict.cpp
//  AOAhw3
//
//  Created by Tuğba Özkal on 23.11.2017.
//  Copyright © 2017 Tuğba Özkal. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
#include <math.h>
#include <map>
#include <set>
#include <ctime>

#include "p3char.h"
#include "p3dict.h"

Dictionary::Dictionary(){
    for (unsigned long i = 0; i < M; i++){
        Collition[i] = 0;
    }
}

Dictionary::~Dictionary(){
    HashTable.clear();
}

BookChar * Dictionary::readFromFile(char * filename){
    BookChar * book = new BookChar[M];
    ifstream file(filename);
    
    if (!file.is_open()){
        cout << "File cannot open" << endl;
        return NULL;
    }
    else{
        unsigned long i = 0;
        string pageNo, lineNo, indexNo, character;
        
        while (file.good() && i < M - 1){
            getline(file, pageNo, '\t');
            book[i].page = atoi(pageNo.c_str());
            getline(file, lineNo, '\t');
            book[i].line = atoi(lineNo.c_str());
            getline(file, indexNo, '\t');
            book[i].index = atoi(indexNo.c_str());
            getline(file, character, '\n');
            book[i].c = character[0];
            book[i].generateUniqueKey();
            i++;
        }
        file.close();
    }
    return book;
}

unsigned long Dictionary::Hashing(unsigned long k){
    return floor(M * (k * A - floor(k * A)));
}

unsigned long Dictionary::QuadraticProbing(unsigned long k, int i){
    return (7 * i) + (3 * (pow(i, 2)));
}

void Dictionary::HashInsert(BookChar c){
    unsigned long value;
    value = Hashing(c.key);
    while (HashTable.count(value)){
        Collition[value]++;
        value = (value + QuadraticProbing(c.key, Collition[value])) % M;
    }
    HashTable.insert(make_pair(value, c));
}

double Dictionary::averageCollision(unsigned long size){
    double avr = 0;
    for (unsigned long i = 0; i < size; i++){
        avr += Collition[i];
    }
    avr = avr / size;
    return avr;
}

void Dictionary::BlockInsertion(char * filename){
    clock_t begin, end;
    double average[4], total_time;

    BookChar * data = readFromFile(filename);
    
    begin = clock();
    for (unsigned long i = 0; i < M - 1; i++){
        HashInsert(data[i]);
    }
    end = clock();
    total_time = double(end - begin) / CLOCKS_PER_SEC;  // Total insertion runtime in type of seconds.
    
    cout << "Insertion finished after " << total_time << " seconds." << endl << endl;
    
    average[0] = averageCollision(1000);       // Average number of first 1000 lines
    average[1] = averageCollision(10000);       // Average number of first 10000 lines
    average[2] = averageCollision(100000);       // Average number of first 100000 lines
    average[3] = averageCollision(M);       // Average number of overall
    
    cout << "Average number of collition (first 1000)\t| " << average[0] << endl;
    cout << "Average number of collition (first 10000)\t| " << average[1] << endl;
    cout << "Average number of collition (first 100000)\t| " << average[2] << endl;
    cout << "Average number of collition (overall)\t\t| " << average[3] << endl;
}

void Dictionary::BlockLookup(char * filename){
    BookChar * lookup = new BookChar[M];
    
    ifstream file(filename);
    if (!file.is_open()){
        cout << "File cannot open" << endl;
    }
    else{
        unsigned long counter = 0;
        string pageNo, lineNo, indexNo;
        while (file.good() && counter < M){
            getline(file, pageNo, '\t');
            lookup[counter].page = atoi(pageNo.c_str());
            getline(file, lineNo, '\t');
            lookup[counter].line = atoi(lineNo.c_str());
            getline(file, indexNo, '\n');
            lookup[counter].index = atoi(indexNo.c_str());
            lookup[counter].generateUniqueKey();
            counter++;
        }
        file.close();
        clock_t begin, end;
        double total_time;
        begin = clock();
        
        Dictionary();
        
        unsigned long value;
        for (unsigned long i = 0; i < M - 1; i++){
            value = Hashing(lookup[i].c);
            if(HashTable[value].key == lookup[i].key){
                lookup[i].c = HashTable[value].c;
            }
            else{
                while (HashTable[value].key != lookup[i].key){
                    Collition[value]++;
                    value = (value + QuadraticProbing(lookup[i].key, Collition[value])) % M;
                }
                lookup[i].c = HashTable[value].c;
            }
        }
        end = clock();

        total_time = double(end - begin) / CLOCKS_PER_SEC;
        cout << endl << "Lookup finished after " << total_time << " seconds." << endl << endl;
        
        char outfile[30] = "ds-set-output-dict.txt";
        ofstream out(outfile);
        
        for (unsigned long i = 0; i < M; i++){
            out << lookup[i].page << "\t" << lookup[i].line << "\t" << lookup[i].index << "\t" << lookup[i].c << "\t" << endl;
        }
        out.close();
    
    }
}






















