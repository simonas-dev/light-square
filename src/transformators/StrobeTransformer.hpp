//
//  StrobeTransformer.hpp
//  light-square
//
//  Created by Simonas Sankauskas on 2020-10-06.
//
#pragma once
#ifndef StrobeTransformer_hpp
#define StrobeTransformer_hpp

#include "BaseTransformer.hpp"

#endif /* StrobeTransformer_hpp */

class StrobeTransformer : public BaseTransformer {
public:
    StrobeTransformer(AppContext * appContext) {
        context = appContext;
    };
    ofxFloatSlider powerRatio;
    ofxFloatSlider randomization;
    TransformationPainter painter;
    vector<ofColor> transform(vector<ofColor> colors);
    void setup();
    void drawThumb(int x, int y, float w, float h);
};
