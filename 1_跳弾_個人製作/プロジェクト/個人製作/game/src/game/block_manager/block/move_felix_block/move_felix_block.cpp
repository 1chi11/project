#include"move_felix_block.h"

CMoveFelixBlock::CMoveFelixBlock(aqua::IGameObject* parent)
	:IBlock(parent,"MoveFelixBlock")
	, m_ReplaceDestination(false)
{
}

void CMoveFelixBlock::Initialize(aqua::CVector2 position1, aqua::CVector2 position2, float speed)
{
	m_CenterPosition = aqua::CVector2(m_size / 2.0f, m_size / 2.0f);
	m_Sprite.Create("data\\object.png");
	m_Sprite.anchor = aqua::CVector2(m_size / 2.0f, m_size / 2.0f);
	//固定オブジェクトにする(色変更)
	m_Sprite.color = 0xffffff00;

	m_Sprite.rotation = 0.0f;
	m_Vertices[0] = aqua::CVector2(0.0f, 0.0f);
	m_Vertices[1] = aqua::CVector2(m_size, 0.0f);
	m_Vertices[2] = aqua::CVector2(m_size, m_size);
	m_Vertices[3] = aqua::CVector2(0.0f, m_size);

	m_Position = position1;
	m_Speed = speed;
	float m_angle = aqua::RadToDeg(atan2(position1.y - position2.y, position1.x - position2.x));
	float m_rad = aqua::DegToRad(m_angle);
	m_Velocity.x = cos(m_rad) * m_Speed;
	m_Velocity.y = sin(m_rad) * m_Speed;
	if (abs(position1.x - position2.x) >= abs(position1.y - position2.y))
	{
		m_Timer.Setup(abs(position1.x - position2.x) / m_Speed);
	}
	else
		m_Timer.Setup(abs(position1.y - position2.y) / m_Speed);
	m_FELIX_BLOCK = FELIX_BLOCK_ID::FELIX_BLOCK;

}

void CMoveFelixBlock::Update(void)
{
	m_Timer.Update();
	if (m_ReplaceDestination)
	{
		m_Position += m_Velocity * aqua::GetDeltaTime();
	}
	else
		m_Position -= m_Velocity * aqua::GetDeltaTime();
	if (m_Timer.Finished() && !m_ReplaceDestination)
	{
		m_ReplaceDestination = true;
		m_Timer.Reset();
	}
	if (m_Timer.Finished() && m_ReplaceDestination)
	{
		m_ReplaceDestination = false;
		m_Timer.Reset();
	}

}

void CMoveFelixBlock::ResetMoving(void)
{
		m_Position = m_StartPos;
		m_ReplaceDestination = false;
}
