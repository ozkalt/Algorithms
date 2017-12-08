//
//  p3char.h
//  AOAhw3
//
//  Created by Tuğba Özkal on 23.11.2017.
//  Copyright © 2017 Tuğba Özkal. All rights reserved.
//

#ifndef p3char_h
#define p3char_h

class BookChar{
private:
    int page;
    int line;
    int index;
    char c;
    unsigned long key;
    void generateUniqueKey();
    
    friend class Dictionary;
    friend class List;
};

#endif /* p3char_h */
