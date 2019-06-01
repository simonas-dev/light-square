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

class FadeVisual : public BaseVisual {
    
public:
    FadeVisual(AppContext * appContext) {
        name = "Fade Visual";
        context = appContext;
    };
    
    void setup();
    void drawScene(int x, int y, float w, float h);
    void drawVisual(int x, int y, float w, float h);
    void drawThumb(int x, int y, float w, float h);

    ofxFloatSlider fadeRatio;
};
