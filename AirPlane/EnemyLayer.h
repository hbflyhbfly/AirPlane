//
//  EnemyLayer.h
//  AirPlane
//
//  Created by Syuuhi on 14-3-11.
//
//

#ifndef __AirPlane__EnemyLayer__
#define __AirPlane__EnemyLayer__

#include <iostream>
#include "cocos2d.h"
#include "Enemy.h"
USING_NS_CC;
const int ENEMY_MAX_LIFE1 = 1;
const int ENEMY_MAX_LIFE2 = 2;
const int ENEMY_MAX_LIFE3 = 5;

enum Level {
    EASY,
    NORMAL,
    HARD
    };

class EnemyLayer:public CCLayer {
    
public:
    EnemyLayer(void);
    ~EnemyLayer(void);
    CREATE_FUNC(EnemyLayer);
    virtual bool init();
    void addEnemy1(float dt = 0.0f);
    void enemyMoveFinish(CCNode* pSender);
    void enemyBlowUp(Enemy* enemy,EnemyType enemyType);
    void removeEnemy(CCNode* pSender,void* pNode);
    void removeAllEnemy();
    CCArray* m_pAllEnemy1;
private:
    CCSpriteFrame* enemy1SpriteFrame;
    CCSpriteFrame* enemy2SpriteFrame;
    CCSpriteFrame* enemy3SpriteFrame_1;
    CCSpriteFrame* enemy3SpriteFrame_2;


};
#endif /* defined(__AirPlane__EnemyLayer__) */
