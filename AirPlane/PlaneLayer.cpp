//
//  PlaneLayer.cpp
//  AirPlane
//
//  Created by Syuuhi on 14-3-10.
//
//

#include "PlaneLayer.h"
PlaneLayer* PlaneLayer::sharedPlane=NULL;

PlaneLayer::PlaneLayer(){
    isAlive = true;
    score = 0;
}

PlaneLayer::~PlaneLayer(){
    
}

PlaneLayer* PlaneLayer::create(){
    PlaneLayer* pRet = new PlaneLayer();
    if (pRet && pRet->init()) {
        pRet->autorelease();
        sharedPlane = pRet;
        return  pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool PlaneLayer::init(){
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot.plist");
        CCSprite* player = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
        CC_BREAK_IF(!player);
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        player->setPosition(ccp(winSize.width/2, player->getContentSize().height));
        this->addChild(player,0,0);
        
        CCBlink* blink = CCBlink::create(1, 3);
        CCAnimation* animation = CCAnimation::create();
        animation->setDelayPerUnit(0.1f);
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero2.png"));
        CCAnimate* animate = CCAnimate::create(animation);
        player->runAction(blink);
        player->runAction(CCRepeatForever::create(animate));
        bRet = true;
    } while (0);
    return bRet;
}

void PlaneLayer::moveTo(CCPoint toPoint){
    if (isAlive && !CCDirector::sharedDirector()->isPaused()) {
        CCPoint actualPoint = toPoint;
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCSize planeSize = this->getChildByTag(0)->getContentSize();
        if (toPoint.x < planeSize.width/2) {
            actualPoint.x = planeSize.width/2;
        }
        if (toPoint.x > winSize.width-planeSize.width/2) {
            actualPoint.x = winSize.width - planeSize.width/2;
        }
        if (toPoint.y > winSize.height-planeSize.height/2) {
            actualPoint.y = winSize.height-planeSize.height/2;
        }
        if (toPoint.y < planeSize.width/2) {
            actualPoint.y = planeSize.height/2;
        }
        this->getChildByTag(0)->setPosition(actualPoint);
    }
}

void PlaneLayer::blowUp(int finalscore){
    if (isAlive) {
        score = finalscore;
        CCAnimation* animation = CCAnimation::create();
        animation->setDelayPerUnit(0.2f);
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n1.png"));
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n2.png"));
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n3.png"));
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n4.png"));
        CCAnimate* animate = CCAnimate::create(animation);
        CCCallFuncN* blowUpDone = CCCallFuncN::create(this, callfuncN_selector(PlaneLayer::removePlane));
        CCSequence* sequence = CCSequence::create(animate,blowUpDone);
        this->getChildByTag(0)->stopAllActions();
        this->getChildByTag(0)->runAction(sequence);
        isAlive = false;
    }
}

void PlaneLayer::removePlane(){
    this->removeChildByTag(0);
    GameOverScene* gameOver = GameOverScene::create(score);
    CCTransitionMoveInB* transition = CCTransitionMoveInB::create(0.5f, gameOver);
    CCDirector::sharedDirector()->replaceScene(transition);
}