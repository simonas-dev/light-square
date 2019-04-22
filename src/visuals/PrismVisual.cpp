//
//  PrismVisual.cpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/22/19.
//

#include "PrismVisual.hpp"


void PrismVisual::setup() {
    gui.setup();
    gui.setName(name);
    gui.add(isEnabled.setup("Is Enabled", true));
    gui.add(reloadShader.setup("Reload?", false));
    shadertoy.load("shaders/prism.frag");
    shadertoy.setAdvanceTime(true);
}

void PrismVisual::drawScene(int x, int y, float w, float h) {
    if (isEnabled) {
        drawVisual(x, y, w, h);
    }
    if (reloadShader) {
        shadertoy.load("shaders/prism.frag");
    }
}

void PrismVisual::drawVisual(int x, int y, float w, float h) {
    shadertoy.setDimensions(w, h);
    shadertoy.draw(x, y, w, h);
}

void PrismVisual::drawThumb(int x, int y, float w, float h) {
    if (context->audio.isReady == false) return;
    gui.setPosition(x, y-gui.getHeight());
    gui.draw();
    drawVisual(x, y, w, h);
}
