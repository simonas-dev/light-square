//
//  VisualMixerWindow.hpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//
#pragma once

#ifndef VisualMixerWindow_hpp
#define VisualMixerWindow_hpp

#include "ofMain.h"
#include "AppContext.hpp"
#include "BaseTransformer.hpp"
#include "FadeTransformer.hpp"
#include "CornerFadeTransformer.hpp"
#include "ComplexityFadeTransformer.hpp"
#include "StrobeTransformer.hpp"
#include "MelTransformer.hpp"
#include "BleedTransformer.hpp"
#include "MazeMelTransformer.hpp"
#include "MelPulseTransformer.h"

#endif /* VisualMixerWindow_hpp */

class VisualMixerWindow : public ofBaseApp {
    AppContext * context;
    TransformationPainter painter;
    vector<BaseTransformer*> transformers;
    vector<ofColor> colorMatrix;
    ofxFloatSlider smoothing;
    ofxFloatSlider hpcpSmoothing;
    ofxPanel gui;
public:
    VisualMixerWindow(AppContext * appContext) {
        context = appContext;
        transformers = {
                new MelPulseTransformer(context),
                new MelTransformer(context),
                new MazeMelTransformer(context),
                new StrobeTransformer(context),
                new FadeTransformer(context),
                new BleedTransformer(context),
                new CornerFadeTransformer(context),
        };
        for (int i = 0; i < 512; ++i) {
            colorMatrix.push_back(ofColor::black);
        }
    };
    void setup();
    void update();
    void draw();
    void exit();
};
