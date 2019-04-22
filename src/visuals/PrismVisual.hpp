//
//  PrismVisual.hpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/22/19.
//

#ifndef PrismVisual_hpp
#define PrismVisual_hpp

#include "BaseVisual.hpp"
#include "ofxShadertoy.h"

#endif /* PrismVisual_hpp */

class PrismVisual : public BaseVisual {
    
public:
    PrismVisual(AppContext * appContext) {
        name = "Prisim Visual";
        context = appContext;
    };
    
    ofxShadertoy shadertoy;
    ofxToggle reloadShader;
    
    void setup();
    void drawScene(int x, int y, float w, float h);
    void drawVisual(int x, int y, float w, float h);
    void drawThumb(int x, int y, float w, float h);
};
