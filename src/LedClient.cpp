//
//  LedClient.cpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//

#include "LedClient.hpp"

const int LED_COLS = 32;
const int LED_ROWS = 16;
int spacing;
void LedClient::setup(int _stageWidth, int _stageHeight) {
    stageWidth = _stageWidth;
    stageHeight = _stageHeight;
    spacing = stageWidth / LED_COLS;
    
    opcClient.setup("127.0.0.1", 7890);
    opcClient.setupStage(stageWidth, stageHeight);
    int iniPixelX = spacing / 2;
    int iniPixelY = spacing / 2;
    opcGrid.setupLedGrid(LED_COLS, LED_ROWS, iniPixelX, iniPixelY, spacing);
}
void LedClient::beginStage() {
    opcClient.update();
    opcClient.beginStage();
}

void LedClient::endStage() {
    opcClient.endStage();
    
    try {
        opcClient.getStagePixels(opcGrid.getPixelCoordinates(), opcGrid.colors);
        // If the client is not connected do not try and send information
        if (!opcClient.isConnected()) {
            // Will continue to try and reconnect to the Pixel Server
            opcClient.tryConnecting();
            opcClient.retryConnecting();
        } else {
            for (int channel = 1; channel <= 8; channel++) {
                vector<ofColor> gridData = opcGrid.colorData();
                int from = (channel-1) * 64;
                int to = channel * 64;
                vector<ofColor> chanelColorData(gridData.begin()+from, gridData.begin()+to);
                opcClient.writeChannel(channel, chanelColorData);
            }
        }
    } catch (...) {
        cout << "LED Write Failed!!";
    }
}

bool LedClient::isConnected() {
    return opcClient.isConnected();
}

void LedClient::drawStage() {
    opcClient.drawStage(true);
    opcGrid.drawGrabRegion(true);
    int xOffset = spacing / 2;
    int yOffset = spacing / 2;
    opcGrid.draw(stageWidth+xOffset, yOffset);
}

void LedClient::exit() {
    
}
