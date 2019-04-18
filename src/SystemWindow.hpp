//
//  SystemWindow.hpp
//  siLedBox
//
//  Created by Simonas Sankauskas on 4/18/19.
//

#ifndef SystemWindow_hpp
#define SystemWindow_hpp

#include "ofMain.h"
#include "AppContext.hpp"

#endif /* SystemWindow_hpp */

class SystemWindow : public ofBaseApp {
    AppContext * context;
    
public:
    SystemWindow(AppContext * appContext) {
        context = appContext;
    };
    void setup();
    void update();
    void draw();
    void exit();
};
