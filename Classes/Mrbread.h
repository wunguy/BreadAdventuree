#ifndef __MRBREAD_H__
#define __MRBREAD_H__

#include "cocos2d.h"

enum pState {
	stand,
	run,
	jump,
	fall,
	standback,
	runback,
	jumpback,
	fallback
};

class Mrbread : public cocos2d::Node {
public:
	virtual bool init();

	void Mrbread::initBody();
	void Mrbread::doAction(const char* actionName);
	void Mrbread::actionSet();
	pState getState() { return m_state; };//


	void Stand();

	void Run();

	void Jump();

	void StandBack();

	void RunBack();

	void JumpBack();

	virtual void update(float dt);

	CREATE_FUNC(Mrbread);

private:
	/*cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char* format, int count);*/
	cocos2d::Sprite* _hero;
	pState m_state;
};/**/

#endif