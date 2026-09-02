#pragma once
#include"..\effect.h"

class CShotCursorEffect
	:public IEffect
{
public:
	CShotCursorEffect(IGameObject* parent);
	~CShotCursorEffect(void) = default;
	void    Initialize(const aqua::CVector2& position)override;
	void    Draw(void) override;
private:
	aqua::CLinePrimitive m_Vertical_Line;				//ècê¸
	aqua::CLinePrimitive m_Beside_Line;				//â°ê¸
};