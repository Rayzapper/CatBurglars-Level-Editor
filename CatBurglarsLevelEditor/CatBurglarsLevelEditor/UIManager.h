#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "UIObject.h"
#include "UIButton.h"

class UIManager
{
public:
	UIManager();
	~UIManager();
	void Render(bool start);
	static void Initialize();
};

#endif