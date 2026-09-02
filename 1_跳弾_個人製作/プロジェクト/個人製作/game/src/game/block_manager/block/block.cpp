#include <iostream>
#include <cmath>
#include <algorithm> // std::max, std::min を使用するために必要
#define NOMINMAX
#include<Windows.h>
#include "block.h"
#include"..\..\bullet_manager\bullet_manager.h"
#include <game/sound_manager/sound_manager.h>
const float IBlock::m_size = 120.0f;
const float IBlock::m_thickness = 5.0f;
const float IBlock::m_max_up_corner = 1.1776f;
const float IBlock::m_min_up_corner = 1.1774f;
const float IBlock::m_max_down_corner = 0.3926f;
const float IBlock::m_min_down_corner = 0.3924f;
const float IBlock::m_vertical_horizontal = 1.57f;
const float IBlock::m_moving_range_area = 100.0f;


IBlock::IBlock(aqua::IGameObject* parent, const std::string& object_name)
	:aqua::IGameObject(parent, "Block")
	, m_Position(0.0f,0.0f)
	, m_Rect(0, 0, m_size, m_size)
	, m_Direction(BLOCK_DIRECTION::NO_HIT)
	, m_Angle(0.0f)
	, m_CenterPosition(0.0f,0.0f)
	, m_MousePos(0, 0)
	, m_Vertices()
	,m_FELIX_BLOCK(FELIX_BLOCK_ID::FELIX_BLOCK)
	, m_SetSw(false)
{
}

void IBlock::Initialize(aqua::CVector2 position1, aqua::CVector2 position2, float speed)
{
	m_CenterPosition = aqua::CVector2(m_size / 2.0f, m_size / 2.0f);
	m_Sprite.Create("data\\object.png");
	m_Sprite.anchor = aqua::CVector2(m_size / 2.0f, m_size / 2.0f);
	m_Sprite.color = 0xffffff00;

	m_Sprite.rotation = 0.0f;
	m_Vertices[0] = aqua::CVector2(0.0f, 0.0f);
	m_Vertices[1] = aqua::CVector2(m_size, 0.0f);
	m_Vertices[2] = aqua::CVector2(m_size, m_size);
	m_Vertices[3] = aqua::CVector2(0.0f, m_size);

	m_Position = position1;
	float m_angle= aqua::RadToDeg(atan2(position1.y- position2.y, position1.x- position2.x));
	float m_rad = aqua::DegToRad(m_angle);
}

void IBlock::Update()
{
	//角度のリセット
		m_Angle = std::fmod(m_Angle, 360.0f);
		m_Sprite.rotation =std::fmod(m_Sprite.rotation, aqua::DegToRad(360.0f));
}

void IBlock::Draw()
{
	m_Sprite.position = m_Position;
	m_Sprite.Draw();
}

void IBlock::Finalize()
{
	m_Sprite.Delete();
	DeleteObject();
}

BLOCK_DIRECTION IBlock::GetDirectionLocal(aqua::CVector2 v)
{
	// オブジェクトの対角線とボールまでのベクトルとの内積を求める
	float dot = aqua::CVector2::Dot(v.Normalize(), aqua::CVector2(m_size, m_size).Normalize());
	float angle = acos(dot);
	float cross = aqua::CVector2::Cross(v, aqua::CVector2(m_size, m_size));

	// 内積の符号でどちら側にあるかを判定 (上右or下左)
	if (cross > 0.0f)
	{
		//上右
		if (angle > m_vertical_horizontal)
		{
			 return m_Direction = BLOCK_DIRECTION::UP;
		}
		else
		{
			if (m_max_up_corner > angle && angle > m_min_up_corner)
			{
				return m_Direction = BLOCK_DIRECTION::UPPER_RIGHT_CORNER;
			}
			else if (m_max_down_corner > angle && angle > m_min_down_corner)
				{
					return m_Direction = BLOCK_DIRECTION::LOWER_RIGHT_CORNER;
				}
				else
				{
					return m_Direction = BLOCK_DIRECTION::RIGHT;
				}
		}
	}
	else
	{
		//下左
		if (angle > m_vertical_horizontal)
		{
			return m_Direction = BLOCK_DIRECTION::LEFT;
		}
		else
		{
			if (m_max_up_corner > angle && angle > m_min_up_corner)
			{
				return m_Direction = BLOCK_DIRECTION::UPPER_LEFT_CORNER;
			}
			else if (m_max_down_corner > angle && angle > m_min_down_corner)
			{
					return m_Direction = BLOCK_DIRECTION::LOWER_LEFT_CORNER;
				}
				else
				{
					return m_Direction = BLOCK_DIRECTION::DOWN;
				}
		}
	}	
}

