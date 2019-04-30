#pragma once

#include "ofMain.h"
#include "ofxAudioAnalyzer.h"
#include "ofSoundPlayerExtended.h"
#include "ofxGui.h"
#include "ofxGraph.h"
#include "AppContext.hpp"

class ofAllAlgsApp : public ofBaseApp {

    AppContext * context;
    
	public:
        ofAllAlgsApp(AppContext * appContext) {
            context = appContext;
        }
    
		void setup();
		void update();
		void draw();
        void exit();
    
        float rms;
        float power;
        float pitchFreq;
        float pitchFreqNorm;
        float pitchConf;
        float pitchSalience;
        float hfc;
        float hfcNorm;
        float specComp;
        float specCompNorm;
        float centroid;
        float centroidNorm;
        float inharmonicity;
        float dissonance;
        float rollOff;
        float rollOffNorm;
        float oddToEven;
        float oddToEvenNorm;
        float strongPeak;
        float strongPeakNorm;
        float strongDecay;
        float strongDecayNorm;
    
        vector<float> spectrum;
        vector<float> melBands;
        vector<float> mfcc;
        vector<float> hpcp;
    
        vector<float> tristimulus;
    
        bool isOnset;
    
    private:
        void setupHistogram(ofxGraph * graph, string name, int row, int col, int xOffset, int yOffset, int min, int max);
        void addHistogram(ofxGraph * graph, string name, int min, int max);
    
        ofxGraph rmsHistogram;
        ofxGraph powerHistogram;
        ofxGraph pitchFreqHistogram;
        ofxGraph pitchFreqNormHistogram;
        ofxGraph pitchConfHistogram;
        ofxGraph pitchSalienceHistogram;
        ofxGraph hfcNormHistogram;
        ofxGraph specCompNormHistogram;
        ofxGraph centroidNormHistogram;
        ofxGraph inharmonicityHistogram;
        ofxGraph dissonanceHistogram;
        ofxGraph rollOffNormHistogram;
        ofxGraph oddToEvenNormHistogram;
        ofxGraph strongPeakNormHistogram;
        ofxGraph strongDecayNormHistogram;
        ofxGraph isOnsetHistogram;
};
