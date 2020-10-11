//
// Created by Simonas Sankauskas on 2020-10-11.
//

#include "BleedTransformer.hpp"

void BleedTransformer::drawThumb(int x, int y, float w, float h) {
    gui.setPosition(x, y-gui.getHeight());
    gui.draw();
}

void BleedTransformer::setup() {
    gui.setup();
    gui.setName("Bleed");
    gui.add(isEnabled.setup("Is Enabled", false));
    gui.add(bleedRatio.setup("Bleed", 0.0, 0.0, 1.0));
}

vector<ofColor> BleedTransformer::transform(vector<ofColor> colors) {
    for (int row = 0; row < 16; row++) {
        for (int col = 0; col < 32; col++) {
            int pixelIndex = row * 32 + col;
            ofColor color = colors[pixelIndex];
            for (int neighbour : neighbourIndexes(row, col)) {
                if (colors[neighbour].getBrightness() < color.getBrightness()) {
                    int tempNeighbour = colors[neighbour].getHex();
                    colors[neighbour].lerp(color, bleedRatio);
                    color.lerp(ofColor(tempNeighbour), bleedRatio);
                }
            }
        }
    }
    return colors;
}

vector<int> BleedTransformer::neighbourIndexes(int row, int col) {
    int flatIndex = row * 32 + col;
    vector<int> neighbours;
    if (col > 0) {
        neighbours.push_back(flatIndex - 1);
        if (row > 0) {
            neighbours.push_back(flatIndex - 32 - 1);
        }
    }
    if (col < 31) {
        neighbours.push_back(flatIndex + 1);
        if (row < 15) {
            neighbours.push_back(flatIndex + 32 + 1);
        }
    }
    if (row > 0) {
        neighbours.push_back(flatIndex - 32);
    }
    if (row < 15) {
        neighbours.push_back(flatIndex + 32);
    }
    return neighbours;
}
