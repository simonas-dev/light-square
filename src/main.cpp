#include "ofMain.h"
#include "ofApp.h"
#include "ofAllAlgsApp.h"
#include "ofAppGLFWWindow.h"
#include "ofAppGLFWWindow.h"
#include "SystemWindow.hpp"

int main() {
    ofGLFWWindowSettings settings;
//
//    settings.setSize(1280, 800);
//    settings.setPosition(ofVec2f(300,0));
//    settings.resizable = true;
//    shared_ptr<ofAppBaseWindow> stageWindow = ofCreateWindow(settings);
//
//    settings.setSize(1280, 800);
//    settings.setPosition(ofVec2f(0,0));
//    settings.resizable = false;
//    shared_ptr<ofAppBaseWindow> algoWindow = ofCreateWindow(settings);
//
//    shared_ptr<ofAllAlgsApp> algoApp(new ofAllAlgsApp());
//    shared_ptr<ofApp> stageApp(new ofApp(algoApp.get()));
//
//    ofRunApp(algoWindow, algoApp);
//    ofRunApp(stageWindow, stageApp);
    
    
    shared_ptr<AppContext> context(new AppContext());
    
    settings.setSize(1280, 800);
    settings.setPosition(ofVec2f(300,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> systemWindow = ofCreateWindow(settings);
    shared_ptr<SystemWindow> stageApp(new SystemWindow(context.get()));
    ofRunApp(systemWindow, stageApp);

    ofRunMainLoop();
}
