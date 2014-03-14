//
//  GameOverLayer.cpp
//  AirPlane
//
//  Created by Syuuhi on 14-3-13.
//
//

#include "GameOverLayer.h"
#include "GameScene.h"
int GameOverLayer::historyHighestScore = 0;
GameOverLayer::GameOverLayer(){
    score = 0;
    scoreLabel = NULL;
}
GameOverLayer::~GameOverLayer(){
    
}

GameOverLayer* GameOverLayer::create(int finalScore){
    GameOverLayer* pRet = new GameOverLayer();
    pRet->score = finalScore;
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    }else{
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool GameOverLayer::init(){
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayer::create());
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCSprite* gameOver = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gameover.png"));
        gameOver->setAnchorPoint(CCPointZero);
        gameOver->setPosition(CCPointZero);
        float scalX=winSize.width/gameOver->getContentSize().width;
        float scalY=winSize.height/gameOver->getContentSize().height;
        gameOver->setScaleX(scalX);
        gameOver->setScaleY(scalY);
        this->addChild(gameOver);
        
        CCDelayTime* delay = CCDelayTime::create(1.5f);
        CCScaleTo* scale1 = CCScaleTo::create(0.5f, 2.0f);
        CCScaleTo* scale2 = CCScaleTo::create(0.2f, 1.0f);
        CCSequence* sequenceScale = CCSequence::create(delay,scale1,scale2,NULL);
        CCString* scoreStr = CCString::createWithFormat("%d",score);
        scoreLabel = CCLabelBMFont::create(scoreStr->getCString(), "font.fnt");
        scoreLabel->setColor(ccc3(143,146,147));
		scoreLabel->setAnchorPoint(ccp(0.5,0.5));
        scoreLabel->setPosition(ccp((winSize.width-scoreLabel->boundingBox().size.width)/2, winSize.height/2+20));
        scoreLabel->runAction(sequenceScale);
        this->addChild(scoreLabel);
        
        CCString* historyScoreStr = CCString::createWithFormat("%d",historyHighestScore);
        historyHighScoreLabel = CCLabelBMFont::create(historyScoreStr->getCString(), "font.fnt");
        historyHighScoreLabel->setColor(ccc3(143,146,147));
		historyHighScoreLabel->setAnchorPoint(ccp(0,0));
        historyHighScoreLabel->setPosition(ccp(200, winSize.height-77));
        this->addChild(historyHighScoreLabel);
        
        if (score > historyHighestScore) {
            CCUserDefault::sharedUserDefault()->setIntegerForKey("highestScore", score);
            CCUserDefault::sharedUserDefault()->flush();
            historyHighestScore = score;
            CCMoveBy* move1 = CCMoveBy::create(0.2f, ccp(0, 20));
            CCCallFuncN* changeHistoryHighestScore = CCCallFuncN::create(this, callfuncN_selector(GameOverLayer::changeHistoryScore));
            CCMoveBy* move2 = CCMoveBy::create(0.4f, ccp(0, -20));
            CCSequence* sequence = CCSequence::create(delay,move1,changeHistoryHighestScore,move2,NULL);
            historyHighScoreLabel->runAction(sequence);
            
        }
        
        CCSprite* backNol = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_finish.png"));
        backMenu = CCMenuItemImage::create();
        backMenu->initWithNormalSprite(backNol, backNol,NULL, this, menu_selector(GameOverLayer::backMenuClick));
        CCMenu* menu = CCMenu::create(backMenu,NULL);
        menu->setAnchorPoint(CCPointZero);
        menu->setPosition(ccp(80, 30));
        this->addChild(menu);
        bRet = true;
    } while (0);
    return bRet;
}

void GameOverLayer::backMenuClick(){
    GameScene* gameScene = GameScene::create();
    CCTransitionMoveInB* transition = CCTransitionMoveInB::create(0.5f, gameScene);
    CCDirector::sharedDirector()->replaceScene(transition);
}

void GameOverLayer::changeHistoryScore(CCNode* pSender){
    CCString* historyScoreStr = CCString::createWithFormat("%d",historyHighestScore);
    historyHighScoreLabel->setCString(historyScoreStr->getCString());
}