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
    context->ledClient.setup();
    gui.setup("Audio");
    gui.add(smoothing.setup("Smoothing", 0.35, 0.0, 1.0));
    gui.add(hpcpSmoothing.setup("HPCP Smoothing", 0.8, 0.0, 1.0));
    
    for (BaseTransformer * transformer : transformers) {
        transformer->setup();
    }
}

void VisualMixerWindow::update() {
    context->audio.smoothing = smoothing;
    context->audio.hpcpSmoothing = hpcpSmoothing;
    ofSetColor(ofColor::blue);
    for (BaseTransformer * transformer : transformers) {
        colorMatrix = transformer->transform(colorMatrix);
    }
    context->ledClient.draw(colorMatrix);
}

void VisualMixerWindow::draw() {
    ofSetWindowTitle(ofToString(ofGetFrameRate()));

    gui.setPosition(0, 0);
    gui.draw();

    int stageWidth = ofGetWidth() / 1.7;
    int margin = (ofGetWidth() - stageWidth) / 2;
    int stageHeight = stageWidth / 2;
    painter.draw(colorMatrix, margin, 0, stageWidth, stageHeight);
    int xpos = 0;
    int thumbW = 150;
    int thumbH = 100;
    for (BaseTransformer * transformer : transformers) {
        transformer->drawThumb(xpos, ofGetHeight()-thumbH, thumbW, thumbH);
        xpos += thumbW;
    }
}

void VisualMixerWindow::exit() {

}
