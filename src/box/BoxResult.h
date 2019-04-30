//
// Created by Simonas Sankauskas on 2019-04-26.
//

#ifndef LIGHT_SQUARE_BOXRESULT_H
#define LIGHT_SQUARE_BOXRESULT_H

#include "ofMain.h"

template <class T>
class BoxResult {
public:
    bool isSuccess;
    string error;
    T value;
};


#endif //LIGHT_SQUARE_BOXRESULT_H
