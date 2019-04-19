//
//  RedVisual.cpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//

#include "RedVisual.hpp"


void RedVisual::drawThumb(int x, int y, float w, float h) {
    ofSetColor(ofColor::red);
    ofDrawRectangle(x, y, w, h);
}
