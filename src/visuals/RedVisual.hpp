//
//  RedVisual.hpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//
#pragma once

#ifndef RedVisual_hpp
#define RedVisual_hpp

#include "ofMain.h"
#include "BaseVisual.hpp"

#endif /* RedVisual_hpp */

class RedVisual : public BaseVisual {
  
public:
    RedVisual() {
        name = "Red Visual";
    };
    
    void drawThumb(int x, int y, float w, float h);
};
