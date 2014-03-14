//
//  EnemyLayer.cpp
//  AirPlane
//
//  Created by Syuuhi on 14-3-11.
//
//

#include "EnemyLayer.h"
#include "GameLayer.h"

EnemyLayer::EnemyLayer(void){
    enemy1SpriteFrame = NULL;
    enemy2SpriteFrame = NULL;
    enemy3SpriteFrame_1 = NULL;
    enemy3SpriteFrame_2 = NULL;

    m_pAllEnemy1 = CCArray::create();
    m_pAllEnemy1->retain();
}

EnemyLayer::~EnemyLayer(void){
    m_pAllEnemy1->removeAllObjects();
}

bool EnemyLayer::init(){
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        enemy1SpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1.png");
        CCAnimation* animation1 = CCAnimation::create();
        animation1->setDelayPerUnit(0.1f);
        animation1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down1.png"));
        animation1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down2.png"));
        animation1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down3.png"));
        animation1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down4.png"));
        CCAnimationCache::sharedAnimationCache()->addAnimation(animation1, "Enemy1Blowup");
        
        enemy2SpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2.png");
        CCAnimation* animation2 = CCAnimation::create();
        animation2->setDelayPerUnit(0.1f);
        animation2->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down1.png"));
        animation2->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down2.png"));
        animation2->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down3.png"));
        animation2->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down4.png"));
        CCAnimationCache::sharedAnimationCache()->addAnimation(animation2, "Enemy2Blowup");
        
        enemy3SpriteFrame_1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n1.png");
        enemy3SpriteFrame_2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n2.png");
        CCAnimation* animation3 = CCAnimation::create();
        animation3->setDelayPerUnit(0.1f);
        animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down1.png"));
        animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down2.png"));
        animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down3.png"));
        animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down4.png"));
        animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down5.png"));
        animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down6.png"));
        CCAnimationCache::sharedAnimationCache()->addAnimation(animation3, "Enemy3Blowup");
        
        this->schedule(schedule_selector(EnemyLayer::addEnemy1), 1.0f);

        bRet = true;
    } while (0);
    return bRet;
}

void EnemyLayer::addEnemy1(float dt){
    Enemy* enemy1 = Enemy::create();
    CCAnimation *animation;
    CCAnimate* animate;
    int enemyType = rand()%3;
    switch (enemyType) {
        case 0:
            enemy1->bindSprite(CCSprite::createWithSpriteFrame(enemy1SpriteFrame),Level1, ENEMY_MAX_LIFE1);
            break;
        case 1:
            enemy1->bindSprite(CCSprite::createWithSpriteFrame(enemy2SpriteFrame),Level2, ENEMY_MAX_LIFE2);
            break;
        case 2:
            enemy1->bindSprite(CCSprite::createWithSpriteFrame(enemy3SpriteFrame_1),Level3, ENEMY_MAX_LIFE3);
            animation = CCAnimation::create();
            animation->setDelayPerUnit(0.2f);
            animation->addSpriteFrame(enemy3SpriteFrame_1);
            animation->addSpriteFrame(enemy3SpriteFrame_2);
            animate = CCAnimate::create(animation);
            enemy1->getSprite()->runAction(CCRepeatForever::create(animate));
            break;
        default:
            enemy1->bindSprite(CCSprite::createWithSpriteFrame(enemy1SpriteFrame),Level1, ENEMY_MAX_LIFE1);
            break;
    }
    this->addChild(enemy1);
    m_pAllEnemy1->addObject(enemy1);
    CCSize enemy1Size = enemy1->getContentSize();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int minX = enemy1Size.width/2;
    int maxX =winSize.width -minX;
    int rangeX = maxX - minX;
    int aclX = (rand()%rangeX) + minX;
    enemy1->setPosition(ccp(aclX, winSize.height+enemy1Size.height));
    float minDuration,maxDuration;
    switch (GameLayer::getGameLevel()) {
        case EASY:
            minDuration = 3;
            maxDuration = 8;
            break;
        case NORMAL:
            minDuration = 1;
            maxDuration = 3;
            break;
        case HARD:
            minDuration = 0.5;
            maxDuration = 1;
            break;
            
        default:
            break;
    }
    int rangeDuration = maxDuration - minDuration;
    int aclDuration = (rand()%rangeDuration) + minDuration;
    CCFiniteTimeAction* moveTo = CCMoveTo::create(aclDuration, ccp(aclX, -2*enemy1Size.height));
    CCFiniteTimeAction* moveDone = CCCallFuncN::create(this, callfuncN_selector(EnemyLayer::enemyMoveFinish));
    CCSequence* sequence = CCSequence::create(moveTo,moveDone);
    enemy1->runAction(sequence);
    
}

void EnemyLayer::enemyBlowUp(Enemy *enemy,EnemyType enemyType){


    CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName("Enemy1Blowup");
    switch (enemyType) {
        case Level1:
            animation = CCAnimationCache::sharedAnimationCache()->animationByName("Enemy1Blowup");            break;
        case Level2:
            animation = CCAnimationCache::sharedAnimationCache()->animationByName("Enemy2Blowup");            break;
        case Level3:
            animation = CCAnimationCache::sharedAnimationCache()->animationByName("Enemy3Blowup");            break;
        default:
            
            break;
    }
    CCFiniteTimeAction* animateBlow = CCAnimate::create(animation);
    CCFiniteTimeAction* removeEnemy = CCCallFuncND::create(this, callfuncND_selector(EnemyLayer::removeEnemy),(void*)enemy);
    CCSequence* sequence = CCSequence::create(animateBlow,removeEnemy);
    enemy->getSprite()->runAction(sequence);
}

void EnemyLayer::removeEnemy(cocos2d::CCNode *pSender, void *pnode){
    Enemy* enemy = (Enemy*)pnode;
    if (enemy != NULL) {
        m_pAllEnemy1->removeObject(enemy);
        this->removeChild(enemy);
    }

}

void EnemyLayer::removeAllEnemy(){
    CCObject* obj;
    CCARRAY_FOREACH(m_pAllEnemy1, obj){
        Enemy* enemy = (Enemy*)obj;
        if (enemy->getLife()>0) {
            enemyBlowUp(enemy, enemy->getType());
        }
    }
}

void EnemyLayer::enemyMoveFinish(CCNode *pSender){
    Enemy* enemy = (Enemy*)pSender;
    this->removeChild(enemy);
    m_pAllEnemy1->removeObject(enemy);
}