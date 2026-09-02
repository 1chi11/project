#pragma once
#include"..\effect.h"

class CEnemyEffect
	:public IEffect
{
public:
	CEnemyEffect(IGameObject* parent);
	~CEnemyEffect(void) = default;
	void    Initialize(const aqua::CVector2& position)override;
	void    Update(void) override;
	void    Draw(void) override;
private:
	static const float m_effect_timer;			//エフェクトタイマーのマックス値
	static const float m_scaling_speed;		//拡大縮小速度
	static const float m_size;						//サイズ
	static const float m_correction;			//拡大縮小速度のマイナス補正

	aqua::CTimer m_Timer;						//エフェクトタイマー
};