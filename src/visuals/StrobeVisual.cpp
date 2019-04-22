//
//  StrobeVisual.cpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//

#include "StrobeVisual.hpp"

void StrobeVisual::setup() {
    gui.setup();
    gui.setName(name);
    gui.add(isEnabled.setup("Is Enabled", true));
}

void StrobeVisual::drawScene(int x, int y, float w, float h) {
    if (isEnabled) {
        drawVisual(x, y, w, h);
    }
}

void StrobeVisual::drawVisual(int x, int y, float w, float h) {
    ofPushMatrix();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    if (ofColor::white, context->audio.model.isOnset) {
        ofSetColor(ofColor::white, 255);
    } else {
        ofSetColor(ofColor::white, 0);
    }
    ofDrawRectangle(x, y, w, h);
    ofSetColor(ofColor::black, 10);
    ofDrawRectangle(x, y, w, h);
    ofDisableBlendMode();
    ofPopMatrix();
}

void StrobeVisual::drawThumb(int x, int y, float w, float h) {
    if (context->audio.isReady == false) return;
    gui.setPosition(x, y-gui.getHeight());
    gui.draw();
    drawVisual(x, y, w, h);
}
