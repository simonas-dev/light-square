//
//  VisualMixerWindow.cpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//

#include "VisualMixerWindow.hpp"

void VisualMixerWindow::setup() {
    int stageWidth = ofGetWidth()/2;
    int stageHeight = stageWidth / 2;
    context->led.setup(stageWidth, stageHeight);
}

void VisualMixerWindow::update() {
    context->led.beginStage();
    ofSetColor(ofColor::blue);
    ofDrawRectangle(0, 0, 200, 100);
    context->led.endStage();
}
void VisualMixerWindow::draw() {
    context->led.drawStage();
    int xpos = 0;
    int thumbSize = 250;
    for (BaseVisual * visual : visuals) {
        visual->drawThumb(xpos, ofGetHeight()-thumbSize, thumbSize, thumbSize);
        xpos += thumbSize;
    }
}

void VisualMixerWindow::exit() {
    context->led.exit();
}
