#pragma once

#include "ofMain.h"
#include "ofxOPC.h"
#include "ofAllAlgsApp.h"

class ofApp : public ofBaseApp{

	public:
        ofApp(ofAllAlgsApp * app);
    
		void setup();
		void update();
		void draw();
        void exit();
    
        ofAllAlgsApp* ofAllAlgsApp;
    
        ofxOPC opcClient;
        ofxNeoPixelGrid opcGridLeft;
        ofxNeoPixelGrid opcGridRight;
        ofxNeoPixelGrid opcGridCenter;
    
        ofColor currentColor;
        vector<ofColor> bandColors;
    
        ofxPanel gui;
        ofxFloatSlider maxNoteRatio;
        ofxFloatSlider fadeRatio;
        ofxFloatSlider addOrBlendRatio;
        ofxToggle onBeatToggle;
};
