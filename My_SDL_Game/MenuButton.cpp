#include "MenuButton.h"

#include "TextureManager.h"

MenuButton::MenuButton(SDL_Rect transform, SDL_Renderer* pRenderer)
	:x(false)
	,y(false)
{
	m_transform = transform;
}

MenuButton::~MenuButton()
{
}

void MenuButton::Renderer()
{
	if (mIsHighlighted)
	{
		y = false;
		if (!x)
			m_pTexture = TextureManager::LoadTexture("assets/Menu2Button.png");
		x = true;
	}
	else if (!mIsHighlighted)
	{
		x = false;
		if (!y)
			m_pTexture = TextureManager::LoadTexture("assets/MenuButton.png");
		y = true;
	}

	SDL_RenderCopy(SDL_Game::m_pRenderer, m_pTexture, nullptr, &m_transform);
}

void MenuButton::HandleEvent(SDL_Event* pEvent)
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

void MenuButton::Trigger()
{
	if (m_callback != nullptr)
	{
		m_callback();
	}
}

bool MenuButton::HitTest(int x, int y)
{
	return (x >= m_transform.x && x < +m_transform.x + m_transform.w &&
		y >= m_transform.y && y < +m_transform.y + m_transform.h);
}