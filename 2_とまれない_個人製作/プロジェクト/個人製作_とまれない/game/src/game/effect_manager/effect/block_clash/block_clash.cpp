#include "block_clash.h"
const float CBlockClash::m_effect_size = 75.0f;
const float CBlockClash::m_glavity = 0.5f;
const float CBlockClash::m_rotation = 0.1f;
const float CBlockClash::m_speed = 10.0f;
const int CBlockClash::m_effect_num = 4;
const int CBlockClash::m_angle_range = 30;
const int CBlockClash::m_add_angle_range = 60;

CBlockClash::CBlockClash(IGameObject* parent)
	: IEffect(parent, "BlockClash")
{
}

void CBlockClash::Initialize(const aqua::CVector2& position)
{
	m_Position = AQUA_NEW aqua::CVector2[m_effect_num];
	m_Velocity = AQUA_NEW aqua::CVector2[m_effect_num];
	m_Rotation = AQUA_NEW float[m_effect_num];
	//初速の角度をランダムに決定
	int angle;
	float* radian = AQUA_NEW float[m_effect_num];
	for (int i = 0;i < m_effect_num;i++)
	{
		angle = (float)(rand() % m_angle_range)+ m_add_angle_range;
		radian[i] = aqua::DegToRad((float)angle);
		m_Velocity[i] = aqua::CVector2{ std::cos(radian[i]) * m_speed,-std::sin(radian[i]) * m_speed };
	}
	
	m_Position[0] = position;
	m_Position[1] = position + aqua::CVector2{ m_effect_size,0.0f };
	m_Position[2] = position + aqua::CVector2{ 0.0f ,m_effect_size };
	m_Position[3] = position + aqua::CVector2{ m_effect_size ,m_effect_size };
	m_Rotation[0] = 0.0f;
	m_Rotation[1] = 0.0f;

	m_Sprite.Create("data\\block.png");
	m_Sprite.scale = { 0.5f, 0.5f };
	m_Sprite.position = position;
	m_Sprite.anchor = { m_Sprite.GetTextureWidth() / 2.0f,m_Sprite.GetTextureHeight() / 2.0f };
}

void CBlockClash::Draw(const aqua::CVector2& travel_postion)
{
	for (int i = 0;i < m_effect_num;i++)
	{
		if (i % 2)
		{
			m_Sprite.rotation = m_Rotation[1];
		}
		else
		{
			m_Sprite.rotation = m_Rotation[0];
		}
		m_Sprite.position = m_Position[i] - travel_postion;
		m_Sprite.Draw();

	}
}

void CBlockClash::Update()
{
	//位置更新
	for (int i = 0;i < m_effect_num;i++)
	{
		m_Position[i] += m_Velocity[i] * m_TimeSpeed;
	}
	for (int i = 0;i < m_effect_num;i++)
	{
		m_Velocity[i].y += m_glavity * m_TimeSpeed;
	}
	//回転の更新
	m_Rotation[0] += m_rotation * m_TimeSpeed;
	m_Rotation[1] -= m_rotation * m_TimeSpeed;

	//すべてのエフェクトが画面外にいったら解放
	for (int i = 0;i < m_effect_num;i++)
	{
		if (m_Position[i].y > aqua::GetWindowHeight())
		{

		}
		else
		{
			return;
		}
	}
	Finalize();
}

void CBlockClash::Finalize(void)
{
	AQUA_SAFE_DELETE(m_Position);
	AQUA_SAFE_DELETE(m_Velocity);
	AQUA_SAFE_DELETE(m_Rotation);
	m_Sprite.Delete();
	DeleteObject();
}



