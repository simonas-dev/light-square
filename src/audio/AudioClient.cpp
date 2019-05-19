//
//  AudioClient.cpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//

#include "AudioClient.hpp"

void AudioClient::setup() {
    setInput(getDefaultInput());
}

void AudioClient::update() {
    if (isReady == false) return;
    
    audioAnalyzer.analyze(soundBuffer);
    
    model.rms = audioAnalyzer.getValue(RMS, 0, smoothing);
    model.power = audioAnalyzer.getValue(POWER, 0, smoothing);
    model.pitchFreq = audioAnalyzer.getValue(PITCH_FREQ, 0, smoothing);
    model.pitchConf = audioAnalyzer.getValue(PITCH_CONFIDENCE, 0, smoothing);
    model.pitchSalience = audioAnalyzer.getValue(PITCH_SALIENCE, 0, smoothing);
    model.inharmonicity = audioAnalyzer.getValue(INHARMONICITY, 0, smoothing);
    model.hfc = audioAnalyzer.getValue(HFC, 0, smoothing);
    model.specComp = audioAnalyzer.getValue(SPECTRAL_COMPLEXITY, 0, smoothing);
    model.centroid = audioAnalyzer.getValue(CENTROID, 0, smoothing);
    model.rollOff = audioAnalyzer.getValue(ROLL_OFF, 0, smoothing);
    model.oddToEven = audioAnalyzer.getValue(ODD_TO_EVEN, 0, smoothing);
    model.strongPeak = audioAnalyzer.getValue(STRONG_PEAK, 0, smoothing);
    model.strongDecay = audioAnalyzer.getValue(STRONG_DECAY, 0, smoothing);
    //Normalized values for graphic meters:
    model.pitchFreqNorm = audioAnalyzer.getValue(PITCH_FREQ, 0, smoothing, TRUE);
    model.hfcNorm = audioAnalyzer.getValue(HFC, 0, smoothing, TRUE);
    model.specCompNorm = audioAnalyzer.getValue(SPECTRAL_COMPLEXITY, 0, smoothing, TRUE);
    model.centroidNorm = audioAnalyzer.getValue(CENTROID, 0, smoothing, TRUE);
    model.rollOffNorm = audioAnalyzer.getValue(ROLL_OFF, 0, smoothing, TRUE);
    model.oddToEvenNorm = audioAnalyzer.getValue(ODD_TO_EVEN, 0, smoothing, TRUE);
    model.strongPeakNorm = audioAnalyzer.getValue(STRONG_PEAK, 0, smoothing, TRUE);
    model.strongDecayNorm = audioAnalyzer.getValue(STRONG_DECAY, 0, smoothing, TRUE);
    
    model.dissonance = audioAnalyzer.getValue(DISSONANCE, 0, smoothing);
    
    model.spectrum = audioAnalyzer.getValues(SPECTRUM, 0, smoothing);
    model.melBands = audioAnalyzer.getValues(MEL_BANDS, 0, smoothing);
    model.mfcc = audioAnalyzer.getValues(MFCC, 0, smoothing);
    model.hpcp = audioAnalyzer.getValues(HPCP, 0, smoothing);
    
    model.tristimulus = audioAnalyzer.getValues(TRISTIMULUS, 0, smoothing);
    
    model.isOnset = audioAnalyzer.getOnsetValue(0);
}

void AudioClient::exit() {
    audioAnalyzer.exit();
}

void AudioClient::setInput(ofSoundDevice device) {
    ofSoundStreamSettings settings;
    
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
}

vector<ofSoundDevice> AudioClient::getInputDevices() {
    return soundStream.getDeviceList(ofSoundDevice::Api::OSX_CORE);
}

void AudioClient::audioIn(ofSoundBuffer & input) {
    soundBuffer = input;
    isReady = true;
}

ofSoundDevice AudioClient::getDefaultInput() {
    auto devices = getInputDevices();
    if(!devices.empty()){
        for (ofSoundDevice deviceItem : devices) {
            if (deviceItem.isDefaultInput) {
                return deviceItem;
            }
        }
    }
    throw "No Input Devices Found";
}
