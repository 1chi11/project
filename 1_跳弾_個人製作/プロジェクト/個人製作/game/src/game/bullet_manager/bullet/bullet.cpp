#include "bullet.h"
#include "..\..\block_manager\block\block.h"
#include"..\..\effect_manager\effect_manager.h"
#include <game/sound_manager/sound_manager.h>

const float CBullet::m_bullet_size = 64.0f;

CBullet::CBullet(aqua::IGameObject* parent)
	:IGameObject(parent, "Ballet")
	, m_Position(0.0f, 0.0f)
	, m_Velocity(0.0f, 0.0f)
	, m_Radius(0.0f)
	, m_Angle(0.0f)
	, m_BounceCount(0)
	,m_Bounce(0.0f)
	,m_Active(true)
{
}

void CBullet::Initialize(const aqua::CVector2& position,int bounce)
{
	m_Speed =0.0f;
	m_Angle = 0.0f;
	m_BounceCount = bounce;

	m_Radius = m_bullet_size / 2.0f;
	m_Position = position;
	m_Velocity = aqua::CVector2(0.0f, 0.0f);

	m_Sprite.Create("data\\new_ball.png");
	m_Sprite.anchor = aqua::CVector2(m_Radius, m_Radius);

	//次の跳ね返りまでの時間を設定
	m_BounceTimer.Setup(0.05f);
	
}

void CBullet::Update()
{
	m_BounceTimer.Update();
	//跳ね返り確認
	BounceCheckHit();
	//壁当たり判定
 	WallCheckHit();

	//角度の正規化
	m_Angle = std::fmod(m_Angle, 360.0f);

	// 位置更新
	m_Rad = aqua::DegToRad(m_Angle);
	m_Velocity.x = cos(m_Rad) * m_Speed;
	m_Velocity.y = sin(m_Rad) * m_Speed;

	m_Position += m_Velocity;

}

void CBullet::Draw()
{
	m_Sprite.position = m_Position;
	m_Sprite.Draw();
}

void CBullet::Finalize()
{
	m_Sprite.Delete();
	DeleteObject();
}

void CBullet::WallCheckHit()
{
	//壁判定
	float w = (float)aqua::GetWindowWidth() - m_Sprite.GetTextureWidth();
	float h = (float)aqua::GetWindowHeight() - m_Sprite.GetTextureHeight();


	//左
	if (m_Position.x < 0.0f)
	{
		m_Position.x = 0.0f - m_Position.x;
		if (m_Angle < 180.0f)
		{
			m_Angle = 180.0f - m_Angle;
		}
		else
		{
			m_Angle = 360.0f - (m_Angle - 180.0f);
		}
	}
	//右
	if (m_Position.x > w)
	{
		m_Position.x = w - (m_Position.x - w);
		if (m_Angle < 270.0f)
		{
			m_Angle = 180.0f - m_Angle;
		}
		else
		{
			m_Angle = 180.0f + (360.0f - m_Angle);
		}
	}
	//上
	if (m_Position.y < 0.0f)
	{
		m_Position.y = 0.0f - m_Position.y;
		if (m_Angle < 270.0f)
		{
			m_Angle = 180.0f - (m_Angle - 180.0f);
		}
		else
		{
			m_Angle = 360.0f - m_Angle;
		}

	}
	//下
	if (m_Position.y > h)
	{

		m_Position.y = h - (m_Position.y - h);
		if (m_Angle < 90.0f)
		{
			m_Angle = 360.0f - m_Angle;
		}
		else
		{
			m_Angle = 180.0f + (180.0f - m_Angle);
		}
	}
}

void CBullet::BounceCheckHit()
{
	//跳ね返り
	if (m_Bounce != m_Angle)
	{
		CEffectManager* effect = (CEffectManager*)aqua::FindGameObject("EffectManager");
		effect->Create(EFFECT_ID::WALL_HIT_EFFECT, GetCenterPosition());
		m_BounceCount--;
		m_Bounce = m_Angle;
	}
		if (m_BounceCount <= 0)
		{
			m_Active = false;
		}
}



