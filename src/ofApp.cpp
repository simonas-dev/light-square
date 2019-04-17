#include "ofApp.h"

float peakMel = 1.0f;
ofColor mixColor = ofColor::black;
float stageWidth = 320;

ofApp::ofApp(class ofAllAlgsApp * app) {
    ofAllAlgsApp = app;
}

//--------------------------------------------------------------
void ofApp::setup(){
    // We still want to draw on a black background, so we need to draw
    // the background before we do anything with the brush
    ofBackground(0);
    
    ofSetFrameRate(60);
    opcClient.setup("127.0.0.1", 7890);
//    opcClient.setup("192.168.88.175", 7890);
    
    opcClient.setupStage(stageWidth, 160);
    
    opcGridLeft.setupLedGrid(32, 16, 7, 5, 10);
    
    bandColors = {
        ofColor::fromHex(0xFF0000),
        ofColor::fromHex(0xFF7F00),
        ofColor::fromHex(0xFFFF00),
        ofColor::fromHex(0x7FFF00),
        ofColor::fromHex(0x00FF00),
        ofColor::fromHex(0x00FF7F),
        ofColor::fromHex(0x00FFFF),
        ofColor::fromHex(0x007FFF),
        ofColor::fromHex(0x0000FF),
        ofColor::fromHex(0x7F00FF),
        ofColor::fromHex(0xFF00FF),
        ofColor::fromHex(0xFF007F)
    };
    currentColor = ofColor::fromHex(0x000000);
    
    gui.setup();
    gui.setPosition(20, 500);
    gui.add(fadeRatio.setup  ("Fade Ratio", 0.035, 0.0, 0.35));
    gui.setPosition(20, 550);
    gui.add(maxNoteRatio.setup  ("Max Note Ratio", 0.02, 0.0, 1.0));
    gui.add(addOrBlendRatio.setup("Volume", 1.0, 0.0, 1.0));

    gui.add(onBeatToggle.setup("On Beat Toggle", true));
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(0);
    uint64_t mills = ofGetSystemTimeMillis();
    
    opcClient.update();
    opcClient.beginStage();

    float full_w = stageWidth;
    float bin_w = (float) full_w / 2 / ofAllAlgsApp->melBands.size();
    float graphH = 160;
    
    peakMel = ofLerp(peakMel, 0.0, 0.01);
    
//    ofSetColor(ofColor::green);
//    ofDrawRectangle(160, 0, full_w-320, 30);
//
//    ofSetColor(ofColor::red);
//    ofDrawRectangle(160, 80, full_w-320, 30);
//
//    ofSetColor(ofColor::blue);
//    ofDrawRectangle(160, 130, full_w-320, 30);
    
//    MEL
    ofPushMatrix();

    ofColor mixer = ofColor::black;
    for (int i = 0; i < ofAllAlgsApp->hpcp.size(); i++) {
        mixer.lerp(bandColors[i], ofAllAlgsApp->hpcp[i]);
    }

    // Mix Color
    mixColor.lerp(mixer, maxNoteRatio);


    int pivot = full_w / 2;
    int pivotH = graphH / 2;

    for (int i = 0; i < ofAllAlgsApp->melBands.size(); i++){
//        DB_MAX
        float scaledValue = ofMap(ofAllAlgsApp->melBands[i], DB_MIN, -1.0, 0.0, 1.0, true); //clamped value
        float historyNormalized = ofMap(scaledValue, 0.0, peakMel, 0.0, 1.0, true);
        float bin_h = -1 * (historyNormalized * graphH);

        if (scaledValue > peakMel) {
            peakMel = scaledValue;
        }

        ofColor drawColor = mixColor;
        if (onBeatToggle && ofAllAlgsApp->isOnset) {
            drawColor = currentColor.getLerped(ofColor(255,255,255,85), pow(ofAllAlgsApp->power, 3));
        }

//        drawColor.lerp(ofColor::black, hfcNorm*10000);

        ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);

        // Add Color
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofSetColor(drawColor, (int) ((255 * addOrBlendRatio)));

        // Right
        ofDrawRectangle(pivot + i*bin_w, pivotH, bin_w, bin_h * -1);
        ofDrawRectangle(pivot + i*bin_w, pivotH, bin_w, bin_h);

        // Left
        ofDrawRectangle(pivot - i*bin_w, pivotH, bin_w, bin_h * -1);
        ofDrawRectangle(pivot - i*bin_w, pivotH, bin_w, bin_h);
    }

    // Fade the Scene
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(ofColor::black, (int) (255*fadeRatio));
    ofDrawRectangle(0, 0, full_w, 160);
    ofSetColor(ofColor::black, 3);
    ofDrawRectangle(0, 0, full_w, 160);
    ofDisableBlendMode();

    ofPopMatrix();
    
    opcClient.endStage();
    
    try {
        opcClient.getStagePixels(opcGridLeft.getPixelCoordinates(), opcGridLeft.colors);
        // If the client is not connected do not try and send information
        if (!opcClient.isConnected()) {
            // Will continue to try and reconnect to the Pixel Server
            opcClient.tryConnecting();
            opcClient.retryConnecting();
        } else {
            for (int channel = 1; channel <= 8; channel++) {
                vector<ofColor> gridData = opcGridLeft.colorData();
                int from = (channel-1) * 64;
                int to = channel * 64;
                vector<ofColor> chanelColorData(gridData.begin()+from, gridData.begin()+to);
                opcClient.writeChannel(channel, chanelColorData);
            }
        }
    } catch (...) {
        cout << "LED Write Failed!!";
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    gui.draw();
    
    opcClient.drawStage(true);
    
    opcGridLeft.drawGrabRegion(true);
    opcGridLeft.draw(20, 300);
    
}

void ofApp::exit(){
    
}
