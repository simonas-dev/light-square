//
//  FadeTransformer.hpp
//  light-square
//
//  Created by Simonas Sankauskas on 2020-10-06.
//
#pragma once

#ifndef FadeTransformator_hpp
#define FadeTransformator_hpp

#include <BaseTransformer.hpp>

#endif /* FadeTransformer_hpp */

class CornerFadeTransformer : public BaseTransformer {
public:
    CornerFadeTransformer(AppContext * appContext) {
        context = appContext;
    };
    ofxFloatSlider fadeRatio;
    ofxFloatSlider bleedRatio;
    vector<ofColor> transform(vector<ofColor> colors);
    void setup();
    void drawThumb(int x, int y, float w, float h);
};
