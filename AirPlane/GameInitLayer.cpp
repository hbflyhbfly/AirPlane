//
//  GameInitLayer.cpp
//  AirPlane
//
//  Created by Syuuhi on 14-3-13.
//
//

#include "GameInitLayer.h"

GameInitLayer::GameInitLayer(){
    
}
GameInitLayer::~GameInitLayer(){
    
}
bool GameInitLayer::init(){
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayer::create());
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();

        //全局缓冲
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot.plist");
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot_background.plist");
        
        //背景
        CCSprite* backGround = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
        float scalX=winSize.width/backGround->getContentSize().width;
        float scalY=winSize.height/backGround->getContentSize().height;
        backGround->setScaleX(scalX);
        backGround->setScaleY(scalY);
        backGround->setAnchorPoint(CCPointZero);
        backGround->setPosition(CCPointZero);
        this->addChild(backGround);
        
        CCSprite* title = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("shoot_copyright.png"));
        title->cocos2d::CCNode::setPosition(ccp(winSize.width/2, winSize.height*3/4));
        this->addChild(title);
        
        //loading动画
        CCSprite* gameLoading = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
        gameLoading->setAnchorPoint(CCPointZero);
        gameLoading->setPosition(ccp((winSize.width-gameLoading->boundingBox().size.width)/2, winSize.height/2+40));
        CCAnimation* animation = CCAnimation::create();
        animation->setDelayPerUnit(0.2f);
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading2.png"));
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading3.png"));
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading4.png"));
        CCAnimate* animate = CCAnimate::create(animation);
        CCRepeat* repeat = CCRepeat::create(animate, 2);
        CCCallFuncN* loadingDone = CCCallFuncN::create(this, callfuncN_selector(GameInitLayer::loadingDone));
        CCSequence* sequence = CCSequence::create(repeat,loadingDone);
        gameLoading->runAction(sequence);
        this->addChild(gameLoading);
        
        
        
        bRet = true;
    } while (0);
    return bRet;
}

void GameInitLayer::loadingDone(CCNode *pSender){
    GameScene* gameScene = GameScene::create();
    CCTransitionMoveInB* transition = CCTransitionMoveInB::create(0.5f, gameScene);
    CCDirector::sharedDirector()->replaceScene(transition);
}

void GameInitLayer::getHighestHistoryScore(){
    if (isHaveSaveFile()) {
        GameOverLayer::historyHighestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("highestScore");
    }
}

bool GameInitLayer::isHaveSaveFile(){
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("isHaveSaveFileXML")) {
        CCUserDefault::sharedUserDefault()->setBoolForKey("isHaveSaveFileXML", true);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("highestScore", 0);
        CCUserDefault::sharedUserDefault()->flush();
        return false;
    } else {
        return true;
    }
}