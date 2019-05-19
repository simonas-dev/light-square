//
//  DefaultVisual.cpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//

#include "DefaultVisual.hpp"

void DefaultVisual::setup() {
    gui.setup();
    gui.setName(name);
    gui.add(isEnabled.setup("Is Enabled", true));
    gui.add(fadeRatio.setup("Fade Ratio", 0.035, 0.0, 0.35));
    gui.add(maxNoteRatio.setup("Max Note Ratio", 0.02, 0.0, 1.0));
    gui.add(addOrBlendRatio.setup("Volume", 1.0, 0.0, 1.0));
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
    
    //    MEL
    ofPushMatrix();
    
    ofColor mixer = ofColor::black;
    for (int i = 0; i < audioModel->hpcp.size(); i++) {
        mixer.lerp(bandColors[i], audioModel->hpcp[i]);
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
        
        //        drawColor.lerp(ofColor::black, hfcNorm*10000);
        
        ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
        
        // Add Color
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofSetColor(drawColor, (int) ((255 * addOrBlendRatio)));
        
        // Right
        ofDrawRectangle(pivot + i*bin_w - bin_w, pivotH, bin_w, bin_h * -1);
        ofDrawRectangle(pivot + i*bin_w - bin_w, pivotH, bin_w, bin_h);
        
        // Left
        if (i != 0) {
            ofDrawRectangle(pivot - i*bin_w - bin_w, pivotH, bin_w, bin_h * -1);
            ofDrawRectangle(pivot - i*bin_w - bin_w, pivotH, bin_w, bin_h);
        }
    }
    
    // Fade the Scene
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    int fade =  (255*fadeRatio);
    if (fade == 0 && fadeRatio > 0) {
        fade = 1;
    }
    ofSetColor(ofColor::black, fade);
    ofDisableBlendMode();
    
    ofPopMatrix();
}

void DefaultVisual::drawThumb(int x, int y, float w, float h) {
    if (context->audio.isReady == false) return;
    gui.setPosition(x, y-gui.getHeight());
    gui.draw();
    
    drawVisual(x, y, w, h);
}



