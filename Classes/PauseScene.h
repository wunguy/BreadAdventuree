
#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"

class PauseScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(PauseScene);
    void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};

#endif