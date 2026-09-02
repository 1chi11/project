#include "wall_hit.h"
const float CWallEffect::m_effect_size = 25.0f;
CWallEffect::CWallEffect(IGameObject* parent)
	: IEffect(parent, "WallEffect")
{
}

void CWallEffect::Initialize(const aqua::CVector2& position)
{
	m_Sprite.Create("data\\wall_hit.png");
	m_Sprite.position = position;
	m_Sprite.position.x -= m_effect_size/2.0f;
	m_Sprite.position.y -= m_effect_size / 2.0f;
}


void CWallEffect::Draw(void)
{
	m_Sprite.Draw();
}

