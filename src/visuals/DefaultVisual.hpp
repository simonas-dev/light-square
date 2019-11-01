//
//  DefaultVisual.hpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//
#pragma once

#ifndef DefaultVisual_hpp
#define DefaultVisual_hpp

#include "ofMain.h"
#include "BaseVisual.hpp"
#include "AudioModel.hpp"

#endif /* DefaultVisual_hpp */

class DefaultVisual : public BaseVisual {
    AudioModel * audioModel;
public:
    DefaultVisual(AppContext * appContext) {
        name = "Original Visual";
        context = appContext;
        audioModel = &appContext->audio.model;
    };
    void setup();
    void drawScene(int x, int y, float w, float h);
    void drawVisual(int x, int y, float w, float h);
    void drawThumb(int x, int y, float w, float h);
    
    float peakMel = 1.0f;
    ofColor mixColor = ofColor::black;
    
    vector<ofColor>bandColors = {
        ofColor::fromHex(0xFF0000),
        ofColor::fromHex(0xFF7F00),
        ofColor::fromHex(0xFFFF00),
        ofColor::fromHex(0x7FFF00),
        ofColor::fromHex(0x00FF00),
        ofColor::fromHex(0x00FF7F),
        ofColor::fromHex(0x00FFFF),
        ofColor::fromHex(0x007FFF),
        ofColor::fromHex(0x0000FF),
        ofColor::fromHex(0x7F00FF),
        ofColor::fromHex(0xFF00FF),
        ofColor::fromHex(0xFF007F)
    };
    ofColor currentColor = ofColor::fromHex(0x000000);
    
    ofxFloatSlider maxNoteRatio;
    ofxFloatSlider alphaSlider;
    ofxIntSlider powerSlider;
    ofxToggle color0;
    ofxToggle color1;
    ofxToggle color2;
    ofxToggle color3;
    ofxToggle color4;
    ofxToggle color5;
    ofxToggle color6;
    ofxToggle color7;
    ofxToggle color8;
    ofxToggle color9;
    ofxToggle color10;
    ofxToggle color11;
};
