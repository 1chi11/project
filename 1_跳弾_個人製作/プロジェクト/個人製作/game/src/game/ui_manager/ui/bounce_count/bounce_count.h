#pragma once
#include"..\ui.h"

class CBounceCount :public IUi
{
public:
	CBounceCount(aqua::IGameObject* parent);
	~CBounceCount() = default;
	void Initialize(aqua::CVector2 position) override;
	void Update()override;
	void Draw()override;
	//’µ‚Ë•Ô‚è”‚ÌXV
private:
	static const float m_size;	//UI‚Ì‘å‚«‚³

	aqua::CSprite m_One_Digit;	//’µ‚Ë•Ô‚è”‚Ì1‚ÌˆÊ
	aqua::CSprite m_Two_Digit;	//’µ‚Ë•Ô‚è”‚Ì10‚ÌˆÊ
};
