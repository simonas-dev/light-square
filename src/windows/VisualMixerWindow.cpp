//
//  VisualMixerWindow.cpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//

#include "VisualMixerWindow.hpp"
#include "ofFbo.h"

void VisualMixerWindow::setup() {
    ofBackground(0);

    int stageWidth = ofGetWidth()/2;
    int stageHeight = stageWidth / 2;
    context->led.setup(stageWidth, stageHeight);
    
    for (BaseVisual * visual : visuals) {
        visual->setup();
    }
}

void VisualMixerWindow::update() {
    context->led.beginStage();
    ofSetColor(ofColor::blue);
    for (BaseVisual * visual : visuals) {
        int stageWidth = ofGetWidth()/2;
        int stageHeight = stageWidth / 2;
        visual->drawScene(0, 0, stageWidth, stageHeight);
    }
    context->led.endStage();
}

void VisualMixerWindow::draw() {
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    context->led.drawStage();
    int xpos = 0;
    int thumbW = 200;
    int thumbH = 100;
    for (BaseVisual * visual : visuals) {
        visual->drawThumb(xpos, ofGetHeight()-thumbH, thumbW, thumbH);
        xpos += thumbW;
    }
}

void VisualMixerWindow::exit() {
    context->led.exit();
}