void CBullet::HitMove(IBlock* block)
{

	aqua::CVector2 object_position = block->GetCenterPosition();
	float object_size = block->GetSize();
	float object_angle = block->GetAngle();

	// オブジェクトからボールまでのベクトルを求めて
	// オブジェクト空間にローカライズ
	aqua::CVector2 v = GetCenterPosition() - object_position;

	//オブジェクトに対してのベクトルの角度を求める
	float angle = aqua::RadToDeg(atan2(v.y, v.x));
	float rad = aqua::DegToRad(angle);
	aqua::CVector2 vector;
	vector.x = cos(rad) ;
	vector.y = sin(rad) ;
	
	//オブジェクトの角度に応じてベクトルを回転させる
	vector = aqua::CVector2::RotationZ(vector, -aqua::DegToRad(object_angle));
	v = aqua::CVector2::RotationZ(v, -aqua::DegToRad(object_angle));

	//オブジェクトの角度に応じて加速度を回転させる
	aqua::CVector2 localized_velocity = aqua::CVector2::RotationZ(m_Velocity, -aqua::DegToRad(object_angle));

	//オブジェクトの当たり位置を求める
	aqua::CVector2 near_position = GetNearPosition(v,vector,object_angle,object_size);
	//跳ね返った後のVelocityの更新
	switch (block->GetDirectionLocal(near_position))
	{
	case BLOCK_DIRECTION::UP:

		//反射の処理
		localized_velocity.y *= -1.0f;

		break;
	case BLOCK_DIRECTION::DOWN:

		//反射の処理
		localized_velocity.y *= -1.0f;

		break;
	case BLOCK_DIRECTION::LEFT:

		//反射の処理
		localized_velocity.x *= -1.0f;

		break;
	case BLOCK_DIRECTION::RIGHT:

		//反射の処理
		localized_velocity.x *= -1.0f;

		break;
	case BLOCK_DIRECTION::UPPER_LEFT_CORNER:
		//反射の処理
		localized_velocity.x *= -1.0f;

		break;
	case BLOCK_DIRECTION::LOWER_LEFT_CORNER:
		//反射の処理
		localized_velocity.x *= -1.0f;


		break;
	case BLOCK_DIRECTION::UPPER_RIGHT_CORNER:

		//反射の処理
		localized_velocity.x *= -1.0f;

			break;
	case BLOCK_DIRECTION::LOWER_RIGHT_CORNER:
		//反射の処理
		localized_velocity.x *= -1.0f;

		break;
	case BLOCK_DIRECTION::NO_HIT:
		return;
		break;
	default:
		break;
	}
	//オブジェクトに埋まらない対策
	v = BackPosition(vector)+((m_Radius+5.0f)*vector);
	//角度に応じた加速度に変換
	m_Velocity = aqua::CVector2::RotationZ(localized_velocity, aqua::DegToRad(object_angle));
	//跳ね返った後の位置
	m_Position = object_position + aqua::CVector2::RotationZ(v, aqua::DegToRad(object_angle))-aqua::CVector2(m_Radius, m_Radius);
	//跳ね返った後の角度
	m_Angle = aqua::RadToDeg(atan2(m_Velocity.y, m_Velocity.x));
}

aqua::CVector2 CBullet::GetCenterPosition()
{
	return aqua::CVector2(m_Position.x + m_Radius, m_Position.y + m_Radius);
}

float CBullet::GetRadius()
{
	return m_Radius;
}

float CBullet::GetSize()
{
	return m_bullet_size;
}

void CBullet::Set_ShotStatus(aqua::CVector2 position, float angle, float speed)
{
	//弾のステータスをセット
	m_Position	= position;
	m_Speed		= speed;
	m_Angle		= angle;
	m_Bounce	= angle;
	//弾の発射効果音
	CSoundManager* sound = (CSoundManager*)aqua::FindGameObject("SoundManager");
	sound->Create(SOUND_ID::BALL_SHOT, false);

}

