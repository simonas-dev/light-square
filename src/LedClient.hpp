//
//  LedClient.hpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//

#ifndef LedClient_hpp
#define LedClient_hpp

#include "ofMain"
#include "ofxOPC.h"

#endif /* LedClient_hpp */

class LedClient {
    ofxOPC opcClient;
    ofxNeoPixelGrid opcGrid;
    
    
public: 
    void setup();
    void beginStage();
    void endStage();
    bool isConnected();
    void drawStage();
    void exit();
};
