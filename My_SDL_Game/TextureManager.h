#pragma once
#include "SDL_Game.h"

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* pTexture, SDL_Rect scr, SDL_Rect dest);
	// load Full image
	static void Draw(SDL_Texture* pTexture, SDL_Rect dest);
};

