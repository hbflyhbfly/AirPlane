//
//  GameInitLayer.h
//  AirPlane
//
//  Created by Syuuhi on 14-3-13.
//
//

#ifndef __AirPlane__GameInitLayer__
#define __AirPlane__GameInitLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameScene.h"
#include "GameOverLayer.h"
USING_NS_CC;
class GameInitLayer:public CCLayer {

public:
    GameInitLayer();
    ~GameInitLayer();
    virtual bool init();
    CREATE_FUNC(GameInitLayer);
    void loadingDone(CCNode* pSender);
    bool isHaveSaveFile();
    void getHighestHistoryScore();
};
#endif /* defined(__AirPlane__GameInitLayer__) */
