#pragma once
#include "BackGround.h"
#include "GameObject.h"

class PlayerCharacter;

class Ui : public GameObject 
{
	PlayerCharacter* m_pPlayer;
	BackGround mUiBackground;

public:
	Ui(SDL_Rect transform, SDL_Renderer* pRenderer, PlayerCharacter* pPlayer);
	~Ui() override;
	void Update(double deltaTime) override;
	void Renderer() override;
};

