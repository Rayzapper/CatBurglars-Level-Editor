#include "UIManager.h"

UIObject *startScreenUIBase;
UIButton *startScreenButtonNew, *startScreenButtonLoad;

UIManager::UIManager()
{
	startScreenUIBase = new UIObject();
	startScreenButtonNew = new UIButton();
	startScreenButtonLoad = new UIButton();
}

UIManager::~UIManager()
{
	delete startScreenUIBase;
	delete startScreenButtonNew;
	delete startScreenButtonLoad;
}

void UIManager::Render(bool start)
{

}

void UIManager::Initialize()
{
	UIObject::Initialize();
}