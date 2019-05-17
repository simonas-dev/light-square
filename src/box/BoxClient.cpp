//
// Created by Simonas Sankauskas on 2019-04-26.
//

#include "BoxClient.h"

BoxResult<FcState> BoxClient::getState() {
    ofxHTTP::GetRequest request(stateUrl);

    return BoxResult<FcState>();
}

BoxResult<FcConfig> BoxClient::getConfig() {
    return BoxResult<FcConfig>();
}

BoxResult<bool> BoxClient::setConfig(FcConfig model) {
    return BoxResult<bool>();
}

BoxResult<bool> BoxClient::start() {
    return BoxResult<bool>();
}

BoxResult<bool> BoxClient::stop() {
    return BoxResult<bool>();
}

BoxResult<bool> BoxClient::restart() {
    return BoxResult<bool>();
}
