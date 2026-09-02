#include "spike_gimmick.h"
const aqua::CVector2 CSpikeGimmick::m_collsion_size = { 120.0f,70.0f };
const aqua::CVector2 CSpikeGimmick::m_texture_size = { 120.0f,70.0f };
const int CSpikeGimmick::m_damage = 1;
const float CSpikeGimmick::m_height_adj = 58.0f;


CSpikeGimmick::CSpikeGimmick(aqua::IGameObject* parent)
	:IStageGimmick(parent, "SpikeGimmick", m_damage, m_collsion_size, m_texture_size)
{
}

void CSpikeGimmick::Initialize(const aqua::CVector2& position, const bool set_flag)
{
	m_Position.x = position.x + m_BlockSize.x / 2.0f - m_Texture_Size.x / 2.0f;
	m_Position.y = position.y + m_BlockSize.y - m_Texture_Size.y;
	m_Sprite.Create("data\\spike.png");
	m_Id = STAGE_GIMMICK_ID::SPIKE;
	m_Set = set_flag;
}



void CSpikeGimmick::PlayerHit(void)
{
}

