#include "TextureManager.h"

#include <iostream>
#include <ostream>
#include <SDL_image.h>



SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{

	// load image
	SDL_Surface* pImageSurface = IMG_Load(fileName);
	if (pImageSurface == nullptr)
	{
		std::cout << "image loading failed. Error: " << SDL_GetError() << std::endl;
	}

	// Convert surface to texture
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(SDL_Game::m_pRenderer, pImageSurface);
	if (pTexture == nullptr)
	{
		std::cout << "Texture loading failed. Error: " << SDL_GetError() << std::endl;
	}

	// Free surface
	SDL_FreeSurface(pImageSurface);

	return pTexture;
}

void TextureManager::Draw(SDL_Texture* pTexture, SDL_Rect scr, SDL_Rect dest)
{
	SDL_RenderCopy(SDL_Game::m_pRenderer, pTexture, &scr, &dest);
}

void TextureManager::Draw(SDL_Texture* pTexture, SDL_Rect dest)
{
	SDL_RenderCopy(SDL_Game::m_pRenderer, pTexture, nullptr, &dest);
}
