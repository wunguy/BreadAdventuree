#include "InputKey.h"

InputKey* InputKey::instance = NULL;

InputKey* InputKey::getInstance() {
	if (instance == NULL) {
	instance =	new InputKey();
	}
	return instance;
}

bool InputKey::CheckKey(int i) 
{
	return Keys[i];
}
void InputKey::onKeyPresses(int i)
{
	Keys[i] = true;
}
void InputKey::onKeyReleased(int i)
{
	Keys[i] = false;
}