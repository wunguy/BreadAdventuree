#include "GameSce.h"
#include "PauseScene.h"
#include "ui/UIButton.h"
#include "GameOver.h"
#include "WinScene.h"
#include "InputKey.h"


USING_NS_CC;

Scene* GameSce::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	scene->getPhysicsWorld()->setGravity(Vec2(0, -980));
	auto layer = GameSce::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameSce::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	InputKey::getInstance()->reset();


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//Background
	/*auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 -100, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);*/

	/*auto map = TMXTiledMap::create("test.tmx");
	map->setPosition(visibleSize / 2);
	map->setScale(0.8f);
	map->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	addChild(map, 0, 99);

	auto wallO = map->getObjectGroup("tuong");
	auto a = wallO->getObjects();
	for (int i = 0; i < a.size(); i++)
	{
		float width, height;
		int x, y;
		auto b = a[i].asValueMap();
		width = b.at("width").asFloat();
		height = b.at("height").asFloat();
		x = b.at("x").asInt();;
		y= b.at("y").asInt();;

		auto node = Node::create();
		auto body = PhysicsBody::createBox(Size(width, height), PHYSICSBODY_MATERIAL_DEFAULT);
		body->setDynamic(false);
		node->setPhysicsBody(body);
		node->setPosition(x, y);
		
		map->addChild(node);
	}
	map->setPosition(Vec2::ANCHOR_MIDDLE);
	map->setPosition(visibleSize/2);*/

	auto Map = Sprite::create("Map1.png");
	Map->setPosition(visibleSize / 2);
	auto Mapborder = PhysicsBody::createEdgeBox(Map->getContentSize(), PhysicsMaterial(0, 0, 1), 1);;
	Map->setPhysicsBody(Mapborder);
	Map->setScale(0.8f);
	Mapborder->setContactTestBitmask(1);
	Mapborder->setCollisionBitmask(1);
	Mapborder->setContactTestBitmask(1);
	Map->setTag(2);
	this->addChild(Map);



	auto Door = PhysicsBody::createBox(Size::Size(98, 145));
	auto doorNode = Node::create();
	doorNode->setPhysicsBody(Door);
	doorNode->setPosition(Vec2(visibleSize.width / 2 + 575, visibleSize.height / 2 - 262));
	Door->setDynamic(false);
	Door->setContactTestBitmask(1);
	Door->setCollisionBitmask(1);
	Door->setContactTestBitmask(1);
	doorNode->setTag(3);
	this->addChild(doorNode);

	auto Brick = PhysicsBody::createBox(Size::Size(1010, 145));
	auto brickNode = Node::create();
	brickNode->setPhysicsBody(Brick);
	brickNode->setPosition(Vec2(visibleSize.width / 2 - 210, visibleSize.height / 2 - 410));
	Brick->setDynamic(false);
	this->addChild(brickNode);

	auto Brick1 = PhysicsBody::createBox(Size::Size(200, 145));
	auto brickNode1 = Node::create();
	brickNode1->setPhysicsBody(Brick1);
	brickNode1->setPosition(Vec2(visibleSize.width / 2 + 575, visibleSize.height / 2 - 410));
	Brick1->setDynamic(false);
	this->addChild(brickNode1);
	//Character


	_hero = Mrbread::create();
	_hero->setPosition(visibleSize / 2);
	_hero->Stand();
	this->addChild(_hero);
	this->schedule(CC_SCHEDULE_SELECTOR(GameSce::UpdateEventKey, this));
	//contact



	////moving

	//Contact
	auto ListenerContact = EventListenerPhysicsContact::create();
	ListenerContact->onContactBegin = CC_CALLBACK_1(GameSce::onContact, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(ListenerContact, this);
	//Pause
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameSce::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameSce::keyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	/*   keyboardListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event)
	   {
		   switch (keyCode)
		   {
		   case EventKeyboard::KeyCode::KEY_ESCAPE:
			   auto PauseScene = PauseScene::createScene();
			   Director::getInstance()->pushScene(PauseScene);

			   break;
		   }
	   };*/

	   //
	auto sbutton = ui::Button::create("setting1.png", "setting2.png", "setting3.png");
	sbutton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			auto PauseScene = PauseScene::createScene();
			Director::getInstance()->pushScene(PauseScene);
			break;
		}
		});
	sbutton->setPosition(Vec2(visibleSize.width - 50, visibleSize.height - 50));
	this->addChild(sbutton);


	return true;
}

