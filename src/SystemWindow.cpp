//
//  SystemWindow.cpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//

#include "SystemWindow.hpp"

void SystemWindow::setup() {
    ofSetFrameRate(60);
    ofBackground(0);
    context->audio.setup();
}

void SystemWindow::update() {
    context->audio.update();
}

void SystemWindow::draw() {
    auto color = ofColor::red.getLerped(ofColor::green, context->audio.model.power);
    ofSetColor(color);
    ofDrawRectangle(0, 0, 200, 200);
}

void SystemWindow::exit() {
    context->audio.exit();
}
