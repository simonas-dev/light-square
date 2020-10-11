//
// Created by Simonas Sankauskas on 2020-10-11.
//
#pragma once

#ifndef LIGHT_SQUARE_BLEEDTRANSFORMER_HPP
#define LIGHT_SQUARE_BLEEDTRANSFORMER_HPP

#include <BaseTransformer.hpp>

class BleedTransformer : public BaseTransformer {
    vector<int> neighbourIndexes(int row, int col);
public:
    BleedTransformer(AppContext * appContext) {
        context = appContext;
    };
    ofxFloatSlider bleedRatio;
    vector<ofColor> transform(vector<ofColor> colors);
    void setup();
    void drawThumb(int x, int y, float w, float h);
};


#endif //LIGHT_SQUARE_BLEEDTRANSFORMER_HPP
