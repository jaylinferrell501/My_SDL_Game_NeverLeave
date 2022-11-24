#include "BossStage.h"

#include <iostream>

#include "BackGround.h"
#include "Bat.h"
#include "GuardZombie.h"
#include "UITextField.h"

BossStage::BossStage(DungeonCrawlerGame* pOwner, CollisionManager* pCollisionManager, TTF_Font* pFont)
	:m_pOwner(pOwner)
	, mpCollisionManager(pCollisionManager)
{
	// Main Menu BackGround
	mGameObjects.push_back(new BackGround(SDL_Rect{ 0, 0, 800, 640 }, "assets/bossStageBackGround.png", SDL_Game::m_pRenderer));

	// Map
	mGameObjects.push_back(new TileMap(pCollisionManager, "assets/Levels/RoomTemplet.txt"));

	// Player
	mpPlayer = new PlayerCharacter(393, 540, pCollisionManager);
	mGameObjects.push_back(mpPlayer);

	// BatBoss
	mpBat = new Bat(Vector2<float>{410, 279}, Vector2<float>{80, 80}, mpPlayer, pCollisionManager);
	mGameObjects.push_back(mpBat);

	//BatBaby
	mGameObjects.push_back(new GuardZombie(Vector2<float>{64, 64}, Vector2<float>{16, 16}, mpPlayer, pCollisionManager, 70));
	mGameObjects.push_back(new GuardZombie(Vector2<float>{32 * 15, 64}, Vector2<float>{20, 20}, mpPlayer, pCollisionManager, 80));
	mGameObjects.push_back(new GuardZombie(Vector2<float>{32 * 20, 64}, Vector2<float>{20, 20}, mpPlayer, pCollisionManager, 90));
	mGameObjects.push_back(new GuardZombie(Vector2<float>{32 * 22, 64}, Vector2<float>{20, 20}, mpPlayer, pCollisionManager, 100));

	mGameObjects.push_back(new UITextField(pFont, "Bat", SDL_Color{ 255,0,0, SDL_ALPHA_OPAQUE },
		Vector2{ 32 * 12, 32 * 22 }, SDL_Game::m_pRenderer));
}

BossStage::~BossStage()
{
	for (const auto& mGameObject : mGameObjects)
	{
		delete mGameObject;
	}
}

void BossStage::Render()
{
	SDL_SetRenderDrawColor(SDL_Game::m_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(SDL_Game::m_pRenderer);

	// Render GameObjects
	for (const auto& mGameObject : mGameObjects)
	{
		mGameObject->Renderer();
	}

	// UI
	// TODO Make a Ui Component
	const SDL_Rect health{ 32 * 25 + 10, 32, mpPlayer->GetHealth(), 13 };
	SDL_SetRenderDrawColor(SDL_Game::m_pRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(SDL_Game::m_pRenderer, &health);
	const SDL_Rect mana{ 32 * 25 + 10, 64, mpPlayer->GetMana(), 13 };
	SDL_SetRenderDrawColor(SDL_Game::m_pRenderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(SDL_Game::m_pRenderer, &mana);

	const SDL_Rect bossHealth{32 * 5, 32 * 24, mpBat->GetHealth(), 13 };
	SDL_SetRenderDrawColor(SDL_Game::m_pRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(SDL_Game::m_pRenderer, &bossHealth);
	SDL_RenderPresent(SDL_Game::m_pRenderer);
}

void BossStage::Update(double deltaTime)
{
	GameState::Update(deltaTime);

	GameObject* toDelete = nullptr;
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
	if (toDelete != nullptr)
	{
		if (toDelete->GetName() == "ZombieGuard")
		{
 			int health = mpBat->GetHealth() - 50;
			mpBat->SetHealth(health);
		}
			
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

bool BossStage::HandleEvent(SDL_Event* pEvent)
{
	bool quit = mController.KeyboardAndMouseInputHandler(mpPlayer, pEvent, m_pOwner);

	if (quit)
	{
		return true;
	}

	if (mpBat->GetHealth() == 0)
	{
		m_pOwner->LoadScene(DungeonCrawlerGame::WinState);
	}

	return false;
}
