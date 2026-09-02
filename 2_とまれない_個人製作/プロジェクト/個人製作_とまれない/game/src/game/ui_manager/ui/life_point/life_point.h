#pragma once
#include"..\ui.h"

class CLifePoint :public IUi
{
public:
	CLifePoint(aqua::IGameObject* parent);
	~CLifePoint(void) = default;
	void Initialize(aqua::CVector2 position)override;
	void Draw(void)override;
	void Finalize(void)override;
	//ライフの表示
	void SetLifePoint(int life);
private:
	static const float m_width;	//幅
	aqua::CSprite* m_Sprite;	//スプライト
	aqua::CVector2 m_Position;	//位置
	int m_Max;					//ライフの最大
};