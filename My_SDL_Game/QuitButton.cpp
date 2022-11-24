#include "QuitButton.h"

#include "TextureManager.h"

QuitButton::QuitButton(SDL_Rect transform, SDL_Renderer* pRenderer)
{
	m_transform = transform;
}

QuitButton::~QuitButton()
{
}

void QuitButton::Renderer()
{
	if (mIsHighlighted)
	{
		y = false;
		if (!x)
			m_pTexture = TextureManager::LoadTexture("assets/ExitButton2.png");
		x = true;
	}
	else if (!mIsHighlighted)
	{
		x = false;
		if (!y)
			m_pTexture = TextureManager::LoadTexture("assets/ExitButton.png");
		y = true;
	}

	SDL_RenderCopy(SDL_Game::m_pRenderer, m_pTexture, nullptr, &m_transform);
}

void QuitButton::HandleEvent(SDL_Event* pEvent)
{
	switch (pEvent->type)
	{

	case SDL_MOUSEMOTION:
		// Mouse Movement
		mIsHighlighted = HitTest(pEvent->button.x, pEvent->button.y);
		break;

	case SDL_MOUSEBUTTONDOWN:
		// There's a callback and the mouse click was inside the button.
		if (m_callback != nullptr && HitTest(pEvent->button.x, pEvent->button.y))
		{
			Trigger();
		}
		break;
	}
}

void QuitButton::Trigger()
{
	if (m_callback != nullptr)
	{
		m_callback();
	}
}

bool QuitButton::HitTest(int x, int y)
{
	return (x >= m_transform.x && x < +m_transform.x + m_transform.w &&
		y >= m_transform.y && y < +m_transform.y + m_transform.h);
}