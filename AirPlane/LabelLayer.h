//
//  LabelLayer.h
//  AirPlane
//
//  Created by Syuuhi on 14-3-12.
//
//

#ifndef __AirPlane__LabelLayer__
#define __AirPlane__LabelLayer__

#include <iostream>
#include "cocos2d.h"
#include "PauseLayer.h"

USING_NS_CC;
const int maxScore = 1000000;
class LabelLayer:public CCLayer {
    
public:
    LabelLayer();
    ~LabelLayer();
    virtual bool init();
    CREATE_FUNC(LabelLayer);
    void updateScore(int score);
    void pauseMenuCallBack(CCNode* pSender);
    
private:
    CCLabelBMFont* m_score;
    CCMenuItemImage* m_pauseItem;
    PauseLayer* pauseLayer;
    
};

#endif /* defined(__AirPlane__LabelLayer__) */
