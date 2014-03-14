//
//  Enemy.h
//  AirPlane
//
//  Created by Syuuhi on 14-3-11.
//
//

#ifndef __AirPlane__Enemy__
#define __AirPlane__Enemy__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
enum EnemyType {
    Level1,
    Level2,
    Level3
};
class Enemy:public CCNode{
public:
    Enemy();
    ~Enemy();
    static Enemy* create();
    void bindSprite(CCSprite* sprite,EnemyType enemyType,float life);
    CCRect getBoundingBox();
    CCSprite* getSprite();
    float getLife();
    void loseLife();
    EnemyType getType();
private:
    EnemyType m_enemyType;
    CCSprite* m_sprite;
    int m_life;
};


#endif /* defined(__AirPlane__Enemy__) */
