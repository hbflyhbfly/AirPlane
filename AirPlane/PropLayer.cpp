//
//  PropLayer.cpp
//  AirPlane
//
//  Created by Syuuhi on 14-3-12.
//
//

#include "PropLayer.h"

PropLayer::PropLayer(){
    m_AllProps = CCArray::create();
    m_AllProps->retain();
}
PropLayer::~PropLayer(){
    m_AllProps->removeAllObjects();
}
bool PropLayer::init(){
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayer::init());        
        this->schedule(schedule_selector(PropLayer::addProp), 20.0f, kCCRepeatForever, 5.0f);
        bRet = true;
    } while (0);
    return bRet;
}
void PropLayer::addProp(float dt){
    CCSprite* prop = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ufo2.png"));
    CCSize conSize = prop->getContentSize();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int minX = conSize.width/2;
    int maxX = winSize.width-minX;
    int rangeX = maxX - minX;
    int aclX = (rand()%rangeX)+minX;
    prop->setPosition(ccp(aclX, winSize.height));
    
    ccBezierConfig bezierCon;
    bezierCon.controlPoint_1 = CCPointMake(aclX+100, winSize.height*2/3);
    bezierCon.controlPoint_2 = CCPointMake(aclX-100, winSize.height/3);
    bezierCon.endPosition = CCPointMake((rand()%rangeX)+minX, 0);
    CCActionInterval* action = CCBezierTo::create(5.0f, bezierCon);
    
    CCCallFuncN* moveDone = CCCallFuncN::create(this, callfuncN_selector(PropLayer::propMoveFinish));
    CCFiniteTimeAction* sequence = CCSequence::create(action,moveDone,NULL);
    prop->runAction(sequence);
    this->addChild(prop);
    m_AllProps->addObject(prop);
}

void PropLayer::propMoveFinish(cocos2d::CCNode *pSender){
    CCSprite* prop = (CCSprite*)pSender;
    this->removeChild(prop);
    m_AllProps->removeObject(prop);
}

void PropLayer::removeProp(cocos2d::CCSprite *prop){
    this->removeChild(prop);
    m_AllProps->removeObject(prop);
}