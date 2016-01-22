#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "UIObject.h"

class UIManager
{
public:
	UIManager();
	~UIManager();
	void Render();
	static void Initialize();
};

#endif