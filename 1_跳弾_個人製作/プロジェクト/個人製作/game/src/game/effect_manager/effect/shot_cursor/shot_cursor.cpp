#include"shot_cursor.h"

CShotCursorEffect::CShotCursorEffect(IGameObject* parent)
	: IEffect(parent, "Shot_Cursor_Effect")
{
}

void CShotCursorEffect::Initialize(const aqua::CVector2& position)
{
	m_Beside_Line.Setup(aqua::CVector2(-25.0f, 0.0f)+position, aqua::CVector2(25.0f, 0.0f) + position,aqua::CColor::GREEN,5.0f);
	m_Vertical_Line.Setup(aqua::CVector2(0.0f, -25.0f) + position, aqua::CVector2(0.0f, 25.0f) + position, aqua::CColor::GREEN, 5.0f);
}

void CShotCursorEffect::Draw(void)
{
	m_Beside_Line.Draw();
	m_Vertical_Line.Draw();
}

