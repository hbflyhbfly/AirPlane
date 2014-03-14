//
//  GameOverScene.cpp
//  AirPlane
//
//  Created by Syuuhi on 14-3-13.
//
//

#include "GameOverScene.h"
GameOverScene::GameOverScene(){
    score = 0;
    _gameOverLayer = NULL;

}
GameOverScene::~GameOverScene(){
    
}

GameOverScene* GameOverScene::create(int passScore)
{
	GameOverScene *pRet = new GameOverScene();
	pRet->score=passScore;
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool GameOverScene::init(){
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCScene::create());
        _gameOverLayer = GameOverLayer::create(score);
        CC_BREAK_IF(!_gameOverLayer);
        this->addChild(_gameOverLayer);
        bRet = true;
    } while (0);
    return bRet;
}