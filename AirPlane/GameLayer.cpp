//
//  GameLayer.cpp
//  AirPlane
//
//  Created by Syuuhi on 14-3-10.
//
//

#include "GameLayer.h"
#include "BulletLayer.h"

static Level gameLevel;

GameLayer::GameLayer(){
    backGround1 = NULL;
    backGround2 = NULL;
    playerLayer = NULL;
    bulletLayer = NULL;
    enemyLayer = NULL;
    bigBombCount = 0;
    score = 0;
}

GameLayer::~GameLayer(){
    
}


bool GameLayer::init(){
    bool ret = false;
    do {
        
        gameLevel = EASY;

        CC_BREAK_IF(!CCLayer::init());
        //背景设置
        backGround1 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
        CC_BREAK_IF(!backGround1);
        float scalX=getSize().width/backGround1->getContentSize().width;
        float scalY=getSize().height/backGround1->getContentSize().height;
        CCSize conSize = CCSizeMake((backGround1->getContentSize().width)*scalX, (backGround1->getContentSize().height)*scalY);
        backGround1->setScaleX(scalX);
        backGround1->setScaleY(scalY);
        backGround1->setAnchorPoint(CCPointZero);
        backGround1->setPosition(CCPointZero);
        this->addChild(backGround1);
        
        backGround2 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
        CC_BREAK_IF(!backGround2);
        backGround2->setScaleX(scalX);
        backGround2->setScaleY(scalY);
        backGround2->setAnchorPoint(CCPointZero);
        backGround2->setPosition(ccp(0, conSize.height-2));
        this->addChild(backGround2);
        
        //玩家设置
        this->playerLayer = PlaneLayer::create();
        this->addChild(playerLayer);
        
        //子弹
        this->bulletLayer = BulletLayer::create();
        this->addChild(bulletLayer);
        this->bulletLayer->startShoot();
        
        //敌机
        this->enemyLayer = EnemyLayer::create();
        this->addChild(enemyLayer);
        
        //道具
        this->propLayer = PropLayer::create();
        this->addChild(propLayer);
        
        //菜单，得分，炸弹数
        this->labelLayer = LabelLayer::create();
        this->addChild(labelLayer);
        
        //炸弹按钮
        CCSprite* bombNormal = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bomb.png"));
        
        m_bomb = CCMenuItemImage::create();
        m_bomb->initWithNormalSprite(bombNormal, bombNormal, NULL, this, menu_selector(GameLayer::bombMenuCallBack));
        m_bomb->setPosition(ccp(m_bomb->getContentSize().width/2+30, m_bomb->getContentSize().height/2+30));
        CCMenu* menu = CCMenu::create(m_bomb,NULL);
        menu->setPosition(CCPointZero);
        this->addChild(menu);
        
        m_bombCount = CCLabelBMFont::create("0", "font.fnt");
        m_bombCount->setColor(ccc3(143,146,147));
		m_bombCount->setAnchorPoint(ccp(0,0.5));
		m_bombCount->setPosition(ccp(m_bomb->getPositionX()+m_bomb->getContentSize().width/2+5,m_bomb->getPositionY()));
		this->addChild(m_bombCount);

        //定时器滚动背景
        this->schedule(schedule_selector(GameLayer::backGroundMove),0.01f);
        
        this->scheduleUpdate();
        
        this->setTouchEnabled(true);
        ret = true;
    } while (0);
    return ret;
}

void GameLayer::backGroundMove(float dt){
    float scalX=getSize().width/backGround1->getContentSize().width;
    float scalY=getSize().height/backGround1->getContentSize().height;
    CCSize conSize = CCSizeMake((backGround1->getContentSize().width)*scalX, (backGround1->getContentSize().height)*scalY);
    
    backGround1->setPositionY(backGround1->getPositionY()-2);
    backGround2->setPositionY(backGround1->getPositionY()+conSize.height-2);
    if (backGround2->getPositionY() <= 0) {
        backGround1->setPositionY(0);
        backGround2->setPositionY(backGround1->getPositionY()+conSize.height-2);
    }
    
}

void GameLayer::registerWithTouchDispatcher(){
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    return true;
}

void GameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    if (playerLayer->isAlive) {
        CCPoint touchPoint = pTouch->getLocationInView();
        touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
        CCRect planeRect = this->playerLayer->getChildByTag(0)->boundingBox();
        planeRect.origin.x -= 15;
        planeRect.origin.y -= 15;
        planeRect.size.width += 30;
        planeRect.size.height += 30;
        if (planeRect.containsPoint(touchPoint)) {
            CCPoint prePoint = pTouch->getPreviousLocation();
            CCPoint offset = ccpSub(touchPoint, prePoint);
            CCPoint toPoint = ccpAdd(this->playerLayer->getChildByTag(0)->getPosition(), offset);
            this->playerLayer->moveTo(toPoint);
        }
    }
}

void GameLayer::update(float dt){
    //子弹和敌机碰撞检测
    CCArray* deletebullets = CCArray::create();
    deletebullets->retain();
    CCObject *bt,*em,*pp;
    CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet, bt){
        CCArray* deleteEnemys = CCArray::create();
        deleteEnemys->retain();
        CCSprite* bullet = (CCSprite*)bt;
        CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1, em){
            Enemy* enemy = (Enemy*)em;
            if (enemy->getLife() > 0 && enemy->getBoundingBox().intersectsRect(bullet->boundingBox())) {
                deletebullets->addObject(bullet);
                enemy->loseLife();
                if (enemy->getLife() <= 0) {
                    deleteEnemys->addObject(enemy);
                }
            }

        }
        CCARRAY_FOREACH(deleteEnemys, bt){
            Enemy* enemy = (Enemy*)bt;
            this->enemyLayer->enemyBlowUp(enemy, enemy->getType());
            
            switch (enemy->getType()) {
                case Level1:
                    score += 100;
                    break;
                case Level2:
                    score += 200;
                    break;
                case Level3:
                    score += 500;
                    break;
                    
                default:
                    break;
            }
            this->labelLayer->updateScore(score);
        }
        deleteEnemys->removeAllObjects();
        deleteEnemys->release();
    }

    CCARRAY_FOREACH(deletebullets, bt){
        CCSprite* bullet = (CCSprite*)bt;
        this->bulletLayer->removeBullet(bullet);
    }
    deletebullets->removeAllObjects();
    deletebullets->release();
    
    //敌机和玩家碰撞
    CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1, em){
        Enemy* enemy = (Enemy*)em;
        if (enemy->getLife()>0 && this->playerLayer->isAlive && enemy->getBoundingBox().intersectsRect(this->playerLayer->getChildByTag(0)->boundingBox())) {
            this->unscheduleAllSelectors();
            this->bulletLayer->stopShoot();
            this->playerLayer->blowUp(score);
            return;
        }
    }
    
    //道具碰撞
    CCArray* deleteProps = CCArray::create();
    deleteProps->retain();
    CCARRAY_FOREACH(this->propLayer->m_AllProps, pp){
        CCSprite* prop = (CCSprite*)pp;
        if (this->playerLayer->getChildByTag(0)->boundingBox().intersectsRect(prop->boundingBox())) {
            bigBombCount++;
            updateBombCount(bigBombCount);
            deleteProps->addObject(pp);
        }
    }
    CCARRAY_FOREACH(deleteProps, pp){
        CCSprite* prop = (CCSprite*)pp;
        this->propLayer->removeProp(prop);
    }

}

void GameLayer::updateBombCount(int bombCount){
    CCString* bombStr = CCString::createWithFormat("%d",bombCount);
    m_bombCount->setString(bombStr->getCString());
    
}

void GameLayer::bombMenuCallBack(CCNode *pSender){
    if(bigBombCount > 0){
        CCObject* em;
        CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1, em){
            Enemy* enemy = (Enemy*)em;
            this->enemyLayer->enemyBlowUp(enemy, enemy->getType());
            switch (enemy->getType()) {
                case Level1:
                    score += 100;
                    break;
                case Level2:
                    score += 200;
                    break;
                case Level3:
                    score += 500;
                    break;
                    
                default:
                    break;
            }
            this->labelLayer->updateScore(score);
        }
        bigBombCount--;
        updateBombCount(bigBombCount);
    }
}

Level GameLayer::getGameLevel(){
    return gameLevel;
}

CCSize GameLayer::getSize(){
    return CCDirector::sharedDirector()->getWinSize();
}