bool GameSce::onContact(PhysicsContact& contact)
{
	auto body1 = contact.getShapeA()->getBody()->getNode();
	auto body2 = contact.getShapeB()->getBody()->getNode();
	auto body3 = contact.getShapeB()->getBody()->getNode();
	log("%d %d", body1->getTag(), body2->getTag());
	if (body1->getTag() == 1 && body2->getTag() == 3 || body1->getTag() == 3 && body2->getTag() == 1)
	{
		auto WinScene = WinScene::createScene();
		Director::getInstance()->replaceScene(WinScene);
	}
	if (body1->getTag() == 1 && body2->getTag() == 2 || body1->getTag() == 2 && body2->getTag() == 1)
	{
		auto GameOver = GameOver::createScene();
		Director::getInstance()->replaceScene(GameOver);
	}

	/*if (body1->getTag() == 2 && body2->getTag() == 1)
	{
		auto GameOver = GameOver::createScene();
		Director::getInstance()->replaceScene(GameOver);
	}
	if(body1->getTag() == 1 && body2->getTag() == 3)
	{
		auto WinScene = WinScene::createScene();
		Director::getInstance()->replaceScene(WinScene);
	}*/

	return true;
};

void GameSce::UpdateEventKey(float dt)
{
	int keyA = (int)EventKeyboard::KeyCode::KEY_A;
	int keyW = (int)EventKeyboard::KeyCode::KEY_W;
	int keyD = (int)EventKeyboard::KeyCode::KEY_D;
	
	Vec2 v = _hero->getPhysicsBody()->getVelocity();
	
	if (InputKey::getInstance()->CheckKey(keyD))
	{
		_hero->Run();
		v.x = 200;
		_hero->getPhysicsBody()->setVelocity(v);

	}



	if (InputKey::getInstance()->CheckKey(keyA))
	{
		_hero->RunBack();
		v.x = -200;
		_hero->getPhysicsBody()->setVelocity(v);

	}

	if (!InputKey::getInstance()->CheckKey(keyA) && !InputKey::getInstance()->CheckKey(keyD)) {
		v.x = 0;
		_hero->getPhysicsBody()->setVelocity(v);
	}


	if (InputKey::getInstance()->CheckKey(keyW))
	{
		_hero->Jump();

	}

	if (!InputKey::getInstance()->CheckKey(keyA) && !InputKey::getInstance()->CheckKey(keyD) && _hero->getState() && _hero->getState() != jump && _hero->getState() != fall) {

		_hero->Stand();

	}
	/*if (!InputKey::getInstance()->CheckKey(keyA) && !InputKey::getInstance()->CheckKey(keyD) && _hero->getState() && _hero->getState() != jumpback && _hero->getState() != fallback)
	{
		_hero->StandBack();
	}*/


}
void GameSce::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{

	InputKey::getInstance()->onKeyPresses((int)keyCode);

}
void GameSce::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)

{
	InputKey::getInstance()->onKeyReleased((int)keyCode);

	//if (keyCode == EventKeyboard::KeyCode::KEY_D)
	//{
	//    //_hero->stopAllActions();
	//    _hero->Stand();
	//    _hero->getPhysicsBody()->setVelocity(Vec2(0, 0));
	//}
	//if (keyCode == EventKeyboard::KeyCode::KEY_A)
	//{
	//    //_hero->stopAllActions();
	//    _hero->Stand();
	//}
	//if (keyCode == EventKeyboard::KeyCode::KEY_A)
	//{
	//    //_hero->stopAllActions();
	//    _hero->Stand();
	//}
}


void GameSce::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}