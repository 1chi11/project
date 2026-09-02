#include "character_hit.h"
const aqua::CVector2 CCharacterHit::m_scale_velocity = { 0.05f,0.05f };

CCharacterHit::CCharacterHit(IGameObject* parent)
	:IEffect(parent,"CharacterHit")
	,m_Scale(0.0f,0.0f)
{
}

void CCharacterHit::Initialize(const aqua::CVector2& position)
{
	m_Position = position;
	m_Sprite.position = position;
	m_Sprite.Create("data\\hit_effect.png");
	m_Sprite.anchor = aqua::CVector2{m_Sprite.GetTextureWidth()/2.0f,m_Sprite.GetTextureHeight()/2.0f};
}

void CCharacterHit::Update(void)
{
	m_Scale += m_scale_velocity*m_TimeSpeed;
	if (m_Sprite.scale.x > 2.0f)
		Finalize();
}

void CCharacterHit::Draw(const aqua::CVector2& travel_postion)
{
	m_Sprite.position = m_Position - travel_postion;
	m_Sprite.scale += m_Scale;
	m_Sprite.Draw();
}

void CCharacterHit::Finalize(void)
{
	m_Sprite.Delete();
	DeleteObject();
}
