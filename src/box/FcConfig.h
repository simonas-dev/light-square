//
// Created by Simonas Sankauskas on 2019-04-26.
//

#ifndef LIGHT_SQUARE_FCCONFIG_H
#define LIGHT_SQUARE_FCCONFIG_H

#import "ofMain.h"
#import "FcAddress.h"
#import "FcColor.h"
#import "FcMapping.h"

class FcConfig {
public:
    FcAddress listen;
    FcAddress relay;
    bool verbose;
    FcColor color;
    vector<FcMapping> devices;
};


#endif //LIGHT_SQUARE_FCCONFIG_H
