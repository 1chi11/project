#include "mouse_click.h"

CMouseClick::CMouseClick(aqua::IGameObject* parent)
	: IUi(parent, "MouseClick")
{
}

void CMouseClick::Initialize(aqua::CVector2 position)
{
		m_Sprite.position = position;
		m_Sprite.Create("data\\mouse_click.png");
}

void CMouseClick::Draw(void)
{
	m_Sprite.Draw();
}

void CMouseClick::Finalize(void)
{
	m_Sprite.Delete();
	DeleteObject();
}

