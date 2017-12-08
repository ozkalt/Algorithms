//
//  main.cpp
//  AOAhw3
//
//  Created by Tuğba Özkal on 23.11.2017.
//  Copyright © 2017 Tuğba Özkal. All rights reserved.
//

#include <iostream>

#include "p3char.h"
#include "p3list.h"
#include "p3dict.h"


using namespace std;

int main(int argc, const char * argv[]) {
    char input[30] = "ds-set-input.txt";
    char lookup[30] = "ds-set-lookup.txt";
    Dictionary d;
    List l;
    /*
    cout << endl << "DICTIONARY" << endl;
    d.BlockInsertion(input);
    d.BlockLookup(lookup);
    */
    cout << endl << "LIST" << endl;
    l.BlockInsertion(input);
    l.BlockLookup(lookup);
    return 0;
}


