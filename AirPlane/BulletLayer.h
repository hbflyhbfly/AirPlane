//
//  BulletLayer.h
//  AirPlane
//
//  Created by Syuuhi on 14-3-10.
//
//

#ifndef __AirPlane__BulletLayer__
#define __AirPlane__BulletLayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class BulletLayer:public CCLayer{
public:
    CCSpriteBatchNode* bulletBatchNode;
    CCArray* m_pAllBullet;
    bool init();
    void addBullet(float dt);
    void bulletMoveFinished(CCNode* pSender);
    void startShoot(float delay = 1.5f);
    void stopShoot();
    void removeBullet(CCSprite* bullet);
    CREATE_FUNC(BulletLayer);
    BulletLayer();
    ~BulletLayer();
    
};
#endif /* defined(__AirPlane__BulletLayer__) */
