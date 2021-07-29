//
//  StrobeTransformer.cpp
//  light-square
//
//  Created by Simonas Sankauskas on 2020-10-06.
//

#include "StrobeTransformer.hpp"

vector<ofColor> StrobeTransformer::transform(vector<ofColor> colors) {
    vector<ofColor> mapped;
    if (isEnabled) {
        float kickFloat = powerRatio * context->audio.model.strongDecayNorm;
        for (ofColor color : colors) {
            float random = ofRandom(randomization);
            float lerp = pow(kickFloat, 2) * (1 - random);
            ofColor strobeColor = ofColor::white;
            ofColor mappedColor = color.lerp(strobeColor, lerp);
            mapped.push_back(mappedColor);
        }
    } else {
        mapped = colors;
    }
    lastTransformation = mapped;
    return mapped;
}

void StrobeTransformer::setup() {
    gui.setup();
    gui.setName("Strobe");
    gui.add(isEnabled.setup("Is Enabled", false));
    gui.add(powerRatio.setup("Strobe Power Ratio", 0.0, 0.0, 1.0));
    gui.add(randomization.setup("Randomization", 0, 0.0, 1.0));
}

void StrobeTransformer::drawThumb(int x, int y, float w, float h) {
    if (context->audio.isReady == false) return;
    gui.setPosition(x, y-gui.getHeight());
    gui.draw();
    if (lastTransformation.size() > 0) {
        painter.draw(lastTransformation, x, y, w, h);
    }
}
