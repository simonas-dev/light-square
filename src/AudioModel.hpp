//
//  AudioModel.hpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//

#ifndef AudioModel_hpp
#define AudioModel_hpp

#include <stdio.h>
#include "ofMain.h"

#endif /* AudioModel_hpp */

class AudioModel {
    
public:
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
};
