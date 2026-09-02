#include "effect.h"

IEffect::IEffect(aqua::IGameObject* parent, const std::string& object_name)
	:IGameObject(parent,"effect")
	,m_Position(0.0f,0.0f)
	, m_TimeSpeed(1.0f)
{
}

void IEffect::Initialize(const aqua::CVector2& position)
{
	m_Position = position;
}

void IEffect::Update()
{
}

void IEffect::Draw(const aqua::CVector2& travel_postion)
{
	m_Sprite.position = m_Position - travel_postion;
	m_Sprite.Draw();
}

void IEffect::Finalize()
{
	m_Sprite.Delete();
	DeleteObject();
}

void IEffect::SetTimeSpeed(float time_speed)
{
	m_TimeSpeed = time_speed;
}
