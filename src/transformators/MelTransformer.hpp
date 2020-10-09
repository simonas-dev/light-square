//
//  MelTransformer.hpp
//  light-square
//
//  Created by Simonas Sankauskas on 2020-10-10.
//
#pragma once

#ifndef MelTransformer_hpp
#define MelTransformer_hpp

#include "BaseTransformer.hpp"

#endif /* MelTransformer_hpp */

class MelTransformer : public BaseTransformer {
    AudioModel * audioModel;
public:
    MelTransformer(AppContext * appContext) {
        context = appContext,
        audioModel = &appContext->audio.model;
    };
    TransformationPainter painter;
    vector<ofColor> transform(vector<ofColor> colors);
    void setup();
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
