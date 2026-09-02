#include "score_manager.h"
#include"..\scene_manager\scene\game_main_scene\game_main_scene.h"
const aqua::CVector2 CScoreManager::m_score_label_position_gameplay = aqua::CVector2(800.0f, 0.0f);
const aqua::CVector2 CScoreManager::m_score_label_position_result = aqua::CVector2(0.0f, 200.0f);
const int CScoreManager::m_score_label_size_gameplay = 50;
const int CScoreManager::m_score_label_size_result = 100;

CScoreManager::CScoreManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "ScoreManager")
	, m_Score(nullptr)
	, m_Time(nullptr)
	, m_StageNumber(0)
	, m_MaxStage(0)
	, m_ClearFlag(false)
{
}

CScoreManager::~CScoreManager(void)
{
	FinalizeScore();
}

void CScoreManager::Initialize(void)
{
}

void CScoreManager::ResultDraw(void)
{
	for(int i = 0; i < m_MaxStage; i++)
	{
		m_ScoreLabel.text = "STAGE" + std::to_string(i + 1) + " SCORE:" + std::to_string(m_Score[i]) + "TIME:" + std::to_string(m_Time[i]);
		m_ScoreLabel.position.x = aqua::GetWindowWidth() / 2.0f - m_ScoreLabel.GetTextWidth() / 2.0f;
		m_ScoreLabel.position.y = m_score_label_position_result.y + (i * m_score_label_size_result);
		m_ScoreLabel.Draw();
	}
}

void CScoreManager::GamePlayDraw(void)
{
	m_ScoreLabel.Create(m_score_label_size_gameplay);
	m_ScoreLabel.position = m_score_label_position_gameplay;
	m_ScoreLabel.text = "SCORE:" + std::to_string(m_Score[m_StageNumber]) + "\nTIME:" + std::to_string(m_Time[m_StageNumber]);
	m_ScoreLabel.Draw();
}

void CScoreManager::ScoreManagerFinalize(void)
{
	m_ScoreLabel.Delete();
	AQUA_SAFE_DELETE(m_Score);
	AQUA_SAFE_DELETE(m_Time);
}

void CScoreManager::Finalize(void)
{
	//なにもしない
}

void CScoreManager::FinalizeScore(void)
{
	m_ScoreLabel.Delete();
	AQUA_SAFE_DELETE(m_Score);
	AQUA_SAFE_DELETE(m_Time);
	DeleteObject();
}

bool CScoreManager::GetClearFlag(void)const
{
	return m_ClearFlag;
}

void CScoreManager::InitializeScore(int max)
{
	m_Score = AQUA_NEW int[max];
	m_Time = AQUA_NEW int[max];
	m_MaxStage = max;
	for (int i = 0; i < m_MaxStage; i++)
	{
		m_Score[i] = 0;
		m_Time[i] = 0;
	}
}

void CScoreManager::SubtractScore(int score)
{
	m_Score[m_StageNumber] -= score;
	if (m_Score[m_StageNumber] < 0)
	{
		m_Score[m_StageNumber] = 0;
	}
}

void CScoreManager::AddScore(int score)
{
	m_Score[m_StageNumber] += score;
}

void CScoreManager::SetTime(int time)
{
	m_Time[m_StageNumber] = time;
}

void CScoreManager::SetStageNumber(int stage_number)
{
	m_StageNumber = stage_number;
}

void CScoreManager::SetClearFlag(bool flag)
{
	m_ClearFlag = flag;
}