FELIX_BLOCK_ID IBlock::GetFelixBlock()
{
	return m_FELIX_BLOCK;
}

aqua::CVector2 IBlock::GetCenterPosition()
{
	return aqua::CVector2(m_Position.x + m_size / 2.0f, m_Position.y + m_size / 2.0f);
}

float IBlock::GetAngle()
{
	return m_Angle;
}

float IBlock::GetSize()
{
	return m_size;
}




// 回転行列で座標を変換
aqua::CVector2 IBlock::RotatePoint(const aqua::CVector2& point, const aqua::CVector2& center)
{
	float rad = aqua::DegToRad(m_Angle);
	// 円の中心を矩形のローカル座標に変換
	float s = std::sin(-rad);
	float c = std::cos(-rad);
	aqua::CVector2 p = point - center;
	return aqua::CVector2(
		p.x * c - p.y * s,
		p.x * s + p.y * c
	) + center;
}

void IBlock::GetRectVertices(aqua::CVector2 verts[4])
{
	float hw = m_size / 2.0f;
	float hh = m_size / 2.0f;
	aqua::CVector2 local[4] = {
		aqua::CVector2(-hw, -hh),
		aqua::CVector2(hw, -hh),
		aqua::CVector2(hw, hh),
		aqua::CVector2(-hw, hh)
	};

	//角の座標を回転させて取得
	for (int i = 0; i < 4; ++i)
	{
		verts[i] = RotatePoint(GetCenterPosition() + local[i], GetCenterPosition());
	}
}

bool IBlock::HitCircleRotatedRect(const aqua::CVector2& ballet_center, float radius)
{
	float rad = aqua::DegToRad(m_Angle);
	// 円の中心を矩形のローカル座標に変換
#if 0
	float s = std::sin(-rad);
	float c = std::cos(-rad);
	aqua::CVector2 rel = ballet_center - GetCenterPosition();
	aqua::CVector2 local(
		rel.x * c - rel.y * s,
		rel.x * s + rel.y * c
	);
#else
	//逆回転して座標を変換
	aqua::CVector2 local = aqua::CVector2::RotationZ(ballet_center - GetCenterPosition(), -rad);
#endif

	// 軸に沿った判定
	float hw = m_size / 2.0f;
	float hh = m_size / 2.0f;
	float closestX = std::max(-hw, std::min(local.x, hw));
	float closestY = std::max(-hh, std::min(local.y, hh));
	float dx = local.x - closestX;
	float dy = local.y - closestY;
	return (dx * dx + dy * dy) <= (radius * radius);
}

void IBlock::SetBlock(bool sw)
{
	m_SetSw = sw;
}


void IBlock::MoveBlock(aqua::CPoint point)
{
	//弾を押し出さない対策
	m_MousePos = point;
	aqua::CVector2 mouse_v = aqua::CVector2((float)m_MousePos.x - m_size / 2.0f, (float)m_MousePos.y - m_size / 2.0f);
	bool sw = true;
	CBulletManager* bullet =
		(CBulletManager*)aqua::FindGameObject("BulletManager");
	if (!bullet)return;
	aqua::CVector2 v = mouse_v - (bullet->GetCenterPosition() + aqua::CVector2(-bullet->GetSize(), -bullet->GetSize()));
	if (v.Length() < m_moving_range_area + bullet->GetRadius())
		sw = false;

	//オブジェクトの位置
	if (m_SetSw && sw)
	{
		m_Position = mouse_v;
	}

}

void IBlock::SpinBlock(int spin)
{
	//回転処理
	if (m_SetSw)
	{
		CSoundManager* sound = (CSoundManager*)aqua::FindGameObject("SoundManager");
		sound->Create(SOUND_ID::BLOCK_ROATATE, false);

		m_Sprite.rotation += aqua::DegToRad((float)spin);
		m_Angle += (float)spin;
	}

}
