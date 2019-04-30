//
// Created by Simonas Sankauskas on 2019-04-26.
//

#ifndef LIGHT_SQUARE_FCMAPPING_H
#define LIGHT_SQUARE_FCMAPPING_H


class FcMapping {
public:
    string type;
    bool dither;
    bool interpolate;
    string serial;
    vector<tuple<int, int, int, int>> map;
};


#endif //LIGHT_SQUARE_FCMAPPING_H
