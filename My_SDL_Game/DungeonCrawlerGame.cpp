#include "DungeonCrawlerGame.h"

#include <iostream>

#include "BossStage.h"
#include "GameState.h"
#include "LoseScreen.h"
#include "MainMenu.h"
#include "Tutorial.h"
#include "WinScreen.h"


DungeonCrawlerGame::DungeonCrawlerGame(SDL_Game* pOwner)
	:m_pOwner(pOwner)
	,m_pCurrentState(nullptr)
	,m_pNextState(nullptr)
	,m_pFont(nullptr)
{ 
}

DungeonCrawlerGame::~DungeonCrawlerGame()
{

	if (m_pFont != nullptr)
	{
		TTF_CloseFont(m_pFont);
	}

	if (m_pMusic != nullptr)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(m_pMusic);
		Mix_FreeMusic(m_pMusic2);
	}

	// exit the current state.
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Exit();
	}

	// delete the current state
	delete m_pCurrentState;
}

void DungeonCrawlerGame::UpdateCurrentState(double deltaTime)
{
	if (!Mix_PlayingMusic() && mMusic2Playing == false)
	{
		Mix_PlayMusic(m_pMusic2, 0);
		mMusic2Playing = true;
	}

	if (!Mix_PlayingMusic() && mMusic2Playing == true)
	{
		Mix_PlayMusic(m_pMusic, 0);
		mMusic2Playing = false;

	}

	// Perform actual state change here
	if(m_pNextState != nullptr)
	{
		ChangeState(m_pNextState);
		m_pNextState = nullptr;
	}

	// If My current state is not null call update.
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Update(deltaTime);
	}
}

void DungeonCrawlerGame::RenderCurrentState(SDL_Renderer* pRenderer)
{
	// If My current state is not null call Render.
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Render();
	}
}

bool DungeonCrawlerGame::HandleEvent(SDL_Event* pEvent)
{
	// If My current state is not null return HandleEvent.
	if (m_pCurrentState != nullptr)
	{
		return m_pCurrentState->HandleEvent(pEvent);
	}
	return false; // we do not exit.
}

void DungeonCrawlerGame::ChangeState(GameState* pNewState)
{
	// exit the current state.
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Exit();
	}
	// delete the old state
	delete m_pCurrentState;

	// load the new state.
	m_pCurrentState = pNewState;

	// enter the new state.
	pNewState->Enter();
}

void DungeonCrawlerGame::LoadScene(SceneName scene)
{
	switch (scene)
	{
	case Menu:
		ChangeState(new MainMenu{ this, m_pFont });
		break;
	case TutorialScreen:
		ChangeState(new Tutorial{ this, &pCollisionManager, m_pFont2});
		break;
	case LoseState:
		ChangeState(new LoseScreen{ this, m_pFont });
		break;
	case WinState:
		ChangeState(new WinScreen{ this, m_pFont });
		break;
	case BossStageScreen:
		ChangeState(new BossStage{ this, &pCollisionManager, m_pFont2 });
		break;
	}
}

bool DungeonCrawlerGame::Init()
{
	Mix_VolumeMusic(10);
	m_pFont = TTF_OpenFont("assets/Fonts/handwriting-draft_free-version.ttf", 54);
	m_pFont2 = TTF_OpenFont("assets/Fonts/handwriting-draft_free-version.ttf", 50);

	m_pMusic = Mix_LoadMUS("assets/MusicAndSound/Chopsticks.mp3");
	m_pMusic2 = Mix_LoadMUS("assets/MusicAndSound/Dungeon_Level.mp3");
	if (m_pMusic == nullptr)
	{
		std::cout << "Failed to load music. Error: " << Mix_GetError();
	}
	else
	{
		Mix_PlayMusic(m_pMusic, 0);
	}

	LoadScene(Menu);

	return true;
}
