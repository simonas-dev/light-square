//
// Created by Simonas Sankauskas on 2019-04-26.
//

#ifndef LIGHT_SQUARE_FCSTATE_H
#define LIGHT_SQUARE_FCSTATE_H

#import "ofMain.h"
#import "FcDevice.h"

class FcState {
public:
    bool isConnected;
    vector<FcDevice> connectedDevices;
};


#endif //LIGHT_SQUARE_FCSTATE_H
