//
//  PauseLayer.h
//  AirPlane
//
//  Created by Syuuhi on 14-3-12.
//
//

#ifndef __AirPlane__PauseLayer__
#define __AirPlane__PauseLayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class PauseLayer:public CCLayer {
    
public:
    //PauseLayer();
    //~PauseLayer();
    virtual bool init();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void registerWithTouchDispatcher();
    CREATE_FUNC(PauseLayer);
};
#endif /* defined(__AirPlane__PauseLayer__) */
