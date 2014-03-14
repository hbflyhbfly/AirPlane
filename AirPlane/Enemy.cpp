//
//  Enemy.cpp
//  AirPlane
//
//  Created by Syuuhi on 14-3-11.
//
//

#include "Enemy.h"

Enemy::Enemy(){
    m_sprite = NULL;
    m_life = 0;
}

Enemy::~Enemy(){
    
}

Enemy* Enemy::create(){
    Enemy* pRet = new Enemy();
    pRet->autorelease();
    return pRet;
}

void Enemy::bindSprite(cocos2d::CCSprite *sprite, EnemyType enemyType,float life){
    m_sprite = sprite;
    this->addChild(sprite);
    m_life = life;
    m_enemyType = enemyType;
}

CCSprite* Enemy::getSprite(){
    return m_sprite;
}

float Enemy::getLife(){
    return m_life;
}

void Enemy::loseLife(){
    m_life--;
}

EnemyType Enemy::getType(){
    return m_enemyType;
}

CCRect Enemy::getBoundingBox(){
    CCRect rect = m_sprite->boundingBox();
    CCPoint pos = this->convertToWorldSpace(rect.origin);
    CCRect enemyRect(pos.x,pos.y,rect.size.width,rect.size.height);
    return enemyRect;
}