
#include "ofAllAlgsApp.h"

//--------------------------------------------------------------
void ofAllAlgsApp::setup(){
    ofBackground(34);
    ofSetFrameRate(60);
    
    // Histograms
    
    addHistogram(&rmsHistogram, "RMS", 0, 1);
    addHistogram(&powerHistogram, "Power", 0, 1);
    addHistogram(&pitchFreqHistogram, "Pitch Freq", 0, 12000);
    addHistogram(&pitchFreqNormHistogram, "Pitch Freq Norm", 0, 1);
    addHistogram(&pitchConfHistogram, "Pitch Conf", 0, 1);
    addHistogram(&pitchSalienceHistogram, "Pitch Salience", 0, 1);
    addHistogram(&hfcNormHistogram, "HFC Norm", 0, 1);
    addHistogram(&specCompNormHistogram, "Spec Comp Norm", 0, 1);
    addHistogram(&centroidNormHistogram, "Centroid Norm", 0, 1);
    addHistogram(&inharmonicityHistogram, "Inharmonicity", 0, 1);
    addHistogram(&dissonanceHistogram, "Dissonance", 0, 1);
    addHistogram(&rollOffNormHistogram, "Roll Off Norm", 0, 1);
    addHistogram(&oddToEvenNormHistogram, "Odd To Even Norm", 0, 1);
    addHistogram(&strongPeakNormHistogram, "Strong Peak Norm", 0, 1);
    addHistogram(&strongDecayNormHistogram, "Strong Decay Norm", 0, 1);
    addHistogram(&isOnsetHistogram, "Is Onset", 0, 1);
}

int histogramIndex = 0;
int maxRowCnt = 4;
void ofAllAlgsApp::addHistogram(ofxGraph * graph, string name, int min, int max) {
    int col = histogramIndex / maxRowCnt;
    int row = histogramIndex % maxRowCnt;
    setupHistogram(graph, name, row, col, 30, 30, min, max);
    histogramIndex++;
}

void ofAllAlgsApp::setupHistogram(ofxGraph * graph, string name, int row, int col, int xOffset, int yOffset, int min, int max) {
    int height = 100;
    int xMargin = 10;
    int yMargin = 20;
    int width = ((ofGetWidth()-60)/4)-xMargin;
    int x = (width*col + xMargin*col)+xOffset;
    int y = (row*height + yMargin*row)+yOffset;
    graph->setup(name);
    graph->min_data=min;
    graph->max_data=max;
    graph->setPosition(x, y);
    graph->setSize(width, height);
    graph->setBufSize(128);
    graph->setColor(ofColor::cyan);
}

//--------------------------------------------------------------
void ofAllAlgsApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    if (context->audio.isReady == false) return;
    
    //-:get Values:
    rms = context->audio.model.rms;
    power = context->audio.model.power;
    pitchFreq = context->audio.model.pitchFreq;
    pitchConf = context->audio.model.pitchConf;
    pitchSalience = context->audio.model.pitchSalience;
    inharmonicity = context->audio.model.inharmonicity;
    hfc = context->audio.model.hfc;
    specComp = context->audio.model.specComp;
    centroid = context->audio.model.centroid;
    rollOff = context->audio.model.rollOff;
    oddToEven = context->audio.model.oddToEven;
    strongPeak = context->audio.model.strongPeak;
    strongDecay = context->audio.model.strongDecay;
    //Normalized values for graphic meters:
    pitchFreqNorm = context->audio.model.pitchFreqNorm;
    hfcNorm = context->audio.model.hfcNorm;
    specCompNorm = context->audio.model.specCompNorm;
    centroidNorm = context->audio.model.centroidNorm;
    rollOffNorm = context->audio.model.rollOffNorm;
    oddToEvenNorm = context->audio.model.oddToEvenNorm;
    strongPeakNorm = context->audio.model.strongPeakNorm;
    strongDecayNorm = context->audio.model.strongDecayNorm;
    
    dissonance = context->audio.model.dissonance;
    
    spectrum = context->audio.model.spectrum;
    melBands = context->audio.model.melBands;
    mfcc = context->audio.model.mfcc;
    hpcp = context->audio.model.hpcp;
    
    tristimulus = context->audio.model.tristimulus;
    
    isOnset = context->audio.model.isOnset;
    
    rmsHistogram.add(rms);
    powerHistogram.add(power);
    pitchFreqHistogram.add(pitchFreq);
    pitchFreqNormHistogram.add(pitchFreqNorm);
    pitchConfHistogram.add(pitchConf);
    pitchSalienceHistogram.add(pitchSalience);
    hfcNormHistogram.add(hfcNorm);
    specCompNormHistogram.add(specCompNorm);
    centroidNormHistogram.add(centroidNorm);
    inharmonicityHistogram.add(inharmonicity);
    dissonanceHistogram.add(dissonance);
    rollOffNormHistogram.add(rollOffNorm);
    oddToEvenNormHistogram.add(oddToEvenNorm);
    strongPeakNormHistogram.add(strongPeakNorm);
    strongDecayNormHistogram.add(strongDecayNorm);
    isOnsetHistogram.add(isOnset ? 1 : 0);
}

