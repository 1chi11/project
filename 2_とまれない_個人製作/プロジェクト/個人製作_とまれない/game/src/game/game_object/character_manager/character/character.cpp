#include "character.h"
#include "..\character_manager.h"

const aqua::CVector2 ICharacter::m_overcome_size = aqua::CVector2{ 30.0f,30.0f };
const float ICharacter::m_gravity		= 0.5f;
const float ICharacter::m_i_frame_timer = 0.0f;
const float ICharacter::m_bounce_power = -12.0f;
const int	ICharacter::m_first_life_point = 30;
const int   ICharacter::m_damage = 1;
const int   ICharacter::m_damage_score = 100;
const int   ICharacter::m_die_score = 1000;


const std::string ICharacter::m_item_file_names[] =
{
	"data\\Dummy.png",
	"data\\Drill.png",
	"data\\Dummy.png",
};

ICharacter::ICharacter(aqua::IGameObject* parent, const std::string& name, const float run_speed, const float width, const float height, const int life_point, const float i_frame_timer)
	: aqua::IGameObject(parent,"ICharacter")
	, m_Position(0.0f, 0.0f)
	, m_Velocity(0.0f, 0.0f)
	, m_TextureSize(0.0f,0.0f)
	, m_TextureScale(1.0f, 1.0f)
	, m_LifePoint(life_point)
	, m_LandingFlg(false)
	, m_State(CHARACTER_STATE::STOP)
	, m_GameObjectId(GAME_OBJECT_ID::GROUND_ENEMY)
	, m_Size(width, height)
	, m_TravelDistance(0.0f, 0.0f)
	, m_RunSpeed(run_speed)
	, m_CharacterHaveItemObject(CHARACTER_HAVE_ITEM_OBJECT::NONE)
	, m_I_Frame_Time(i_frame_timer)
	, m_TimeSpeed(1.0f)
{
}

void ICharacter::Initialize(const aqua::CVector2& position, const aqua::CVector2& travel_distance)
{
	//アニメーションスプライトの作成
	m_Position = position;
	m_TravelDistance = travel_distance;
	m_AnimationSprite.Create("data\\enemy.ass");
	m_AnimationSprite.position = m_Position;
	m_AnimationSprite.scale = aqua::CVector2(1.0f, 1.0f);
	m_AnimationSprite.Change("stop_animation");
	//キャラクターの状態を走る状態にする
	m_State = CHARACTER_STATE::RUN;
	//キャラクターの体力を初期体力にする
	m_IFrameTimer.Setup(m_I_Frame_Time);

	m_Ncolor = 0xffffffff;
	m_Icolor = 0x55ffffff;
	m_TextureSize = aqua::CVector2(m_AnimationSprite.GetFrameWidth(), m_AnimationSprite.GetFrameHeight());
}

void ICharacter::Update(void)
{
	//キャラクターのアイテムオブジェクトの効果時間の処理
	ItemObjectTimerUpdate();
	//キャラクターの無敵時間の処理
	IFrameTimerUpdate();
	//キャラクターの状態に応じた処理
	StateMove();
	//重力の処理
	Gravity();
	//キャラクターのアニメーションの処理
	AnimationChange();
	//位置の確認
	PositionChecker();

	m_Velocity.x = m_RunSpeed;
}

void ICharacter::Draw(const aqua::CVector2& player_travel_distance)
{
	//キャラクターと所持アイテムの描画
	aqua::CVector2 draw_position = m_Position - player_travel_distance;
	aqua::CVector2 draw_item_position = m_Position - player_travel_distance + aqua::CVector2{ 0.0f,(float)-m_ItemSprite.GetTextureHeight() };
	if (m_AnimationSprite.scale.x < 0.0f)
	{
		draw_position.x = m_Position.x - player_travel_distance.x + m_TextureSize.x;
		draw_item_position.x = m_Position.x - player_travel_distance.x;
	}
	m_AnimationSprite.position = draw_position;
	m_AnimationSprite.Draw();
	if (!m_ItemObjectTimer.Finished())
	{
		m_ItemSprite.Draw();
	}
	m_ItemSprite.position = draw_item_position ;

}

