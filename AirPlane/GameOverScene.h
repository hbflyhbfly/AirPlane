//
//  GameOverScene.h
//  AirPlane
//
//  Created by Syuuhi on 14-3-13.
//
//

#ifndef __AirPlane__GameOverScene__
#define __AirPlane__GameOverScene__

#include <iostream>
#include "cocos2d.h"
#include "GameOverLayer.h"
USING_NS_CC;
class GameOverScene:public CCScene {
    
public:
    GameOverScene();
    ~GameOverScene();
    virtual bool init();
    static GameOverScene* create(int finalScore);
    CREATE_FUNC(GameOverScene);
    GameOverLayer* _gameOverLayer;
    int score;
};
#endif /* defined(__AirPlane__GameOverScene__) */
