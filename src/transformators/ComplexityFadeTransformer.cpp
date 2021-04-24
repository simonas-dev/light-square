//
//  ComplexityFadeTransformer.cpp
//  light-square
//
//  Created by Simonas Sankauskas on 2020-10-06.
//
#include "ComplexityFadeTransformer.hpp"

void ComplexityFadeTransformer::setup() {
    gui.setup();
    gui.setName("Fade");
    gui.add(isEnabled.setup("Is Enabled", true));
    gui.add(fadeRatio.setup("Fade Ratio", 0.035, 0.0, 0.35));
    gui.add(dropOff.setup("Drop Off", 0.5, 0.0, 1.0));
}

vector<ofColor> ComplexityFadeTransformer::transform(vector<ofColor> colors) {
    if (isEnabled) {
        vector<ofColor> mapped;
        for (ofColor color : colors) {
            float complexity = context->audio.model.specCompNorm;
            rollingComplexity = rollingComplexity * (1 - dropOff) + complexity * (dropOff);
            ofColor mappedColor = color.lerp(ofColor::black, fadeRatio * rollingComplexity);
            mapped.push_back(mappedColor);
        }
        lastTransformation = mapped;
        return mapped;
    } else {
        return colors;
    }
}

void ComplexityFadeTransformer::drawThumb(int x, int y, float w, float h) {
    if (context->audio.isReady == false) return;
    gui.setPosition(x, y-gui.getHeight());
    gui.draw();
}
