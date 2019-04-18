//
//  LedClient.cpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//

#include "LedClient.hpp"

void LedClient::setup() {
    opcClient.setup("127.0.0.1", 7890);
    opcClient.setupStage(320, 160);
    opcGrid.setupLedGrid(32, 16, 7, 5, 10);
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
    opcGrid.draw(20, 300);
}

void LedClient::exit() {
    
}
