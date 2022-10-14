#pragma once
#include "cocos2d.h"
USING_NS_CC;
 class InputKey {
public:
	 static InputKey* getInstance();
	bool CheckKey(int i);
	void onKeyPresses(int i);
	void onKeyReleased(int i);
	void reset() {
		for (int i = 0; i < 165; i++) {
			Keys[i] = false;
		}
	}
private:
	InputKey() { }
	bool Keys[165] ={0};
 static	InputKey* instance;
};