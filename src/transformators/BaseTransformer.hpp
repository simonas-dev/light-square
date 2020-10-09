//
//  BaseTransformer.hpp
//  light-square
//
//  Created by Simonas Sankauskas on 2020-10-06.
//
#pragma once

#ifndef BaseTransformer_hpp
#define BaseTransformer_hpp

#include "ofMain.h"
#include "ofMath.h"
#include "ofxGui.h"
#include "AppContext.hpp"
#include "TransformationPainter.hpp"

#endif /* BaseTransformer_hpp */

class BaseTransformer {
public:
    vector<ofColor> lastTransformation;
    ofxPanel gui;
    ofxToggle isEnabled;
    AppContext * context;
    
    virtual vector<ofColor> transform(vector<ofColor> colors) = 0;
    virtual void setup() = 0;
    virtual void drawThumb(int x, int y, float w, float h) = 0;
};
