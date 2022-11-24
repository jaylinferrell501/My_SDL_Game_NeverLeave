#pragma once

#include <list>
#include <SDL_mixer.h>

#include "Animator.h"
#include "GameObject.h"
#include "Collider.h"
#include "FireBall.h"

class PlayerCharacter : public GameObject
{
	using Vector2 = Vector2<float>;

	// Shape color
	static constexpr int k_pShapeColor[] = { 0, 255, 0, SDL_ALPHA_OPAQUE };

	// Width
	static constexpr int s_width = 80;

	// Length
	static constexpr int s_length = 80;

	// Stamina
	double mStamina;

	Animator m_Movement;

	// collider component for checking
	Collider m_collider;

	Collider* GetColider() { return &m_collider; }

	SDL_Rect mBoxColider{ m_Movement.GetTransform().x, m_Movement.GetTransform().y, 32, 32 };
	int mili = 0;

	// Pointer to manager for registering and collision checking
	CollisionManager* m_pCollisionManager;

	// sound data.
	Mix_Chunk* m_pSound;

	Mix_Chunk* m_pHeal;

	Mix_Chunk* m_pCastFireBall;

	Mix_Chunk* m_pCoinCollected;

	std::list<FireBall*> mFireBalls;

	void MovementManager(double deltaTime);
	void AnimationManager();

public:
	PlayerCharacter(double x, double y, CollisionManager* pCollisionManager);
	~PlayerCharacter() override;
	void Update(double deltaTime) override;
	void Renderer() override;
	void OnCollision(Collider* pCollider) override;
	std::string TryMove(Vector2 deltaPosition);
	

	Animator GetAnimation() { return m_Movement; }
	

	// PLAYER STATS / Abilites.
private:
	int mHealth = 100;
	int mMana = 100;
	int mGold = 0;
public:
	int GetHealth() const { return mHealth; }
	int GetMana() const { return mMana; }
	int GetGold() const { return mGold; }
	void CasteFireBall(CollisionManager* pCollisionManager, double deltaTime);
	bool mCastedFireBall = false;

private:
	void Shoot(int direction_X, int direction_Y, int position_X, int position_Y, CollisionManager* pCollisionManager);
};


// Todo Add the Rest of MovementManager Ability
// Todo Clean up Code (Update)

