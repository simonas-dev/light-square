//
//  AppContext.hpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//

#ifndef AppContext_hpp
#define AppContext_hpp

#include <stdio.h>
#include <AudioClient.hpp>
#include <LedClient.hpp>

#endif /* AppContext_hpp */

class AppContext {
    
public:
    AudioClient audio = AudioClient();
    LedClient led = LedClient();
};
