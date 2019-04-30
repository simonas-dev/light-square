//
//  StrobeVisual.hpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//
#pragma once

#ifndef StrobeVisual_hpp
#define StrobeVisual_hpp

#include "BaseVisual.hpp"

#endif /* RedVisual_hpp */

class StrobeVisual : public BaseVisual {
    
public:
    StrobeVisual(AppContext * appContext) {
        name = "Strobe Visual";
        context = appContext;
    };
    
    void setup();
    void drawScene(int x, int y, float w, float h);
    void drawVisual(int x, int y, float w, float h);
    void drawThumb(int x, int y, float w, float h);

    ofxFloatSlider fadeRatio;
    ofxFloatSlider powerRatio;
};
