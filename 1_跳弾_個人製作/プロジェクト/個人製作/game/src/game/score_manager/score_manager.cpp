#include "score_manager.h"

CScoreManager::CScoreManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "ScoreManager")
	,m_First(false)
{
}



void CScoreManager::SetScore(int score, int id)
{
	if (!m_First)
	{
		//ステージが途中から始まったときのためにそれまでのステージスコアをリセット
		for (int i = 0;i < id+1;i++)
		{
			m_ThrowCount[i] = 0;
		}
		m_First = true;
	}
	//スコアの保存
	m_StageCount = id;
	m_ThrowCount[id] = score;
}

int CScoreManager::GetScore(int id)
{
	return m_ThrowCount[id];
}

int CScoreManager::GetStageCount()
{
	return m_StageCount;
}
