//
//  DefaultVisual.cpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//

#include "DefaultVisual.hpp"
#include "math.h"

void DefaultVisual::setup() {
    gui.setup();
    gui.setName(name);
    gui.add(isEnabled.setup("Is Enabled", false));
    gui.add(maxNoteRatio.setup("Max Note Ratio", 0.5, 0.0, 1.0));
    gui.add(alphaSlider.setup("Alpha", 0.5, 0.0, 1.0));
    gui.add(powerSlider.setup("Power", 1, 0, 10));
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

void DefaultVisual::drawScene(int x, int y, float w, float h) {
    if (isEnabled) {
        drawVisual(x, y, w, h);
    }
}

void DefaultVisual::drawVisual(int x, int y, float w, float h) {
    float full_w = w;
    float bin_w = (float) w / 2 / audioModel->melBands.size();
    float graphH = h;
    
    peakMel = ofLerp(peakMel, 0.0, 0.01);
    
    // MEL
    ofPushMatrix();
    
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
        float amount = audioModel->hpcp[i] * pow(audioModel->power, powerSlider);
        mixer.lerp(filteredColors[colorIndex], amount);
    }
    
    // Mix Color
    mixColor.lerp(mixer, maxNoteRatio);
    
    int pivot = full_w / 2 + x;
    int pivotH = graphH / 2 + y;
    
    for (int i = 0; i < audioModel->melBands.size(); i++){
        //        DB_MAX
        float scaledValue = ofMap(audioModel->melBands[i], DB_MIN, -1.0, 0.0, 1.0, true); //clamped value
        float historyNormalized = ofMap(scaledValue, 0.0, peakMel, 0.0, 1.0, true);
        float bin_h = -1 * (historyNormalized * (graphH/2));
        
        if (scaledValue > peakMel) {
            peakMel = scaledValue;
        }
        
        ofColor drawColor = mixColor;
        
        ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
        
        // Add Color
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofSetColor(drawColor, (int) ((255 * alphaSlider)));
        
        // Right
        ofDrawRectangle(pivot + i*bin_w - bin_w, pivotH, bin_w, bin_h * -1);
        ofDrawRectangle(pivot + i*bin_w - bin_w, pivotH, bin_w, bin_h);
        
        // Left
        if (i != 0) {
            ofDrawRectangle(pivot - i*bin_w - bin_w, pivotH, bin_w, bin_h * -1);
            ofDrawRectangle(pivot - i*bin_w - bin_w, pivotH, bin_w, bin_h);
        }
    }

    ofDisableBlendMode();
    ofPopMatrix();
}

void DefaultVisual::drawThumb(int x, int y, float w, float h) {
    if (context->audio.isReady == false) return;
    gui.setPosition(x, y-gui.getHeight());
    gui.draw();
    
    drawVisual(x, y, w, h);
}



