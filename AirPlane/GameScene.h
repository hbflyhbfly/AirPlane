//
//  GameScene.h
//  AirPlane
//
//  Created by Syuuhi on 14-3-10.
//
//

#ifndef __AirPlane__GameScene__
#define __AirPlane__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "GameLayer.h"
USING_NS_CC;
class GameScene:public CCScene {

public:
     GameScene(void);
    ~GameScene(void);

    CREATE_FUNC(GameScene);
    virtual bool init();
    GameLayer *_gameLayer;
};

#endif /* defined(__AirPlane__GameScene__) */
