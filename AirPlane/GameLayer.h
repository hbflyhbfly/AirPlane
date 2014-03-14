//
//  GameLayer.h
//  AirPlane
//
//  Created by Syuuhi on 14-3-10.
//
//

#ifndef __AirPlane__GameLayer__
#define __AirPlane__GameLayer__

#include <iostream>
#include "cocos2d.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"
#include "PropLayer.h"
#include "LabelLayer.h"
#include "GameOverScene.h"

#define TAG_BOMB 1
USING_NS_CC;
class GameLayer:public CCLayer {
private:
    CCSprite* backGround1;
    CCSprite* backGround2;
    void backGroundMove(float dt);
    CCSize getSize();
    PlaneLayer* playerLayer;
    BulletLayer* bulletLayer;
    EnemyLayer* enemyLayer;
    PropLayer* propLayer;
    LabelLayer* labelLayer;
    int bigBombCount;
    int score;
    CCLabelBMFont* m_bombCount;
    CCMenuItemImage* m_bomb;
public:
    CREATE_FUNC(GameLayer);
    virtual bool init();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    void registerWithTouchDispatcher();
    void bombMenuCallBack(CCNode* pSender);
    void updateBombCount(int bombCount);
    static Level getGameLevel();
    void update(float dt);
    GameLayer(void);
    ~GameLayer(void);

};
#endif /* defined(__AirPlane__GameLayer__) */
