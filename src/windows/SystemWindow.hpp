//
//  SystemWindow.hpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//
#pragma once

#ifndef SystemWindow_hpp
#define SystemWindow_hpp

#include "ofMain.h"
#include "AppContext.hpp"
#include "Grapher.h"

#endif /* SystemWindow_hpp */

class SystemWindow : public ofBaseApp {
    AppContext * context;
    
public:
    SystemWindow(AppContext * appContext) {
        context = appContext;
    };
    void setup();
    void update();
    void draw();
    void exit();

private:
    int histogramIndex = 0;
    int maxRowCnt = 4;

    void setupHistogram(Grapher * graph, string name, int row, int col, int xOffset, int yOffset, int min, int max);
    void addHistogram(Grapher * graph, string name, int min, int max);

    Grapher rmsHistogram;
    Grapher powerHistogram;
    Grapher pitchFreqHistogram;
    Grapher pitchFreqNormHistogram;
    Grapher pitchConfHistogram;
    Grapher pitchSalienceHistogram;
    Grapher hfcNormHistogram;
    Grapher specCompNormHistogram;
    Grapher centroidNormHistogram;
    Grapher inharmonicityHistogram;
    Grapher dissonanceHistogram;
    Grapher rollOffNormHistogram;
    Grapher oddToEvenNormHistogram;
    Grapher strongPeakNormHistogram;
    Grapher strongDecayNormHistogram;
    Grapher isOnsetHistogram;
};
