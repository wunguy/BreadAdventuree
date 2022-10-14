#include "Mrbread.h"

USING_NS_CC;

bool Mrbread::init() {


    auto frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("MrBread.plist", "MrBread.png");

    _hero = Sprite::createWithSpriteFrameName("MrBreadForward1.png");
    _hero->setScale(1.5);
    _hero->setPosition(Vec2(-0, 0));
    this->addChild(_hero);

    actionSet();

    initBody();

    this->m_state = fall;
    this->scheduleUpdate();

    this->setTag(1);

    return true;
}

void Mrbread::initBody() {
    Size bodySize;
    bodySize.width -= 50;
    bodySize.height -= 120;

    auto heroBody = PhysicsBody::createBox(bodySize, PhysicsMaterial(0.0f, 0.0f, 0.0f));
    heroBody->setRotationEnable(false);
    heroBody->setCategoryBitmask(1);
    heroBody->setCollisionBitmask(1);
    heroBody->setContactTestBitmask(1);

    this->setPhysicsBody(heroBody);
}

void Mrbread::actionSet() {

    SpriteFrame* frame = NULL;

    char file[100] = { 0 };

    Vector<SpriteFrame*>frameVector;

    //-----Stand-----
    for (int i = 1; i <= 3; i++) {
        sprintf(file, "MrBreadForward%d.png", i);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
        frameVector.pushBack(frame);
    }
    auto stand_animation = Animation::createWithSpriteFrames(frameVector, 0.1f, -1);
    AnimationCache::getInstance()->addAnimation(stand_animation, "stand");
    //-----Run-----
    frameVector.clear();
    for (int i = 1; i <= 8; i++) {
        sprintf(file, "MrBreadRunf%d.png", i);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
        frameVector.pushBack(frame);
    }
    auto Run_animation = Animation::createWithSpriteFrames(frameVector, 0.1f, -1);
    AnimationCache::getInstance()->addAnimation(Run_animation, "run");
    //-----Jump----
    
    frameVector.clear();
    for (int i = 1; i <= 2; i++) {
        sprintf(file, "MrBreadJump%d.png", i);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
        frameVector.pushBack(frame);
    }
    auto jump_animation = Animation::createWithSpriteFrames(frameVector, 0.1f, -1);
    AnimationCache::getInstance()->addAnimation(jump_animation, "jump");
    //fall
    frameVector.clear();
    for (int i = 1; i <= 2; i++) 
    {
        sprintf(file, "MrBreadFall%d.png",i);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
        frameVector.pushBack(frame);
    }
    auto fall_animation = Animation::createWithSpriteFrames(frameVector, 0.1f, -1);
    AnimationCache::getInstance()->addAnimation(fall_animation, "fall");

    //-----StandBack-----
    for (int i = 1; i <= 3; i++) {
        sprintf(file, "MrBreadBack%d.png", i);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
        frameVector.pushBack(frame);
    }
    auto standb_animation = Animation::createWithSpriteFrames(frameVector, 0.1f, -1);
    AnimationCache::getInstance()->addAnimation(standb_animation, "standback");
    //-----RunBack-----
    frameVector.clear();
    for (int i = 1; i <= 8; i++) {
        sprintf(file, "MrBreadRunb%d.png", i);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
        frameVector.pushBack(frame);
    }
    auto Runb_animation = Animation::createWithSpriteFrames(frameVector, 0.1f, -1);
    AnimationCache::getInstance()->addAnimation(Runb_animation, "runback");
    //-----JumpBack----

    frameVector.clear();
    for (int i = 1; i <= 2; i++) {
        sprintf(file, "MrBreadJumpb%d.png", i);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
        frameVector.pushBack(frame);
    }
    auto jumpb_animation = Animation::createWithSpriteFrames(frameVector, 0.1f, -1);
    AnimationCache::getInstance()->addAnimation(jumpb_animation, "jumpback");
    //-----FallBack----
    frameVector.clear();
    for (int i = 1; i <= 2; i++)
    {
        sprintf(file, "MrBreadFallb%d.png", i);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
        frameVector.pushBack(frame);
    }
    auto fallb_animation = Animation::createWithSpriteFrames(frameVector, 0.1f, -1);
    AnimationCache::getInstance()->addAnimation(fallb_animation, "fallback");
    

}
void Mrbread::doAction(const char* actionName) {
    auto animation = AnimationCache::getInstance()->getAnimation(actionName);
    auto action = Animate::create(animation);
    _hero->runAction(action);
}

void Mrbread::Stand() {
    log(" %d", (int)m_state);

    if (m_state == stand) return;
    log("stand %d", (int)m_state);
    _hero->stopAllActions();
    m_state = stand;
    //initBody();
    
    doAction("stand");
    //this->setPosition(0,0);
}
void Mrbread::Run()
{
    if (m_state == run || m_state == jump || m_state == fall) return;
    m_state = run;
    _hero->stopAllActions();

    //initBody();
    doAction("run");
}
void Mrbread::Jump() {
    if (m_state == stand || m_state == run) {
        m_state = jump;

        auto mass = this->getPhysicsBody()->getMass() * 500;

        this->getPhysicsBody()->applyImpulse(Vect(0, mass));

        _hero->stopAllActions();

        doAction("jump");
    }
}
void Mrbread::update(float dt) {
    auto vel = this->getPhysicsBody()->getVelocity();
    if (m_state == jump) {
        if (vel.y < 0.1) {
            m_state = fall;
            _hero->stopAllActions();
            doAction("fall");
        }
    }

    if (m_state == fall) {
        if (vel.y > 0) {
            Stand();
        }
    }
    if (m_state == jumpback) {
        if (vel.y < 0.1) {
            m_state = fallback;
            _hero->stopAllActions();
            doAction("fallback");
        }
    }

    if (m_state == fallback) {
        if (vel.y > 0) {
            StandBack();
        }
    }
}
void Mrbread::StandBack() {
    log(" %d", (int)m_state);

    if (m_state == standback) return;
    log("stand %d", (int)m_state);
    _hero->stopAllActions();
    m_state = standback;
    //initBody();

    doAction("standback");
    //this->setPosition(0,0);
}
void Mrbread::RunBack()
{
    if (m_state == runback || m_state == jumpback || m_state == fallback) return;
    m_state = runback;
    _hero->stopAllActions();

    //initBody();
    doAction("runback");
}
void Mrbread::JumpBack() {
    if (m_state == standback || m_state == runback) {
        m_state = jumpback;

        auto mass = this->getPhysicsBody()->getMass() * 500;

        this->getPhysicsBody()->applyImpulse(Vect(0, mass));

        _hero->stopAllActions();

        doAction("jumpback");
    }
}