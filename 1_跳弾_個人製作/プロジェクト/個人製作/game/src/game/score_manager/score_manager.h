#pragma once
#include "aqua.h"

class CScoreManager
	: public aqua::IGameObject
{
public:
	CScoreManager(aqua::IGameObject* parent);
	~CScoreManager(void)=default;
	void SetScore(int score,int id);
	int GetScore(int id) ;
	int GetStageCount();
private:
	bool m_First;				//初回判定
	int    m_StageCount;	//ステージ数
	int    m_ThrowCount[10];	//各ステージの投げた回数
	
};
