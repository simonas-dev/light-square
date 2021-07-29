//
// Created by Simonas Sankauskas on 2021-07-29.
//

#include "MelPulseTransformer.h"

vector<ofColor> MelPulseTransformer::transform(vector<ofColor> colors) {
    if (context->audio.isReady == false) return colors;
    if (audioModel->melBands.size() == 0) return colors;
    if (isEnabled == false) return colors;

    vector<float> scaledMels;
    for (int i = 0; i < audioModel->melBands.size(); i++) {
        float scaledValue = ofMap(audioModel->melBands[i], DB_MIN, -1.0, 0.0, 1.0, true);
        float historyNormalized = ofMap(scaledValue, 0.0, peakMel, 0.0, 1.0, true);
        if (scaledValue > peakMel) {
            peakMel = scaledValue;
        }
        scaledMels.push_back(historyNormalized);
    }

    vector<float> foldedMels;
    int shrinkByTimes = scaledMels.size() / melToggles.size() ;
    int newSize = scaledMels.size() / shrinkByTimes;
    foldedMels.assign(newSize, 0);
    for (int i = 0; i < scaledMels.size(); i++) {
        foldedMels[i/shrinkByTimes] += scaledMels[i];
    }
    for (int i = 0; i < foldedMels.size(); i++) {
        foldedMels[i] /= (shrinkByTimes * 1.0);
    }

    float melEnergy = 0;
    for (int i = 0; i < melToggles.size(); i++) {
        if (melToggles[i] == true) {
            melEnergy += foldedMels[i];
        }
    }
    float kickFloat = multiplier * (pow(melEnergy, powerRatio) - melFloor);

    if (kickFloat > 1) {
        kickFloat = 1;
    } else if (kickFloat < 0) {
        kickFloat = 0;
    }

    ofColor strobeColor = ofColor::black;
    for (int i = 0; i < colorToggles.size(); i++) {
        if (colorToggles[i] == true) {
            strobeColor += pulseColors[i];
        }
    }

    vector<ofColor> mapped;
    for (ofColor color : colors) {
        ofColor mappedColor = color.lerp(strobeColor, kickFloat);
        mapped.push_back(mappedColor);
    }
    lastTransformation = mapped;
    return mapped;
}

void MelPulseTransformer::setup() {
    gui.setDefaultWidth(150);
    gui.setWidthElements(150);
    gui.setup();
    gui.setName("Mel Pulser");
    gui.add(isEnabled.setup("Is Enabled", true));
    gui.add(multiplier.setup("Multiplier", 4.0, 1.0, 8.0));
    gui.add(powerRatio.setup("Power", 4, 1, 8));
    gui.add(melFloor.setup("Mel Floor", 0.5, 0.0, 1.0));
    gui.add(mel0.setup("Bands 0-4", true));
    gui.add(mel1.setup("Bands 4-8", true));
    gui.add(mel2.setup("Bands 8-12", true));
    gui.add(mel3.setup("Bands 12-16", false));
    gui.add(mel4.setup("Bands 16-20", false));
    gui.add(mel5.setup("Bands 20-24", false));
    gui.add(mel6.setup("Bands 24-28", false));
    gui.add(mel7.setup("Bands 28-32", false));

    for (int i = 0; i < colorToggles.size(); i++) {
        colorToggles[i].setTextColor(pulseColors[i]);
        gui.add(colorToggles[i].setup("color", i == 0));
    }
}

void MelPulseTransformer::drawThumb(int x, int y, float w, float h) {
    if (context->audio.isReady == false) return;
    gui.setPosition(x, y-gui.getHeight());
    gui.draw();
    if (lastTransformation.size() > 0) {
        painter.draw(lastTransformation, x, y, w, h);
    }
}