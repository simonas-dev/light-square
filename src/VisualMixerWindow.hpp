//
//  VisualMixerWindow.hpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//
#pragma once

#ifndef VisualMixerWindow_hpp
#define VisualMixerWindow_hpp

#include <ofMain.h>
#include <AppContext.hpp>

#endif /* VisualMixerWindow_hpp */

class VisualMixerWindow : public ofBaseApp {
    AppContext * context;
    
public:
    VisualMixerWindow(AppContext * appContext) {
        context = appContext;
    };
    void setup();
    void update();
    void draw();
    void exit();
};
