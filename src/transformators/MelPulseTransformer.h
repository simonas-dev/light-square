//
// Created by Simonas Sankauskas on 2021-07-29.
//
#pragma once


#ifndef LIGHT_SQUARE_MELPULSETRANSFORMER_H

#include "BaseTransformer.hpp"

#define LIGHT_SQUARE_MELPULSETRANSFORMER_H




class MelPulseTransformer : public BaseTransformer {

    AudioModel * audioModel;
    float peakMel = 0.0f;
public:
    MelPulseTransformer(AppContext * appContext) {
        context = appContext,
        audioModel = &appContext->audio.model;
    };
    TransformationPainter painter;
    vector<ofColor> transform(vector<ofColor> colors);
    void setup();
    void drawThumb(int x, int y, float w, float h);

    ofxFloatSlider multiplier;
    ofxIntSlider powerRatio;
    ofxFloatSlider melFloor;

    ofxToggle mel0;
    ofxToggle mel1;
    ofxToggle mel2;
    ofxToggle mel3;
    ofxToggle mel4;
    ofxToggle mel5;
    ofxToggle mel6;
    ofxToggle mel7;

    vector<ofxToggle> melToggles = {
            mel0,
            mel1,
            mel2,
            mel3,
            mel4,
            mel5,
            mel6,
            mel7
    };

    vector<ofColor> pulseColors = {
            ofColor::fromHex(0xFF0000),
            ofColor::fromHex(0xFF7F00),
            ofColor::fromHex(0x0000FF),
            ofColor::fromHex(0x7F00FF),
            ofColor::fromHex(0xFF00FF),
            ofColor::fromHex(0xFF007F)
    };

    ofxToggle color0;
    ofxToggle color1;
    ofxToggle color2;
    ofxToggle color3;
    ofxToggle color4;
    ofxToggle color5;
    vector<ofxToggle> colorToggles = {
            color0,
            color1,
            color2,
            color3,
            color4,
            color5
    };
};


#endif //LIGHT_SQUARE_MELPULSETRANSFORMER_H
