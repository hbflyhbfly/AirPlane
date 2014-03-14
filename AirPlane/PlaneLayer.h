//
//  PlaneLayer.h
//  AirPlane
//
//  Created by Syuuhi on 14-3-10.
//
//

#ifndef __AirPlane__PlaneLayer__
#define __AirPlane__PlaneLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameOverScene.h"
USING_NS_CC;
class PlaneLayer:public CCLayer {
    
public:
    PlaneLayer(void);
    ~PlaneLayer(void);
    static PlaneLayer* create();
    virtual bool init();
    static PlaneLayer* sharedPlane;
    bool isAlive;
    void moveTo(CCPoint toPoint);
    void blowUp(int finalscore);
    void removePlane();
    int score;

};
#endif /* defined(__AirPlane__PlaneLayer__) */
