#pragma once
#include"..\effect.h"

class CWallEffect
	:public IEffect
{
public:
	CWallEffect(IGameObject* parent);
	~CWallEffect(void) = default;
	void    Initialize(const aqua::CVector2& position)override;
	void    Draw(void) override;
private:
	static const float m_effect_size;	//エフェクトのサイズ
};