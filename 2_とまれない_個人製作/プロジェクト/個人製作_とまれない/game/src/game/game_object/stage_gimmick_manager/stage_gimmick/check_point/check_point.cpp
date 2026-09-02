#include "check_point.h"

const aqua::CVector2 CCheckPoint::m_collsion_size = { 120.0f,(float)aqua::GetWindowHeight()};
const aqua::CVector2 CCheckPoint::m_texture_size = { 120.0f,120.0f };
const int CCheckPoint::m_damage = 0;
const int CCheckPoint::m_score = 1000;

CCheckPoint::CCheckPoint(aqua::IGameObject* parent)
	:IStageGimmick(parent, "CheckPoint", m_damage, m_collsion_size, m_texture_size)
	, m_FirstHit(false)
{
}


void CCheckPoint::Initialize(const aqua::CVector2& position, const bool set_flag)
{
	m_Position.x = position.x + m_BlockSize.x / 2.0f - m_Texture_Size.x / 2.0f;
	m_Position.y = position.y + m_BlockSize.y - m_Texture_Size.y;

	m_Sprite.Create("data\\check_point.png");
	m_Id = STAGE_GIMMICK_ID::CHECK_POINT;
	m_Set = set_flag;
}

void CCheckPoint::PlayerHit(void)
{
	if (!m_FirstHit)
	{
		m_Sprite.color = 0xffff0000;
		CSoundPlayManager* sound = (CSoundPlayManager*)aqua::FindGameObject("SoundPlayManager");
		if (sound)
			sound->Play(SOUND_ID::CHECK_POINT);
		CScoreManager* score_manager = (CScoreManager*)aqua::FindGameObject("ScoreManager");
		if (score_manager)
			score_manager->AddScore(m_score);
		m_FirstHit = true;
	}
}
