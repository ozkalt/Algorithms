//
//  p3list.cpp
//  AOAhw3
//
//  Created by Tuğba Özkal on 23.11.2017.
//  Copyright © 2017 Tuğba Özkal. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <list>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>

#include "p3char.h"
#include "p3list.h"


List::List(){
    llist.resize(M);
}

List::~List(){
    
}

BookChar * List::readFromFile(char * filename){
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

void List::BlockInsertion(char * filename){
    clock_t begin, end;
    BookChar * data = readFromFile(filename);
    
    begin = clock();
    for (unsigned long i = 0; i < M - 1; i++){
        llist.push_back(data[i]);
    }
    end = clock();
    double total_time = double(end - begin) / CLOCKS_PER_SEC;  // Total insertion runtime in type of seconds.
    
    cout << "Insertion finished after " << total_time << " seconds." << endl << endl;
}

void List::BlockLookup(char * filename){
    clock_t begin, end;
    
    BookChar * lookup = new BookChar[M];
    ifstream file(filename);
    
    if (!file.is_open()){
        cout << "File cannot open" << endl;
    }
    else{
        unsigned long i = 0;
        string pageNo, lineNo, indexNo, character;
        
        while (file.good() && i < M - 1){
            getline(file, pageNo, '\t');
            lookup[i].page = atoi(pageNo.c_str());
            getline(file, lineNo, '\t');
            lookup[i].line = atoi(lineNo.c_str());
            getline(file, indexNo, '\n');
            lookup[i].index = atoi(indexNo.c_str());
            lookup[i].generateUniqueKey();
            i++;
        }
    }
    file.close();
    
    begin = clock();
    vector<BookChar>::iterator it;
    for (unsigned long i = 0; i < M - 1; i++){
        for (it = llist.begin(); it != llist.end(); it++){
            if (it->key == lookup[i].key){
                lookup[i].c = it->c;
                //cout << lookup[i].key << "\t" << lookup[i].c << endl;
                break;
            }
        }
    }
    end = clock();
    double total_time = double(end - begin) / CLOCKS_PER_SEC;
    cout << endl << "Lookup finished after " << total_time << " seconds." << endl << endl;
    
    char outfile[30] = "ds-set-output-list.txt";
    ofstream out(outfile);
    
    for (unsigned long i = 0; i < M; i++){
        out << lookup[i].page << "\t" << lookup[i].line << "\t" << lookup[i].index << "\t" << lookup[i].c << "\t" << endl;
    }
    out.close();
    
}







