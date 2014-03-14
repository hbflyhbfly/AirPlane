//
//  LabelLayer.cpp
//  AirPlane
//
//  Created by Syuuhi on 14-3-12.
//
//

#include "LabelLayer.h"

LabelLayer::LabelLayer(){
    m_score = NULL;
    m_pauseItem = NULL;
}

LabelLayer::~LabelLayer(){
    
}

bool LabelLayer::init(){
    bool bRet = false;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    do {
        CC_BREAK_IF(!CCLayer::init());
        CCSprite* pauseNormal = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_nor.png"));
        CCSprite* pausePressed = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_pressed.png"));
        m_pauseItem = CCMenuItemImage::create();
        m_pauseItem->initWithNormalSprite(pauseNormal, pausePressed, NULL, this, menu_selector(LabelLayer::pauseMenuCallBack));
        m_pauseItem->setPosition(ccp(pauseNormal->getContentSize().width/2+10, winSize.height-pauseNormal->getContentSize().height/2-30));
        CCMenu* menu = CCMenu::create(m_pauseItem,NULL);
        menu->setPosition(CCPointZero);
        this->addChild(menu);
        
        m_score = CCLabelBMFont::create("0", "font.fnt");
        m_score->setColor(ccc3(143,146,147));
		m_score->setAnchorPoint(ccp(0,0.5));
		m_score->setPosition(ccp(m_pauseItem->getPositionX()+m_pauseItem->getContentSize().width/2+5,m_pauseItem->getPositionY()));
		this->addChild(m_score);
        
        bRet = true;
    } while (0);
    return bRet;
}

void LabelLayer::updateScore(int score){
    if (score > 0 && score <= maxScore) {
        CCString* scoreStr = CCString::createWithFormat("%d",score);
        m_score->setString(scoreStr->getCString());
        
    }
}



void LabelLayer::pauseMenuCallBack(cocos2d::CCNode *pSender){
    if (!CCDirector::sharedDirector()->isPaused()) {
        m_pauseItem->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_nor.png"));
        m_pauseItem->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_pressed.png"));
        pauseLayer = PauseLayer::create();
        this->addChild(pauseLayer);
        CCDirector::sharedDirector()->pause();
    } else {
        m_pauseItem->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_nor.png"));
        m_pauseItem->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_pressed.png"));
        this->removeChild(pauseLayer);
        CCDirector::sharedDirector()->resume();
    }
}
