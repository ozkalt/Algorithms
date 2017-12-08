//
//  p3dict.h
//  AOAhw3
//
//  Created by Tuğba Özkal on 23.11.2017.
//  Copyright © 2017 Tuğba Özkal. All rights reserved.
//

#ifndef p3dict_h
#define p3dict_h

#include <map>
#include <set>

#define M 131071    // File size
#define A 0.618     // const value. It is used for hashing.

using namespace std;

class Dictionary{
private:
    map<unsigned long, BookChar> HashTable;     // HashTable keeps the unique key (1-131071) and BookChar objects.
    int Collition[M];   // Collision keeps the occured collision number for per unique key. Default value is zero.
        
    BookChar * readFromFile(char * filename);
    unsigned long Hashing(unsigned long);
    unsigned long QuadraticProbing(unsigned long, int);
    void HashInsert(BookChar);
    double averageCollision(unsigned long);

public:
    Dictionary();
    ~Dictionary();
    void BlockInsertion(char *);
    void BlockLookup(char *);
};

#endif /* p3dict_h */
