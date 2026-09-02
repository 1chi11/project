#include "chara.h"
#include <cmath>
const float CChara::m_radius = 16.0f;

CChara::CChara(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Chara")
	, m_Position(0.0f, 0.0f)
	, m_Radius(m_radius)
{
}

void CChara::Initialize(const aqua::CVector2& position)
{
	m_Position = position;

	m_Sprite.Create("data\\chara.png");
	m_Sprite.position = position;
}

void CChara::Hit()
{
	Finalize();
}

float CChara::GetRadius()
{
	return m_Radius;
}


void CChara::Draw(void)
{
	m_Sprite.Draw();
}

void CChara::Finalize(void)
{
	m_Sprite.Delete();
	DeleteObject();
}

aqua::CVector2 CChara::GetCenterPosition()
{
	return aqua::CVector2(m_Position.x + m_Radius, m_Position.y + m_Radius);
}
