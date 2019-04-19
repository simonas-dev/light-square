//
//  AppContext.hpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//
#pragma once

#ifndef AppContext_hpp
#define AppContext_hpp

#include <AudioClient.hpp>
#include <LedClient.hpp>

#endif /* AppContext_hpp */

class AppContext {
    
public:
    AudioClient audio;
    LedClient led;
};
