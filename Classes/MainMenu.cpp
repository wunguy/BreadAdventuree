#include "MainMenu.h"
#include "GameSce.h"
#include "ui/UIButton.h"
//#include "MrBread.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //Background
    auto Bg = Sprite::create("MenuBackground.png");
    Bg->setPosition(visibleSize/2);
    this->addChild(Bg);

    //auto Bread = Mrbread::createMrbread();
    //Bread->setPosition(visibleSize / 2);
    //this->addChild(Bread);


    //PlayButton

    auto pbutton = ui::Button::create("Play_Button_Normal.png", "Play_Button_Pressed.png", "Play_Button_Normal.png");
    pbutton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            auto gameScene = GameSce::createScene();
            Director::getInstance()->pushScene(gameScene);
            break;
        }
        });
    pbutton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
    this->addChild(pbutton);

    auto qbutton = ui::Button::create("Quit_Button_Normal.png", "Quit_Button_Pressed.png", "Quit_Button_Normal.png");
    qbutton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->end();
            break;
        }
        });
    qbutton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(qbutton);
    //setting
    auto sbutton = ui::Button::create("setting1.png", "setting2.png", "setting3.png");
    sbutton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->end();
            break;
        }
        });
    sbutton->setPosition(Vec2(visibleSize.width-50, visibleSize.height-50));
    this->addChild(sbutton);
    return true;
}


void MainMenu::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

}