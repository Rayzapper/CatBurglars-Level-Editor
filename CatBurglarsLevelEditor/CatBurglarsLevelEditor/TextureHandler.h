#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include <SFML/Graphics.hpp>

class TextureHandler
{
public:
	TextureHandler();
	~TextureHandler();
	void Initialize();
	sf::Texture mTileTexture, mSelectorTexture, mSaveTexture, mLayerTexture;
	sf::Texture* GetTexture(int ID);
};

#endif