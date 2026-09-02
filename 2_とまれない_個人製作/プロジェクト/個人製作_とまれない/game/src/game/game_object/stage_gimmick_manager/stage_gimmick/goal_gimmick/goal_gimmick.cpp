#include "goal_gimmick.h"
#include"..\..\..\..\scene_manager\scene_manager.h"
const aqua::CVector2 CGoalGimmick::m_collsion_size = { 120.0f,(float)aqua::GetWindowHeight()};
const aqua::CVector2 CGoalGimmick::m_texture_size = { 120.0f,120.0f };
const int CGoalGimmick::m_damage = 0;
const int CGoalGimmick::m_score = 10000;

CGoalGimmick::CGoalGimmick(aqua::IGameObject* parent)
	:IStageGimmick(parent, "GoalGimmick", m_damage, m_collsion_size, m_texture_size)
{
}

void CGoalGimmick::Initialize(const aqua::CVector2& position, const bool set_flag)
{
	m_Position.x = position.x + m_BlockSize.x / 2.0f - m_Texture_Size.x / 2.0f;
	m_Position.y = position.y + m_BlockSize.y - m_Texture_Size.y;
	m_Sprite.Create("data\\goal.png");
	m_Sprite.color = aqua::CColor(255, 255, 255, 255);
	m_Id = STAGE_GIMMICK_ID::GOAL;
	m_Set = set_flag;
}

void CGoalGimmick::PlayerHit(void)
{
	CScoreManager* score_manager = (CScoreManager*)aqua::FindGameObject("ScoreManager");
	if(score_manager)
	{
		score_manager->AddScore(m_score);
	}
	//ゴールに当たったときの処理
}
