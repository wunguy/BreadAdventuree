#include "PauseScene.h"
#include "MainMenu.h"
#include "ui/UIButton.h"
#include "GameSce.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
    return PauseScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool PauseScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //PlayAgain
    auto pabutton = ui::Button::create("Replay_Button_Normal.png", "Replay_Button_Pressed.png", "Replay_Button_Normal.png");
    pabutton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            auto GameSce = GameSce::createScene();
            Director::getInstance()->popScene();
            Director::getInstance()->replaceScene(GameSce);
            break;
        }
        });
    pabutton->setScale(2);
    pabutton->setPosition(Vec2(visibleSize.width/2-150,visibleSize.height/2-100));
    this->addChild(pabutton);
    //Resume
    auto rbutton = ui::Button::create("Resume_Button_Normal.png", "Resume_Button_Pressed.png", "Resume_Button_Normal.png");
    rbutton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->popScene();
            break;
        }
        });
    rbutton->setScale(2);
    rbutton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));
    this->addChild(rbutton);
    //MainMenu
    auto mbutton = ui::Button::create("Menu_Button_Normal.png", "Menu_Button_Pressed.png", "Menu_Button_Normal.png");
    mbutton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            auto mainMenu = MainMenu::createScene();
            Director::getInstance()->replaceScene(mainMenu);
            break;
        }
        });
    mbutton->setScale(2);
    mbutton->setPosition(Vec2(visibleSize.width / 2 + 150, visibleSize.height / 2 - 100));
    this->addChild(mbutton);

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(PauseScene::keyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(PauseScene::keyReleased, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    keyboardListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event)
    {
        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_ESCAPE:
            auto PauseScene = PauseScene::createScene();
            Director::getInstance()->popScene();
            break;
        }
    };

    auto label = Label::createWithTTF("PAUSE", "fonts/Marker Felt.ttf", 99);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    { 
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        this->addChild(label, 1);
    }
    return true;
}

void PauseScene::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{

}
void PauseScene::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{

}

void PauseScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}