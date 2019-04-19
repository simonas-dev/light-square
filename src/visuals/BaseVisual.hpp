//
//  BaseVisual.hpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//
#pragma once

#ifndef BaseVisual_hpp
#define BaseVisual_hpp

#include "ofMain.h"

#endif /* BaseVisual_hpp */

class BaseVisual {
  
public:
    string name = "Untitled";
    bool isEnabled = true;
    float opacity = 1.0;
    void setup();
    void update();
    virtual void drawThumb(int x, int y, float w, float h) = 0;
    void exit();
};
