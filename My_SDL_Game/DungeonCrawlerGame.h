#pragma once
#include <SDL_mixer.h>

#include "GameStateMachine.h"
#include "SDL_Game.h"
#include "CollisionManager.h"
#include "PlayerCharacter.h"
#include "SDL_ttf.h"
class GameState;

class DungeonCrawlerGame : public GameStateMachine
{
public:
	enum SceneName
	{
		Menu,
		TutorialScreen,
		BossStageScreen,
		LoseState,
		WinState
	};

private:

	// SDL_Game Object that is running the state machine.
	SDL_Game* m_pOwner;

	// Currently active scene.
	GameState* m_pCurrentState;

	// Any state waiting to be loaded on the next frame.
	GameState* m_pNextState;

	CollisionManager pCollisionManager;

	// Pointer to loaded music data.
	Mix_Music* m_pMusic;
	Mix_Music* m_pMusic2;
	bool mMusic2Playing = false;

	// Font for rendering.
	TTF_Font* m_pFont;
	TTF_Font* m_pFont2;

public:
	DungeonCrawlerGame(SDL_Game* pOwner);
	~DungeonCrawlerGame() override;

	// Returns a pointer to the SDL_Game object for access to system objects.
	SDL_Game* GetGame() { return m_pOwner; }

	// Update the current game state.
	void UpdateCurrentState(double deltaTime) override;

	// Render the current game state.
	void RenderCurrentState(SDL_Renderer* pRenderer) override;

	// Handle the given event within the current state.
	bool HandleEvent(SDL_Event* pEvent) override;

	// Exits current state and enters new state
	void ChangeState(GameState* pNewState) override;

	// Loads the given scene.
	void LoadScene(SceneName scene);

	bool Init() override;
};

