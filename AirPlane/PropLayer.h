//
//  PropLayer.h
//  AirPlane
//
//  Created by Syuuhi on 14-3-12.
//
//

#ifndef __AirPlane__PropLayer__
#define __AirPlane__PropLayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class PropLayer:public CCLayer {
    
public:
    CREATE_FUNC(PropLayer);
    virtual bool init();
    void addProp(float dt);
    void propMoveFinish(CCNode* pSender);
    void removeProp(CCSprite* prop);

    PropLayer();
    ~PropLayer();
    CCArray* m_AllProps;

};
#endif /* defined(__AirPlane__PropLayer__) */
