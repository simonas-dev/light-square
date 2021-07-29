//
//  FadeTransformer.cpp
//  light-square
//
//  Created by Simonas Sankauskas on 2020-10-06.
//
#include "CornerFadeTransformer.hpp"

void CornerFadeTransformer::setup() {
    gui.setDefaultWidth(150);
    gui.setWidthElements(150);
    gui.setup();
    gui.setName("Corner Fade");
    gui.add(isEnabled.setup("Is Enabled", true));
    gui.add(fadeRatio.setup("Fade Ratio", 0.001, 0.0, 0.01));
    gui.add(bleedRatio.setup("Bleed Ratio", 0.5, 0.0, 1.0));
}

vector<ofColor> CornerFadeTransformer::transform(vector<ofColor> colors) {
    if (isEnabled == false) return colors;

    vector<ofColor> mapped;
    mapped.assign(colors.size(), ofColor::black);
    // south-west
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 16; col++) {
            float nearbyBrightnessSum = 0;

            if (row != 0) {
                int x1 = col + ((row - 1) * 32);
                nearbyBrightnessSum += colors[x1].getBrightness();
            }

            if (col != 0) {
                int x2 = (col - 1) + (row * 32);
                nearbyBrightnessSum += colors[x2].getBrightness();
            }
            if (row != 0 && col != 0) {
                int x3 = (col - 1) + ((row - 1) * 32);
                nearbyBrightnessSum += colors[x3].getBrightness();
            }
            float avgNearbyBrightness = nearbyBrightnessSum / 3.0;

            int pixelIndex = row * 32 + col;
            ofColor color = ofColor(colors[pixelIndex]);
            float bleededBrightness = color.getBrightness() * (1 - bleedRatio) + avgNearbyBrightness * bleedRatio;
            color.setBrightness(bleededBrightness * (1 - fadeRatio));
            mapped[pixelIndex] = color;
        }
    }
    // south-east
    for (int row = 0; row < 8; row++) {
        for (int col = 16; col < 31; col++) {

            float nearbyBrightnessSum = 0;

            if (row != 0) {
                int x1 = col + ((row - 1) * 32);
                nearbyBrightnessSum += colors[x1].getBrightness();
            }

            if (col != 31) {
                int x2 = (col + 1) + (row * 32);
                nearbyBrightnessSum += colors[x2].getBrightness();
            }
            if (row != 0 && col != 31) {
                int x3 = (col + 1) + ((row - 1) * 32);
                nearbyBrightnessSum += colors[x3].getBrightness();
            }
            float avgNearbyBrightness = nearbyBrightnessSum / 3.0;

            int pixelIndex = row * 32 + col;
            ofColor color = ofColor(colors[pixelIndex]);
            float bleededBrightness = color.getBrightness() * (1 - bleedRatio) + avgNearbyBrightness * bleedRatio;
            color.setBrightness(bleededBrightness * (1 - fadeRatio));
            mapped[pixelIndex] = color;
        }
    }
    // north-west
    for (int row = 8; row < 15; row++) {
        for (int col = 0; col < 16; col++) {

            float nearbyBrightnessSum = 0;

            if (row != 15) {
                int x1 = col + ((row + 1) * 32);
                nearbyBrightnessSum += colors[x1].getBrightness();
            }

            if (col != 0) {
                int x2 = (col - 1) + (row * 32);
                nearbyBrightnessSum += colors[x2].getBrightness();
            }
            if (row != 15 && col != 0) {
                int x3 = (col - 1) + ((row + 1) * 32);
                nearbyBrightnessSum += colors[x3].getBrightness();
            }
            float avgNearbyBrightness = nearbyBrightnessSum / 3.0;

            int pixelIndex = row * 32 + col;
            ofColor color = ofColor(colors[pixelIndex]);
            float bleededBrightness = color.getBrightness() * (1 - bleedRatio) + avgNearbyBrightness * bleedRatio;
            color.setBrightness(bleededBrightness * (1 - fadeRatio));
            mapped[pixelIndex] = color;
        }
    }
    // north-east
    for (int row = 8; row < 15; row++) {
        for (int col = 16; col < 31; col++) {

            float nearbyBrightnessSum = 0;

            if (row != 15) {
                int x1 = col + ((row + 1) * 32);
                nearbyBrightnessSum += colors[x1].getBrightness();
            }

            if (col != 31) {
                int x2 = (col + 1) + (row * 32);
                nearbyBrightnessSum += colors[x2].getBrightness();
            }
            if (row != 15 && col != 31) {
                int x3 = (col + 1) + ((row + 1) * 32);
                nearbyBrightnessSum += colors[x3].getBrightness();
            }
            float avgNearbyBrightness = nearbyBrightnessSum / 3.0;

            int pixelIndex = row * 32 + col;
            ofColor color = ofColor(colors[pixelIndex]);
            float bleededBrightness = color.getBrightness() * (1 - bleedRatio) + avgNearbyBrightness * bleedRatio;
            color.setBrightness(bleededBrightness * (1 - fadeRatio));
            mapped[pixelIndex] = color;
        }
    }

    lastTransformation = mapped;
    return mapped;
}

void CornerFadeTransformer::drawThumb(int x, int y, float w, float h) {
    if (context->audio.isReady == false) return;
    gui.setPosition(x, y-gui.getHeight());
    gui.draw();
}
