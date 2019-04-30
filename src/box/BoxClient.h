//
// Created by Simonas Sankauskas on 2019-04-26.
//

#ifndef LIGHT_SQUARE_BOXCLIENT_H
#define LIGHT_SQUARE_BOXCLIENT_H

#include "FcState.h"
#include "BoxResult.h"
#include "FcConfig.h"
#include "ofxHTTP.h"

class BoxClient {

private:
    ofxHTTP::Client client;
    string baseUrl = "localhost:8080";
    string stateUrl = baseUrl + "/fc";
public:
    BoxResult<FcState> getState();
    BoxResult<FcConfig> getConfig();
    BoxResult<bool> setConfig(FcConfig model);
    BoxResult<bool> start();
    BoxResult<bool> stop();
    BoxResult<bool> restart();
};


#endif //LIGHT_SQUARE_BOXCLIENT_H
