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
    gui.add(alphaRatio.setup("Alpha", 0.0, 0.0, 1.0));
    shadertoy.load("shaders/prism.frag");
    shadertoy.setAdvanceTime(true);
}

void PrismVisual::drawScene(int x, int y, float w, float h) {
    if (!isEnabled) return;
    drawVisual(x, y, w, h);
    if (reloadShader) {
        shadertoy.load("shaders/prism.frag");
    }
}

void PrismVisual::drawVisual(int x, int y, float w, float h) {
    ofEnableAlphaBlending();
    shadertoy.begin();
    shadertoy.setDimensions(w, h);
    shadertoy.setUniform1f("aAlpha", (float) alphaRatio);
    shadertoy.setUniform1f("aPower", context->audio.model.power);
    shadertoy.setUniform1f("aStrongPeak", context->audio.model.strongPeakNorm);
    shadertoy.end();
    shadertoy.draw(x, y, w, h);
    ofDisableAlphaBlending();
}

void PrismVisual::drawThumb(int x, int y, float w, float h) {
    if (context->audio.isReady == false) return;
    gui.setPosition(x, y-gui.getHeight());
    gui.draw();
    if (!isEnabled) return;
    drawVisual(x, y, w, h);
}
