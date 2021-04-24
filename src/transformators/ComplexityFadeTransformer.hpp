//
//  ComplexityFadeTransformer.hpp
//  light-square
//
//  Created by Simonas Sankauskas on 2020-10-06.
//
#pragma once

#ifndef ComplexityFadeTransformer_hpp
#define ComplexityFadeTransformer_hpp

#include <BaseTransformer.hpp>

#endif /* ComplexityFadeTransformer_hpp */

class ComplexityFadeTransformer : public BaseTransformer {
public:
    ComplexityFadeTransformer(AppContext * appContext) {
        context = appContext;
    };
    ofxFloatSlider fadeRatio;
    ofxFloatSlider dropOff;
    float rollingComplexity = 0;
    vector<ofColor> transform(vector<ofColor> colors);
    void setup();
    void drawThumb(int x, int y, float w, float h);
};
