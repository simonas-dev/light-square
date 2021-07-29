#include "ofMain.h"
#include "ofAppGLFWWindow.h"
#include "SystemWindow.hpp"
#include "VisualMixerWindow.hpp"

int main() {
    ofGLWindowSettings settings;

    shared_ptr<AppContext> context(new AppContext());

    settings.setSize(1280, 800);
    settings.setPosition(ofVec2f(300,0));
    shared_ptr<ofAppBaseWindow> systemWindow = ofCreateWindow(settings);
    shared_ptr<SystemWindow> systemApp(new SystemWindow(context.get()));
    ofRunApp(systemWindow, systemApp);


    settings.setSize(1280, 840);
    settings.setPosition(ofVec2f(300,0));
    shared_ptr<ofAppBaseWindow> mixerWindow = ofCreateWindow(settings);
    shared_ptr<VisualMixerWindow> mixerApp(new VisualMixerWindow(context.get()));
    ofRunApp(mixerWindow, mixerApp);

    ofRunMainLoop();
}