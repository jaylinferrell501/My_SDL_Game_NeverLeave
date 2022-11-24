#include "Tutorial.h"

#include <iostream>

#include "Ui.h"
#include "UITextField.h"

Tutorial::Tutorial(DungeonCrawlerGame* pOwner, CollisionManager* pCollisionManager, TTF_Font* pFont)
	:m_pOwner(pOwner)
	, mpCollisionManager(pCollisionManager)
{
	// Map
	mGameObjects.push_back(new TileMap(pCollisionManager, "assets/Levels/RoomProrto.txt"));

	// Coins
	int y = 7;
	for (int i = 0; i < 6; i++)
	{
		mGameObjects.push_back(new Coins(SDL_Rect{ 64 * 2, 32 * y, 16, 16 }, mpCollisionManager));
		y += 2;
	}

	// Player
	mpPlayer = new PlayerCharacter(32 * 14, 32 * 10, pCollisionManager);
	mGameObjects.push_back(mpPlayer);

	//UI
	mGameObjects.push_back(new	Ui(SDL_Rect{ 0,0, 32 * 30, 32 * 3 }, SDL_Game::m_pRenderer, mpPlayer));
	//GoldCount
	//mGameObjects.push_back(new UITextField(pFont, "You Will Never Leave", SDL_Color{ 0,0,0, SDL_ALPHA_OPAQUE },
		//Vector2{ 32 * 5 + 1, 32 * 7 }, SDL_Game::m_pRenderer));
}

Tutorial::~Tutorial()
{
	for (const auto& mGameObject : mGameObjects)
	{
		delete mGameObject;
	}
}

void Tutorial::Render()
{
	SDL_SetRenderDrawColor(SDL_Game::m_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(SDL_Game::m_pRenderer);

	// Render GameObjects
	for (const auto& mGameObject : mGameObjects)
	{
		mGameObject->Renderer();
	}

}

void Tutorial::Update(double deltaTime)
{
	GameState::Update(deltaTime);

	GameObject* toDelete;
	// Update GameObjects4
	for (const auto& mGameObject : mGameObjects)
	{

		if (mGameObjects.empty())
			break;

		if (mGameObject != nullptr)
			mGameObject->Update(deltaTime);

		if (!mGameObject->GetActive())
			toDelete = mGameObject;
	}
	mGameObjects.remove(toDelete);

	if (mpPlayer->GetHealth() == 0)
	{
		mDead = true;
		if (mDead)
		{
			mDead = false;
			m_pOwner->LoadScene(DungeonCrawlerGame::LoseState);
		}

	}
}

bool Tutorial::HandleEvent(SDL_Event* pEvent)
{
	bool quit = mController.KeyboardAndMouseInputHandler(mpPlayer, pEvent, m_pOwner);

	if (quit)
	{
		return true;
	}

	return false;
}