void ICharacter::Finalize(void)
{
	m_CharacterHaveItemObject = CHARACTER_HAVE_ITEM_OBJECT::NONE;
	m_AnimationSprite.Delete();
	m_Sprite.Delete();
	DeleteObject();
}



void ICharacter::BackPosition(const aqua::CVector2& block_position)
{
	m_Position.y = block_position.y - m_Size.y;
}

void ICharacter::StateMove(void)
{
	if (m_Velocity.x == 0.0f)
	{
		m_State = CHARACTER_STATE::STOP;
	}
	else
	{
		m_State = CHARACTER_STATE::RUN;
	}

	//時間の速さを取得
	//時間の速さの倍率を取得

	aqua::CVector2 velocity = m_Velocity;
	//キャラクターの位置を更新
	m_Position.y += velocity.y * m_TimeSpeed;
	m_Position.x += velocity.x * m_TimeSpeed;

	if (velocity.x < 0)
	{
		m_AnimationSprite.scale = { m_TextureScale.x, m_TextureScale.y };
	}
	else
	{
		m_AnimationSprite.scale = { -m_TextureScale.x, m_TextureScale.y };
	}

}

aqua::CVector2 ICharacter::GetTravelDistance()const
{
	return m_TravelDistance;
}

aqua::CVector2 ICharacter::GetCenterPosition()const
{
	return aqua::CVector2(m_Position.x + m_Size.x / 2.0f, m_Position.y + m_Size.y / 2.0f);
}

aqua::CVector2 ICharacter::GetPosition(void)const
{
	return aqua::CVector2(m_Position.x + m_TextureSize.x / 2.0f - m_Size.x / 2.0f, m_Position.y);
}

float ICharacter::GetWidth()const
{
	return m_Size.x;
}

float ICharacter::GetHeight()const
{
	return m_Size.y;
}

float ICharacter::GetRunSpeed(void)const
{
	return m_RunSpeed;
}

float ICharacter::GetLifePoint(void)const
{
	return m_LifePoint;
}

float ICharacter::GetBouncePower(void)const
{
	return m_bounce_power;
}

int ICharacter::GetDamage(void)const
{
	return m_damage;
}

CHARACTER_HAVE_ITEM_OBJECT ICharacter::GetCharacterHaveItemObject(void)const
{
	return m_CharacterHaveItemObject;
}


aqua::CVector2 ICharacter::GetSize(void)const
{
	return	m_Size;
}

aqua::CVector2 ICharacter::GetOverComeSize(void)const
{
	return m_overcome_size;
}

GAME_OBJECT_ID ICharacter::GetGameObjectId(void)const
{
	return m_GameObjectId;
}

void ICharacter::SetTimeSpeed(const float rate)
{
	m_TimeSpeed = rate;
}


void ICharacter::Gravity(void)
{
	//時間の速さを取得
	//キャラクターが地面にいるかどうかで重力の処理を分ける
	if (m_LandingFlg)
	{
		m_Velocity.y = 0.0f;
	}
	else
	{
		m_Velocity.y += m_gravity * m_TimeSpeed;
		//キャラクターのY軸の速度が0より大きい場合は落下状態、そうでない場合は上昇状態にする
		if (m_Velocity.y > 0.0f)
		{
			m_State = CHARACTER_STATE::FALL;
		}
		else
		{
			m_State = CHARACTER_STATE::UP;
		}
	}
	m_LandingFlg = false;
}

void ICharacter::BlockHit(const aqua::CVector2& hit_position,const BLOCK_DIRECTION direction)
{
	aqua::CVector2 local_position = hit_position;
	if (m_GameObjectId == GAME_OBJECT_ID::PLAYER)
	{
		local_position -= GetTravelDistance();
	}
	//キャラクターがブロックの上にいない場合落下状態にする
	if (direction == BLOCK_DIRECTION::UP && m_State != CHARACTER_STATE::UP)
	{
		//ブロックに当たったときのキャラクターの位置を調整
		m_Position.y = local_position.y - m_Size.y;
		m_LandingFlg = true;
	}
	//ドリルを所持している場合は止まらない
	if (direction == BLOCK_DIRECTION::DOWN)
	{
		//ブロックに当たったときのキャラクターの位置を調整
		m_Position.y = local_position.y;
		m_Velocity.y = 0.0f;
	}
	if (direction == BLOCK_DIRECTION::LEFT)
	{
		m_Position.x = local_position.x - m_TextureSize.x / 2.0f - m_Size.x / 2.0f;
		m_State = CHARACTER_STATE::STOP;
		m_Velocity.x = 0.0f;
	}
	if (direction == BLOCK_DIRECTION::RIGHT)
	{
		m_Position.x = local_position.x;
	}
}

