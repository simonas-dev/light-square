//
//  DefaultVisual.cpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//

#include "DefaultVisual.hpp"

void DefaultVisual::drawThumb(int x, int y, float w, float h) {
    ofSetColor(ofColor::green);
    ofDrawRectangle(x, y, w, h);
}
