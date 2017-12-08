//
//  p3char.cpp
//  AOAhw3
//
//  Created by Tuğba Özkal on 23.11.2017.
//  Copyright © 2017 Tuğba Özkal. All rights reserved.
//

#include <stdio.h>

#include "p3char.h"
#include "p3list.h"
#include "p3dict.h"

using namespace std;

void BookChar::generateUniqueKey(){
    key = (page * 10000) + (line * 100) + index;
}