void ICharacter::Jump(const float power)
{
	m_LandingFlg = false;
	m_Velocity.y = power;
	CSoundPlayManager* sm = (CSoundPlayManager*)aqua::FindGameObject("SoundPlayManager");
	if (sm)
		sm->Play(SOUND_ID::JUMP);
}

void ICharacter::Damage(const int damage)
{
	//無敵時間
	if (m_IFrameTimer.Finished())
	{
		//ダメージ処理
		m_IFrameTimer.Reset();
		m_LifePoint -= damage;
		CSoundPlayManager* sm = (CSoundPlayManager*)aqua::FindGameObject("SoundPlayManager");
		if (sm)
			sm->Play(SOUND_ID::HIT);
		CEffectManager* em = (CEffectManager*)aqua::FindGameObject("EffectManager");
		if (em)
			em->Create(EFFECT_ID::CHARACTER_HIT_EFFECT,m_Position);
		CScoreManager* score_manager = (CScoreManager*)aqua::FindGameObject("ScoreManager");
		if (score_manager)
			score_manager->AddScore(m_damage_score);
		//ライフ０で死亡
		if(m_LifePoint <= 0)
		{
			score_manager->AddScore(m_die_score);
			Finalize();
		}
	}
	else
	{
		return;
	}
}

void ICharacter::PickUpItemObject(const CHARACTER_HAVE_ITEM_OBJECT item_object,const float time)
{
	m_CharacterHaveItemObject = CHARACTER_HAVE_ITEM_OBJECT::NONE;
	m_CharacterHaveItemObject = item_object;
	m_ItemObjectTimer.Setup(time);
	m_ItemSprite.Create(m_item_file_names[(int)item_object]);
	m_ItemSprite.position = m_Position + aqua::CVector2{ - m_TextureSize.x,(float) - m_ItemSprite.GetTextureHeight()};
}

void ICharacter::IFrameTimerUpdate(void)
{
	if (m_IFrameTimer.Finished())
	{
		//通常
		m_AnimationSprite.color = m_Ncolor;
	}
	else
	{
		//無敵
		m_AnimationSprite.color = m_Icolor;
		m_IFrameTimer.SetTimeScale(m_TimeSpeed);
		m_IFrameTimer.Update();
	}
}

void ICharacter::ItemObjectTimerUpdate(void)
{
	if (m_ItemObjectTimer.Finished())
	{
		m_CharacterHaveItemObject = CHARACTER_HAVE_ITEM_OBJECT::NONE;
	}
	else
	{
		m_ItemObjectTimer.SetTimeScale(m_TimeSpeed);
		m_ItemObjectTimer.Update();
	}
}

void ICharacter::AnimationChange(void)
{
	switch (m_State)
	{
	case ICharacter::CHARACTER_STATE::STOP:
		m_AnimationSprite.Change("stop_animation");
		break;
	case ICharacter::CHARACTER_STATE::RUN:
		m_AnimationSprite.Change("run_animation");
		break;
	case ICharacter::CHARACTER_STATE::UP:
		m_AnimationSprite.Change("jump_animation");
		break;
	case ICharacter::CHARACTER_STATE::FALL:
		m_AnimationSprite.Change("fall_animation");
		break;
	case ICharacter::CHARACTER_STATE::JUMP:
		m_AnimationSprite.Change("jump_animation");
		break;
	default:
		break;
	}
	//時間の流れに合わせてアニメーションの再生速度を変える
	m_AnimationSprite.SetPlayRate(m_TimeSpeed);
	//アニメーション更新
	m_AnimationSprite.Update();
}

void ICharacter::PositionChecker(void)
{
	if (m_Position.y > aqua::GetWindowHeight())
	{
		Finalize();
	}
}