bool CBullet::GetActive()
{
	return m_Active;
}

int CBullet::GetBounceCount()
{
	return m_BounceCount;
}

aqua::CVector2 CBullet::BackPosition(aqua::CVector2 velocity)
{
	//接触する直前の位置を求める
	aqua::CVector2 local = { 0.0f,0.0f };
	float m_size = 120.0f;
	for (;;)
	{
		//ローカル座標がオブジェクトのサイズ内にあるか
		if (-m_size / 2.0f < local.x && local.x < m_size / 2.0f && -m_size / 2.0f < local.y && local.y < m_size / 2.0f)
		{
			local += velocity * 0.1f;
		}
		else
		{
			break;
		}
	}

	return local ;
}

aqua::CVector2 CBullet::GetNearPosition(aqua::CVector2 v,aqua::CVector2 velocity, float block_angle, float block_size)
{
	//veloctyの角度を求める
	float 	angle = aqua::RadToDeg(atan2(m_Velocity.y, m_Velocity.x));
	angle = std::fmod(angle, 360.0f);
	angle -= block_angle;
	//角度を0~360に変換
	if (angle < 0.0f)
	{
	angle += 360.0f;
	}

	aqua::CVector2 object_center = { 0.0f,0.0f };
	if (( -block_size / 2.0f <= v.x && v.x <= block_size / 2.0f)||(-block_size /2.0f<= v.y&& v.y<= block_size /2.0f))
	{
		return v;
	}

	//ballの右端か左端のどちらを参照すべきか
	//0~45
	if ((0.0f < angle && angle < 45.0f))
	{
		//オブジェクトがベクトルの上にあるか下にあるか
		if (object_center .y< v.y)
		{
			angle -= 90.0f;
		}
		else
		{
			angle += 90.0f;
		}
	}
	//45~90
	if ((45.0f <= angle && angle <= 90.0f))
	{
		//オブジェクトがベクトルの右にあるか左にあるか
		if (object_center.x < v.x)
		{
			angle += 90.0f;
		}
		else
		{
			angle -= 90.0f;
		}
	}else
	//90~135
	if ((90.0f < angle && angle < 135.0f))
	{
		if (object_center.x < v.x)
		{
			angle += 90.0f;
		}
		else
		{
			angle -= 90.0f;
		}
	}
	else
	//135~180
	if ((135.0f <= angle && angle <= 180.0f))
	{
		if (object_center.y < v.y)
		{
			angle += 90.0f;
		}
		else
		{
			angle -= 90.0f;
		}
	}
	else
	//180~225
	if ((180.0f < angle && angle < 225.0f))
	{
		if (object_center.y < v.y)
		{
			angle += 90.0f;
		}
		else
		{
			angle -= 90.0f;
		}
	}
	else
	//225~270
	if ((225.0f <= angle && angle <= 270.0f))
	{
		if (object_center.x < v.x)
		{
			angle -= 90.0f;
		}
		else
		{
			angle += 90.0f;
		}
	}
	else
	//270~315
	if ((270.0f < angle && angle < 315.0f))
	{
		if (object_center.x < v.x)
		{
			angle -= 90.0f;
		}
		else
		{
			angle += 90.0f;
		}
	}
	else
	//315~360
	if ((315.0f <= angle && angle <= 360.0f))
	{
		if (object_center.y < v.y)
		{
			angle -= 90.0f;
		}
		else
		{
			angle += 90.0f;
		}
	}

	//angleをベクトルに変換
	float rad = aqua::DegToRad(angle);
	aqua::CVector2 vector;
	vector.x = cos(rad);
	vector.y = sin(rad);

	//参照する位置を返す
	return v + (m_Radius * vector);
}

