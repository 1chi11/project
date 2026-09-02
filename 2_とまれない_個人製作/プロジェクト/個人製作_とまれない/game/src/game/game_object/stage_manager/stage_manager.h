#pragma once
#include "aqua.h"

class CStage :
	public aqua::IGameObject
{
public:
	CStage(aqua::IGameObject* parent);
	~CStage(void) = default;
	void Initialize(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Finalize(void) override;
private:
	static const int m_scroll;
	aqua::CSprite m_Sprite;
	aqua::CVector2* m_Position;
};