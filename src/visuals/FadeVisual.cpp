//
//  StrobeVisual.cpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//

#include "FadeVisual.hpp"

void FadeVisual::setup() {
    gui.setup();
    gui.setName(name);
    gui.add(isEnabled.setup("Is Enabled", true));
    gui.add(fadeRatio.setup("Fade Ratio", 0.035, 0.0, 0.35));
}

void FadeVisual::drawScene(int x, int y, float w, float h) {
    if (isEnabled) {
        drawVisual(x, y, w, h);
    }
}

void FadeVisual::drawVisual(int x, int y, float w, float h) {
    ofPushMatrix();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(ofColor::black, (int) (255 * fadeRatio));
    ofDrawRectangle(x, y, w, h);
    ofDisableBlendMode();
    ofPopMatrix();
}

void FadeVisual::drawThumb(int x, int y, float w, float h) {
    if (context->audio.isReady == false) return;
    gui.setPosition(x, y-gui.getHeight());
    gui.draw();
    drawVisual(x, y, w, h);
}
