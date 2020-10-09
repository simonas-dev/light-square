//
//  MatrixLedClient.cpp
//  light-square
//
//  Created by Simonas Sankauskas on 2020-10-06.
//

#include "MatrixLedClient.hpp"

void MatrixLedClient::setup() {
    opcClient.setup("127.0.0.1", 7890);
}

bool MatrixLedClient::isConnected() {
    return opcClient.isConnected();
}

void MatrixLedClient::draw(vector<ofColor> colors) {
    if (colors.size() != 512) throw std::runtime_error("length must be 512");
    // If the client is not connected do not try and send information
    if (!opcClient.isConnected()) {
        // Will continue to try and reconnect to the Pixel Server
        opcClient.tryConnecting();
        opcClient.retryConnecting();
    } else {
        for (int channel = 1; channel <= 8; channel++) {
            int from = (channel-1) * 64;
            int to = channel * 64;
            vector<ofColor> chanelColorData(colors.begin()+from, colors.begin()+to);
            opcClient.writeChannel(channel, chanelColorData);
        }
    }
}

