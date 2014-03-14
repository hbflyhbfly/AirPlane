//
//  GameInitScene.cpp
//  AirPlane
//
//  Created by Syuuhi on 14-3-13.
//
//

#include "GameInitScene.h"
GameInitScene::GameInitScene(){
    _gameInitLayer = NULL;
}
GameInitScene::~GameInitScene(){
    
}
bool GameInitScene::init(){
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCScene::create());
        _gameInitLayer = GameInitLayer::create();
        CC_BREAK_IF(!_gameInitLayer);
        this->addChild(_gameInitLayer);
        bRet = true;
    } while (0);
    return bRet;
}