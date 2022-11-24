#pragma once

#include <SDL.h>

// A game state / scene interface.
class GameState
{
protected:
	
public:
	virtual ~GameState() = default;

	// Initializes the scene
	virtual void Enter() {}

	// Updates the scene.
	virtual void Update(double deltaTime) {}

	// Renders the scene.
	virtual void Render() {}

	// Handles the event in the context of this scene.
	virtual bool HandleEvent(SDL_Event* pEvent) { return false; }

	//Cleans up state before exit.
	virtual void Exit() {}

};

