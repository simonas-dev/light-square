//
//  AppContext.hpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//
#pragma once

#ifndef AppContext_hpp
#define AppContext_hpp

#include <audio/AudioClient.hpp>
#include <led/MatrixLedClient.hpp>

#endif /* AppContext_hpp */

class AppContext {
    
public:
    AudioClient audio;
    MatrixLedClient matrixLed;
};
