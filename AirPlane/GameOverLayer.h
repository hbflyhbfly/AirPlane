//
//  GameOverLayer.h
//  AirPlane
//
//  Created by Syuuhi on 14-3-13.
//
//

#ifndef __AirPlane__GameOverLayer__
#define __AirPlane__GameOverLayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class GameOverLayer:public CCLayer {
    
public:
    GameOverLayer();
    ~GameOverLayer();
    virtual bool init();
    static GameOverLayer* create(int finalScore);
    void changeHistoryScore(CCNode* pSender);
    void backMenuClick();
    int score;
    static int historyHighestScore;
    CCLabelBMFont* scoreLabel;
    CCLabelBMFont* historyHighScoreLabel;
    CCMenuItemImage* backMenu;
};
#endif /* defined(__AirPlane__GameOverLayer__) */
