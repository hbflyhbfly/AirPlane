//
//  BulletLayer.cpp
//  AirPlane
//
//  Created by Syuuhi on 14-3-10.
//
//

#include "BulletLayer.h"
#include "PlaneLayer.h"

BulletLayer::BulletLayer(void){
    bulletBatchNode = NULL;
    m_pAllBullet = CCArray::create();
    m_pAllBullet->retain();
}

BulletLayer::~BulletLayer(){
    m_pAllBullet->removeAllObjects();
}

bool BulletLayer::init(){
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->textureForKey("shoot.png");
        bulletBatchNode = CCSpriteBatchNode::createWithTexture(texture);
        this->addChild(bulletBatchNode);
        bRet = true;
    } while (0);
    return bRet;
}

void BulletLayer::addBullet(float dt){
    CCSprite* bullet = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bullet1.png"));
    CCPoint planePosition = PlaneLayer::sharedPlane->getChildByTag(0)->getPosition();
    CCSize conSize = PlaneLayer::sharedPlane->getChildByTag(0)->getContentSize();
    CCPoint bulletPosition = ccp(planePosition.x, planePosition.y+conSize.height/2);
    bullet->setPosition(bulletPosition);
    float length = CCDirector::sharedDirector()->getWinSize().height-bulletPosition.y;
    float vel = 1200;
    float duration = length/vel;
    CCFiniteTimeAction* actionMove = CCMoveTo::create(duration, ccp(bulletPosition.x, CCDirector::sharedDirector()->getWinSize().height));
    CCFiniteTimeAction* actionDone=CCCallFuncN::create(this,callfuncN_selector(BulletLayer::bulletMoveFinished));
    CCSequence* sequence = CCSequence::create(actionMove,actionDone);
    bullet->runAction(sequence);
    bulletBatchNode->addChild(bullet);
    m_pAllBullet->addObject(bullet);
}

void BulletLayer::bulletMoveFinished(CCNode *pSender){
    CCSprite* bullet = (CCSprite*)pSender;
    m_pAllBullet->removeObject(bullet);
    bulletBatchNode->removeChild(bullet, true);
}

void BulletLayer::startShoot(float delay){
    this->schedule(schedule_selector(BulletLayer::addBullet), 0.2f, kCCRepeatForever, delay);
}

void BulletLayer::stopShoot(){
    this->unschedule(schedule_selector(BulletLayer::addBullet));
}

void BulletLayer::removeBullet(CCSprite *bullet){
    if (bullet != NULL) {
        m_pAllBullet->removeObject(bullet);
        bulletBatchNode->removeChild(bullet,true);
    }
}