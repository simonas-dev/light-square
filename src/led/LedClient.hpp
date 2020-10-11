//
//  LedClient.hpp
//  light-square
//
//  Created by Simonas Sankauskas on 2020-10-06.
//

#ifndef MatrixLedClient_hpp
#define MatrixLedClient_hpp

#include "ofMain.h"
#include "ofxOPC.h"

#endif /* MatrixLedClient_hpp */

class LedClient {
    ofxOPC opcClient;
    ofxNeoPixelGrid opcGrid;
    int stageWidth;
    int stageHeight;
    
public:
    void setup();
    void draw(vector<ofColor>);
    bool isConnected();
};
