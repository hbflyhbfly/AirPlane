//
//  PauseLayer.cpp
//  AirPlane
//
//  Created by Syuuhi on 14-3-12.
//
//

#include "PauseLayer.h"

bool PauseLayer::init(){
    bool pRet = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        pRet = true;
    } while (0);
    return pRet;
}

void PauseLayer::registerWithTouchDispatcher(){
    CCDirector* director = CCDirector::sharedDirector();
    director->getTouchDispatcher()->addTargetedDelegate(this, -127, true);
}
bool PauseLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    return true;
}