//--------------------------------------------------------------
void ofAllAlgsApp::draw(){
    if (context->audio.isReady == false) return;
    
    ofPushStyle();
        rmsHistogram.draw();
        powerHistogram.draw();
        pitchFreqHistogram.draw();
        pitchFreqNormHistogram.draw();
        pitchConfHistogram.draw();
        pitchSalienceHistogram.draw();
        hfcNormHistogram.draw();
        specCompNormHistogram.draw();
        centroidNormHistogram.draw();
        inharmonicityHistogram.draw();
        dissonanceHistogram.draw();
        rollOffNormHistogram.draw();
        oddToEvenNormHistogram.draw();
        strongPeakNormHistogram.draw();
        strongDecayNormHistogram.draw();
        isOnsetHistogram.draw();
    ofPopStyle();
    
    int histogramEnd = 550;
    
    ofPushMatrix();
        ofColor textColor = ofColor::white;
        ofColor barColor = ofColor::cyan;
    
        int windowPadding = 60;
        int graphMargin = 10;
        int barChartWidth = ((ofGetWidth()-windowPadding)/5)-graphMargin;
        int graphH = 75;
        int xoffset = barChartWidth + graphMargin;
        int ypos = histogramEnd;
        int xpos = 30;
    
        ofSetColor(textColor);
        ofDrawBitmapString("Spectrum: ", xpos, ypos);
        ofPushMatrix();
        ofTranslate(xpos, ypos);
        ofSetColor(barColor);
        float bin_w = (float) barChartWidth / spectrum.size();
        for (int i = 0; i < spectrum.size(); i++){
            float scaledValue = ofMap(spectrum[i], DB_MIN, DB_MAX, 0.0, 1.0, true);//clamped value
            float bin_h = -1 * (scaledValue * graphH);
            ofDrawRectangle(i*bin_w, graphH, bin_w, bin_h);
        }
        ofPopMatrix();

        xpos += xoffset;
        ofSetColor(textColor);
        ofDrawBitmapString("Mel Bands: ", xpos, ypos);
        ofPushMatrix();
        ofTranslate(xpos, ypos);
        ofSetColor(barColor);
        bin_w = (float) barChartWidth / melBands.size();
        for (int i = 0; i < melBands.size(); i++){
            float scaledValue = ofMap(melBands[i], DB_MIN, DB_MAX, 0.0, 1.0, true);//clamped value
            float bin_h = -1 * (scaledValue * graphH);
            ofDrawRectangle(i*bin_w, graphH, bin_w, bin_h);
        }
        ofPopMatrix();

        xpos += xoffset;
        ofSetColor(textColor);
        ofDrawBitmapString("MFCC: ", xpos, ypos);
        ofPushMatrix();
        ofTranslate(xpos, ypos);
        ofSetColor(barColor);
        bin_w = (float) barChartWidth / mfcc.size();
        for (int i = 0; i < mfcc.size(); i++){
            float scaledValue = ofMap(mfcc[i], 0, MFCC_MAX_ESTIMATED_VALUE, 0.0, 1.0, true);//clamped value
            float bin_h = -1 * (scaledValue * graphH);
            ofDrawRectangle(i*bin_w, graphH, bin_w, bin_h);
        }
        ofPopMatrix();

        xpos += xoffset;
        ofSetColor(textColor);
        ofDrawBitmapString("HPCP: ", xpos, ypos);
        ofPushMatrix();
        ofTranslate(xpos, ypos);
        ofSetColor(barColor);
        bin_w = (float) barChartWidth / hpcp.size();
        for (int i = 0; i < hpcp.size(); i++){
            //float scaledValue = ofMap(hpcp[i], DB_MIN, DB_MAX, 0.0, 1.0, true);//clamped value
            float scaledValue = hpcp[i];
            float bin_h = -1 * (scaledValue * graphH);
            ofDrawRectangle(i*bin_w, graphH, bin_w, bin_h);
        }
        ofPopMatrix();

        xpos += xoffset;
        ofSetColor(textColor);
        ofDrawBitmapString("Tristimulus: ", xpos, ypos);
        ofPushMatrix();
        ofTranslate(xpos, ypos);
        ofSetColor(barColor);
        bin_w = (float) barChartWidth / tristimulus.size();
        for (int i = 0; i < tristimulus.size(); i++){
            //float scaledValue = ofMap(hpcp[i], DB_MIN, DB_MAX, 0.0, 1.0, true);//clamped value
            float scaledValue = tristimulus[i];
            float bin_h = -1 * (scaledValue * graphH);
            ofDrawRectangle(i*bin_w, graphH, bin_w, bin_h);
        }
        ofPopMatrix();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofAllAlgsApp::exit(){
    
}
