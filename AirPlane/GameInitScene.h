//
//  GameInitScene.h
//  AirPlane
//
//  Created by Syuuhi on 14-3-13.
//
//

#ifndef __AirPlane__GameInitScene__
#define __AirPlane__GameInitScene__

#include <iostream>
#include "cocos2d.h"
#include "GameInitLayer.h"
USING_NS_CC;
class GameInitScene:public CCScene {
    
public:
    GameInitScene();
    ~GameInitScene();
    CREATE_FUNC(GameInitScene);
    virtual bool init();
    GameInitLayer* _gameInitLayer;
};
#endif /* defined(__AirPlane__GameInitScene__) */
