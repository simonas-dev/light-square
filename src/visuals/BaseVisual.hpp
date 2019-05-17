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
#include "AppContext.hpp"
#include "ofxGui.h"

#endif /* BaseVisual_hpp */

class BaseVisual {
public:
    AppContext * context;
    ofxPanel gui;
    ofxToggle isEnabled;
    
    string name = "Untitled";
    float opacity = 1.0;
    virtual void setup() = 0;
    void update();
    virtual void drawVisual(int x, int y, float w, float h) = 0;
    virtual void drawThumb(int x, int y, float w, float h) = 0;
    virtual void drawScene(int x, int y, float w, float h) = 0;
    void exit();
};
