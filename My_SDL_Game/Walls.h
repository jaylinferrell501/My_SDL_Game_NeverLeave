#pragma once
#include "Tile.h"

class Walls : public Tile 
{
	Collider mCollider;

public:
	Walls(SDL_Rect scr, SDL_Rect dest, CollisionManager* pCollisionManager, const char* filename);
	~Walls() = default;
	void Renderer() override;
	void Update(double deltaTime) override;
	void OnCollision(Collider* pCollider) override;
};

