//
//  TransformationPainter.hpp
//  light-square
//
//  Created by Simonas Sankauskas on 2020-10-06.
//
#pragma once

#ifndef TransformationPainter_hpp
#define TransformationPainter_hpp

#include <ofMain.h>

#endif /* TransformationPainter_hpp */

class TransformationPainter {
    
public:
    void draw(vector<ofColor> colors, int x, int y, float w, float h) {
        ofPushMatrix();
        float rectHeight = h / 16;
        float rectWidth = w / 32;

        for (int row = 0; row < 16; row++) {
            for (int col = 0; col < 32; col++) {
                float rectX = x + rectWidth * col;
                float rectY = y + rectWidth * row;
                ofColor rectColor = colors[row * 32 + col];
                ofSetColor(rectColor);
                ofDrawRectangle(rectX, rectY, rectWidth, rectHeight);
            }
        }
        ofPopMatrix();
    }
};
