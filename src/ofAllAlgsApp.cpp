
#include "ofAllAlgsApp.h"

bool isIniting = true;
int WINDOW_W = 1280;
int WINDOW_H = 800;

ofAllAlgsApp::ofAllAlgsApp() {

}

//--------------------------------------------------------------
void ofAllAlgsApp::setup(){
    ofBackground(34);
    ofSetFrameRate(60);
    
    soundStream.printDeviceList();
    
    ofSoundStreamSettings settings;
    ofSoundDevice device;
    
    auto devices = soundStream.getDeviceList(ofSoundDevice::Api::OSX_CORE);
    if(!devices.empty()){
        for (ofSoundDevice deviceItem : devices) {
            if (deviceItem.isDefaultInput) {
                device = deviceItem;
                settings.setInDevice(device);
            }
        }
    }
    
    float sampleRate = 44100;
    float bufferSize = 512;
    int inChannels = device.inputChannels;
    
    settings.setInListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 0;
    settings.numInputChannels = inChannels;
    settings.bufferSize = bufferSize;
    
    soundStream.setup(settings);
    
    audioAnalyzer.setup(sampleRate, bufferSize, inChannels);
    
    gui.setup();
    gui.setPosition(10, 500);
    gui.add(smoothing.setup("Smoothing", 0.0, 0.0, 1.0));
    
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
    int width = ((WINDOW_W-60)/4)-xMargin;
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

void ofAllAlgsApp::audioIn(ofSoundBuffer & input){
    soundBuffer = input;
    isIniting = false;
}

//--------------------------------------------------------------
void ofAllAlgsApp::update(){
    if (isIniting) return;
    
    ofSetWindowTitle("ofxAudioAnalyzer " + ofToString(ofGetFrameRate()));
    
    //-:ANALYZE SOUNDBUFFER:
    audioAnalyzer.analyze(soundBuffer);
    
    //-:get Values:
    rms = audioAnalyzer.getValue(RMS, 0, smoothing);
    power = audioAnalyzer.getValue(POWER, 0, smoothing);
    pitchFreq = audioAnalyzer.getValue(PITCH_FREQ, 0, smoothing);
    pitchConf = audioAnalyzer.getValue(PITCH_CONFIDENCE, 0, smoothing);
    pitchSalience = audioAnalyzer.getValue(PITCH_SALIENCE, 0, smoothing);
    inharmonicity = audioAnalyzer.getValue(INHARMONICITY, 0, smoothing);
    hfc = audioAnalyzer.getValue(HFC, 0, smoothing);
    specComp = audioAnalyzer.getValue(SPECTRAL_COMPLEXITY, 0, smoothing);
    centroid = audioAnalyzer.getValue(CENTROID, 0, smoothing);
    rollOff = audioAnalyzer.getValue(ROLL_OFF, 0, smoothing);
    oddToEven = audioAnalyzer.getValue(ODD_TO_EVEN, 0, smoothing);
    strongPeak = audioAnalyzer.getValue(STRONG_PEAK, 0, smoothing);
    strongDecay = audioAnalyzer.getValue(STRONG_DECAY, 0, smoothing);
    //Normalized values for graphic meters:
    pitchFreqNorm = audioAnalyzer.getValue(PITCH_FREQ, 0, smoothing, TRUE);
    hfcNorm = audioAnalyzer.getValue(HFC, 0, smoothing, TRUE);
    specCompNorm = audioAnalyzer.getValue(SPECTRAL_COMPLEXITY, 0, smoothing, TRUE);
    centroidNorm = audioAnalyzer.getValue(CENTROID, 0, smoothing, TRUE);
    rollOffNorm = audioAnalyzer.getValue(ROLL_OFF, 0, smoothing, TRUE);
    oddToEvenNorm = audioAnalyzer.getValue(ODD_TO_EVEN, 0, smoothing, TRUE);
    strongPeakNorm = audioAnalyzer.getValue(STRONG_PEAK, 0, smoothing, TRUE);
    strongDecayNorm = audioAnalyzer.getValue(STRONG_DECAY, 0, smoothing, TRUE);
    
    dissonance = audioAnalyzer.getValue(DISSONANCE, 0, smoothing);
    
    spectrum = audioAnalyzer.getValues(SPECTRUM, 0, smoothing);
    melBands = audioAnalyzer.getValues(MEL_BANDS, 0, smoothing);
    mfcc = audioAnalyzer.getValues(MFCC, 0, smoothing);
    hpcp = audioAnalyzer.getValues(HPCP, 0, smoothing);
    
    tristimulus = audioAnalyzer.getValues(TRISTIMULUS, 0, smoothing);
    
    isOnset = audioAnalyzer.getOnsetValue(0);
    
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
    if (isIniting) return;
    
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
        int barChartWidth = ((WINDOW_W-windowPadding)/5)-graphMargin;
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
    
    int barChartEnd = 550+graphH;
    
//    ofPushStyle();
//    ofColor hitColor = ofColor::pink;
//
//    ofPushMatrix();
//
//    ofSetColor(hitColor);
//    ofTranslate(30, barChartEnd);
//    ofDrawRectangle(0, 0, barChartWidth, 400);
//
//    ofPopMatrix();
//
//    ofPopStyle();

    gui.draw();
}

//--------------------------------------------------------------
void ofAllAlgsApp::exit(){
    audioAnalyzer.exit();
}
