#include "Ui.h"

#include "PlayerCharacter.h"
#include "SDL_Game.h"


Ui::Ui(SDL_Rect transform, SDL_Renderer* pRenderer, PlayerCharacter* pPlayer)
	:m_pPlayer(pPlayer)
	,mUiBackground(transform, "assets/UI.png", SDL_Game::m_pRenderer)
{
	m_transform = transform;
}

Ui::~Ui()
= default;

void Ui::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}

void Ui::Renderer()
{
	mUiBackground.Renderer();

	const SDL_Rect health{ 32 * 25 + 10, 32, m_pPlayer->GetHealth(), 13 };
	SDL_SetRenderDrawColor(SDL_Game::m_pRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(SDL_Game::m_pRenderer, &health);

	const SDL_Rect mana{ 32 * 2 + 10, 64, m_pPlayer->GetMana(), 13 };
	SDL_SetRenderDrawColor(SDL_Game::m_pRenderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(SDL_Game::m_pRenderer, &mana);

	SDL_RenderPresent(SDL_Game::m_pRenderer);

}
