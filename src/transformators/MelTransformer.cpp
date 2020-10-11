//
//  MelTransformer.cpp
//  light-square
//
//  Created by Simonas Sankauskas on 2020-10-10.
//

#include "MelTransformer.hpp"

vector<ofColor> MelTransformer::transform(vector<ofColor> colors) {
    if (context->audio.isReady == false) return colors;
    if (isEnabled == false) return colors;

    ofColor mixer = ofColor::black;
    vector<ofColor> filteredColors;
    if (color0 == true) {
        filteredColors.push_back(bandColors[0]);
    }
    if (color1 == true) {
        filteredColors.push_back(bandColors[1]);
    }
    if (color2 == true) {
        filteredColors.push_back(bandColors[2]);
    }
    if (color3 == true) {
        filteredColors.push_back(bandColors[3]);
    }
    if (color4 == true) {
        filteredColors.push_back(bandColors[4]);
    }
    if (color5 == true) {
        filteredColors.push_back(bandColors[5]);
    }
    if (color6 == true) {
        filteredColors.push_back(bandColors[6]);
    }
    if (color7 == true) {
        filteredColors.push_back(bandColors[7]);
    }
    if (color8 == true) {
        filteredColors.push_back(bandColors[8]);
    }
    if (color9 == true) {
        filteredColors.push_back(bandColors[9]);
    }
    if (color10 == true) {
        filteredColors.push_back(bandColors[10]);
    }
    if (color11 == true) {
        filteredColors.push_back(bandColors[11]);
    }

    int colorSize = filteredColors.size();
    int hpcpSize = audioModel->hpcp.size();
    for (int i = 0; i < hpcpSize && colorSize != 0; i++) {
        int colorIndex = round(((i * 1.f) / hpcpSize) * colorSize);
        float amount = audioModel->hpcp[i] * pow(audioModel->power, addSlider);
        mixer.lerp(filteredColors[colorIndex], amount);
    }

    mixColor.lerp(mixer, maxNoteRatio);

    vector<float> scaledMels;

    // 32 mel bands
    for (int i = 0; i < audioModel->melBands.size(); i++) {
        float scaledValue = ofMap(audioModel->melBands[i], DB_MIN, -1.0, 0.0, 1.0, true);
        float historyNormalized = ofMap(scaledValue, 0.0, peakMel, 0.0, 1.0, true);
        if (scaledValue > peakMel) {
            peakMel = scaledValue;
        }
        scaledMels.push_back(historyNormalized);
    }

    vector<ofColor> mutColors;
    for (int row = 0; row < 16; row++) {
        float rowRatio = (15 - row) / 15.0;
        for (int col = 0; col < 32; col++) {
            float melIndex = col > 15 ? col % 16 : 15 - col % 16;
            float mel = scaledMels[melIndex];
            int pixelIndex = row * 32 + col;
            if (mel > rowRatio) {
                ofColor mutColor = colors[pixelIndex].getLerped(mixColor, alphaSlider) + colors[pixelIndex].lerp(ofColor::black, addSlider);
                mutColors.push_back(mutColor);
            } else {
                mutColors.push_back(colors[pixelIndex]);
            }
        }
    }
    return mutColors;
}

void MelTransformer::setup() {
    gui.setup();
    gui.setName("Mel");
    gui.add(isEnabled.setup("Is Enabled", false));
    gui.add(maxNoteRatio.setup("Max Note Ratio", 0.5, 0.0, 1.0));
    gui.add(alphaSlider.setup("Alpha", 0.5, 0.0, 1.0));
    gui.add(addSlider.setup("Add", 0.0, 0.0, 1.0));
    color0.setTextColor(bandColors[0]);
    gui.add(color0.setup("color0", false));
    color1.setTextColor(bandColors[1]);
    gui.add(color1.setup("color1", false));
    color2.setTextColor(bandColors[2]);
    gui.add(color2.setup("color2", false));
    color3.setTextColor(bandColors[3]);
    gui.add(color3.setup("color3", false));
    color4.setTextColor(bandColors[4]);
    gui.add(color4.setup("color4", false));
    color5.setTextColor(bandColors[5]);
    gui.add(color5.setup("color5", false));
    color6.setTextColor(bandColors[6]);
    gui.add(color6.setup("color6", false));
    color7.setTextColor(bandColors[7]);
    gui.add(color7.setup("color7", false));
    color8.setTextColor(bandColors[8]);
    gui.add(color8.setup("color8", false));
    color9.setTextColor(bandColors[9]);
    gui.add(color9.setup("color9", false));
    color10.setTextColor(bandColors[10]);
    gui.add(color10.setup("color10", false));
    color11.setTextColor(bandColors[11]);
    gui.add(color11.setup("color11", false));
}

void MelTransformer::drawThumb(int x, int y, float w, float h) {
    if (context->audio.isReady == false) return;
    gui.setPosition(x, y-gui.getHeight());
    gui.draw();
    if (lastTransformation.size() > 0) {
        painter.draw(lastTransformation, x, y, w, h);
    }
}

