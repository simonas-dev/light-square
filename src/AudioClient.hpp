//
//  AudioClient.hpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//

#ifndef AudioClient_hpp
#define AudioClient_hpp

#include "ofxAudioAnalyzer.h"
#include "ofSoundPlayerExtended.h"
#include "AudioModel.hpp"

#endif /* AudioClient_hpp */

class AudioClient {
    ofxAudioAnalyzer audioAnalyzer;
    ofSoundStream soundStream;
    ofSoundBuffer soundBuffer;
    
public:
    bool isReady = false;
    AudioModel model;
    void setup();
    void setInput(ofSoundDevice device);
    vector<ofSoundDevice> getInputDevices();
    ofSoundDevice getDefaultInput();
    float smoothing;
    void audioIn(ofSoundBuffer & input);
    void update();
    void exit();
};
