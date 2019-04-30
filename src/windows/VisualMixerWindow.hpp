//
//  VisualMixerWindow.hpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//
#pragma once

#ifndef VisualMixerWindow_hpp
#define VisualMixerWindow_hpp

#include "ofMain.h"
#include "AppContext.hpp"
#include "visual/BaseVisual.hpp"
#include "visual/DefaultVisual.hpp"
#include "visual/StrobeVisual.hpp"
#include "visual/PrismVisual.hpp"

#endif /* VisualMixerWindow_hpp */

class VisualMixerWindow : public ofBaseApp {
    AppContext * context;
    vector<BaseVisual*> visuals;
    
public:
    VisualMixerWindow(AppContext * appContext) {
        context = appContext;
        visuals = {
            new DefaultVisual(context),
            new StrobeVisual(context),
            new PrismVisual(context)
        };
    };
    void setup();
    void update();
    void draw();
    void exit();
};
