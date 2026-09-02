#include "life_point.h"
const float CLifePoint::m_width = 64.0f;

CLifePoint::CLifePoint(aqua::IGameObject* parent)
	:IUi(parent,"LifePoint")
	,m_Position(0.0f,0.0f)
	,m_Max(99)
{
}

void CLifePoint::Initialize(aqua::CVector2 position)
{
	m_Sprite = AQUA_NEW aqua::CSprite[m_Max];

	m_Position = position;
}

void CLifePoint::Draw(void)
{
	for (int i = 0;i < m_Max;i++)
	{
		m_Sprite[i].Draw();
	}
}

void CLifePoint::Finalize(void)
{
	AQUA_SAFE_DELETE_ARRAY(m_Sprite);

	IGameObject::Finalize();
}

void CLifePoint::SetLifePoint(int life)
{
	AQUA_SAFE_DELETE_ARRAY(m_Sprite);

	if (life <= 0)
	{
		return;
	}
	m_Max = life;
	m_Sprite = AQUA_NEW aqua::CSprite[m_Max];
	for (int i = 0;i < m_Max;i++)
	{
		m_Sprite[i].Create("data\\life.png");
		m_Sprite[i].position = m_Position;
		m_Sprite[i].position.x = m_Position.x+( m_width * i );
	}
}
