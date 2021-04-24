//
//  FadeTransformer.cpp
//  light-square
//
//  Created by Simonas Sankauskas on 2020-10-06.
//
#include "FadeTransformer.hpp"

void FadeTransformer::setup() {
    gui.setup();
    gui.setName("Fade");
    gui.add(isEnabled.setup("Is Enabled", true));
    gui.add(fadeRatio.setup("Fade Ratio", 0.035, 0.0, 0.35));
}

vector<ofColor> FadeTransformer::transform(vector<ofColor> colors) {
    vector<ofColor> mapped;
    for (ofColor color : colors) {
        ofColor mappedColor = color.lerp(ofColor::black, fadeRatio);
        mapped.push_back(mappedColor);
    }
    lastTransformation = mapped;
    return mapped;
}

void FadeTransformer::drawThumb(int x, int y, float w, float h) {
    if (context->audio.isReady == false) return;
    gui.setPosition(x, y-gui.getHeight());
    gui.draw();
}
