#pragma once
#include"..\block.h"

class CMoveFelixBlock :public IBlock
{
public:
	CMoveFelixBlock(aqua::IGameObject* parent);
	~CMoveFelixBlock(void) = default;
	void Initialize(aqua::CVector2 position1, aqua::CVector2 position2, float speed);
	void Update(void)override;
	//動くブロックを初期位置に戻す
	void ResetMoving(void);
private:
	aqua::CVector2	m_StartPos;		//開始位置
	aqua::CVector2	m_Velocity;		//移動のベクトル
	bool m_ReplaceDestination;		//ポイント１とポイント２を行き来するためのフラグ
	aqua::CTimer		m_Timer;	//移動の往復タイマー
	float				m_Speed;		//移動速度
};