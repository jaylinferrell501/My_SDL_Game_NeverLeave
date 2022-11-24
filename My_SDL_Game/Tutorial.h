#pragma once
#include "BackGround.h"
#include "Coins.h"
#include "Door.h"
#include "DungeonCrawlerGame.h"
#include "GameState.h"
#include "Ghost.h"
#include "KeyboardAndMouse.h"
#include "PlayerCharacter.h"
#include "Switch.h"

class Tutorial : public GameState
{
	// Map
	// 20 rows and 25 col
	int mTutorialLevel[20][25] = {
		{3,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,7,},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},
		{1,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,6,},
		{1,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,6,},
		{1,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,6,},
		{1,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,6,},
		{1,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,6,},
		{1,0,0,0,0,0,0,0,0,9,9,9,9,9,0,0,0,0,0,0,0,0,0,0,6,},
		{1,0,0,0,0,0,0,0,0,9,9,9,9,9,0,0,0,0,0,0,0,0,0,0,6,},
		{1,0,0,0,0,0,0,0,0,9,9,9,9,9,0,0,0,0,0,0,0,0,0,0,6,},
		{1,0,0,0,0,0,0,0,0,9,9,9,9,9,0,0,0,0,0,0,0,0,0,0,6,},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},
		{1,0,0,0,0,0,0,0,0,10,10,10,10,10,0,0,0,0,0,0,0,0,0,0,6,},
		{1,0,0,0,0,0,0,0,0,10,10,10,10,10,0,0,0,0,0,0,0,0,0,0,6,},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},
		{5,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,8,},
	};

	// Pointer to the state machine running this state.
	DungeonCrawlerGame* m_pOwner;

	PlayerCharacter* mpPlayer;

	CollisionManager* mpCollisionManager;

	// Controller
	KeyboardAndMouse mController;

	// Storing all game objects in a vector
	std::list<GameObject*> mGameObjects;

	bool mDead = false;
	
public:
	Tutorial(DungeonCrawlerGame* pOwner, CollisionManager* pCollisionManager, TTF_Font* pFont);
	~Tutorial() override;

	void Render() override;

	void Update(double deltaTime) override;

	bool HandleEvent(SDL_Event* pEvent) override;
};

