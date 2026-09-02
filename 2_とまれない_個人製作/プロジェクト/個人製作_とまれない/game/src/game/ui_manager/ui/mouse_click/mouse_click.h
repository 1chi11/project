#pragma once
#include"..\ui.h"

class CMouseClick :public IUi
{
public:
	CMouseClick(aqua::IGameObject* parent);
	~CMouseClick(void) = default;
	void Initialize(aqua::CVector2 position)override;
	void Draw(void)override;
	void Finalize(void)override;
private:
	static const float m_width;	//幅
	aqua::CSprite m_Sprite;	//スプライト
};