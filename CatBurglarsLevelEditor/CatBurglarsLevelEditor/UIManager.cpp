#include "UIManager.h"

UIObject *startScreenUIBase, *startScreenButtonNew, *startScreenButtonLoad;

UIManager::UIManager()
{

}

UIManager::~UIManager()
{
	delete startScreenUIBase;
	delete startScreenButtonNew;
	delete startScreenButtonLoad;
}

void UIManager::Render()
{

}

void UIManager::Initialize()
{
	UIObject::Initialize();
}