//
//  GameScene.cpp
//  AirPlane
//
//  Created by Syuuhi on 14-3-10.
//
//

#include "GameScene.h"
USING_NS_CC;
GameScene::GameScene(void){
    _gameLayer = NULL;
}
GameScene::~GameScene(void){
    
}
bool GameScene::init(){
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCScene::init());
        _gameLayer = GameLayer::create();
        CC_BREAK_IF(!_gameLayer);
        this->addChild(_gameLayer);
        bRet = true;
    } while (0);
    return bRet;
}