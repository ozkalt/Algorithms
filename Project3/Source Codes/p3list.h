//
//  p3list.h
//  AOAhw3
//
//  Created by Tuğba Özkal on 23.11.2017.
//  Copyright © 2017 Tuğba Özkal. All rights reserved.
//

#ifndef p3list_h
#define p3list_h

#include <vector>

#define M 131071    // File size

using namespace std;

class List{
private:
    vector <BookChar> llist;
    BookChar * readFromFile(char * filename);
    
public:
    List();
    ~List();
    void BlockInsertion(char *);
    void BlockLookup(char *);
};

#endif /* p3list_h */
