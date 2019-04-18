//
//  VisualMixerWindow.cpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//

#include "VisualMixerWindow.hpp"

void VisualMixerWindow::setup() {
    context->led.setup();
}

void VisualMixerWindow::update() {
    context->led.beginStage();
    ofSetColor(ofColor::blue);
    ofDrawRectangle(0, 0, 200, 100);
    context->led.endStage();
}
void VisualMixerWindow::draw() {
    context->led.drawStage();
}
void VisualMixerWindow::exit() {
    context->led.exit();
}
