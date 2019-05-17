//
//  SystemWindow.cpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//

#include "SystemWindow.hpp"

void SystemWindow::setup() {
    ofBackground(0);
    context->audio.setup();

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

void SystemWindow::update() {
    context->audio.update();

    if (context->audio.isReady == false) return;

    rmsHistogram.add(context->audio.model.rms);
    powerHistogram.add(context->audio.model.power);
    pitchFreqHistogram.add(context->audio.model.pitchFreq);
    pitchFreqNormHistogram.add(context->audio.model.pitchFreqNorm);
    pitchConfHistogram.add(context->audio.model.pitchConf);
    pitchSalienceHistogram.add(context->audio.model.pitchSalience);
    hfcNormHistogram.add(context->audio.model.hfcNorm);
    specCompNormHistogram.add(context->audio.model.specCompNorm);
    centroidNormHistogram.add(context->audio.model.centroidNorm);
    inharmonicityHistogram.add(context->audio.model.inharmonicity);
    dissonanceHistogram.add(context->audio.model.dissonance);
    rollOffNormHistogram.add(context->audio.model.rollOffNorm);
    oddToEvenNormHistogram.add(context->audio.model.oddToEvenNorm);
    strongPeakNormHistogram.add(context->audio.model.strongPeakNorm);
    strongDecayNormHistogram.add(context->audio.model.strongDecayNorm);
    isOnsetHistogram.add(context->audio.model.isOnset ? 1 : 0);
}

void SystemWindow::draw() {
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
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
    float bin_w = (float) barChartWidth / context->audio.model.spectrum.size();
    for (int i = 0; i < context->audio.model.spectrum.size(); i++){
        float scaledValue = ofMap(context->audio.model.spectrum[i], DB_MIN, DB_MAX, 0.0, 1.0, true);//clamped value
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
    bin_w = (float) barChartWidth / context->audio.model.melBands.size();
    for (int i = 0; i < context->audio.model.melBands.size(); i++){
        float scaledValue = ofMap(context->audio.model.melBands[i], DB_MIN, DB_MAX, 0.0, 1.0, true);//clamped value
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
    bin_w = (float) barChartWidth / context->audio.model.mfcc.size();
    for (int i = 0; i < context->audio.model.mfcc.size(); i++){
        float scaledValue = ofMap(context->audio.model.mfcc[i], 0, MFCC_MAX_ESTIMATED_VALUE, 0.0, 1.0, true);//clamped value
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
    bin_w = (float) barChartWidth / context->audio.model.hpcp.size();
    for (int i = 0; i < context->audio.model.hpcp.size(); i++){
        //float scaledValue = ofMap(hpcp[i], DB_MIN, DB_MAX, 0.0, 1.0, true);//clamped value
        float scaledValue = context->audio.model.hpcp[i];
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
    bin_w = (float) barChartWidth / context->audio.model.tristimulus.size();
    for (int i = 0; i < context->audio.model.tristimulus.size(); i++){
        //float scaledValue = ofMap(hpcp[i], DB_MIN, DB_MAX, 0.0, 1.0, true);//clamped value
        float scaledValue = context->audio.model.tristimulus[i];
        float bin_h = -1 * (scaledValue * graphH);
        ofDrawRectangle(i*bin_w, graphH, bin_w, bin_h);
    }
    ofPopMatrix();
    ofPopMatrix();
}

void SystemWindow::exit() {
    context->audio.exit();
}

void SystemWindow::addHistogram(Grapher * graph, string name, int min, int max) {
    int col = histogramIndex / maxRowCnt;
    int row = histogramIndex % maxRowCnt;
    setupHistogram(graph, name, row, col, 30, 30, min, max);
    histogramIndex++;
}

void SystemWindow::setupHistogram(Grapher * graph, string name, int row, int col, int xOffset, int yOffset, int min, int max) {
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