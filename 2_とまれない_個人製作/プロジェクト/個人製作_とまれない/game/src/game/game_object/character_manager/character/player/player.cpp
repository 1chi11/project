#include "player.h"
#include"..\..\character_manager.h"
#include"..\..\..\..\ui_manager\ui\life_point\life_point.h"
#include"..\..\..\..\scene_manager\scene\game_main_scene\game_main_scene.h"

const aqua::CVector2 CPlayer::m_texture_scale = aqua::CVector2(1.0f, 0.7f);
const float CPlayer::m_run_speed = 5.0f;
const float CPlayer::m_width = 90.0f;
const float CPlayer::m_height = 145.0f;
const float CPlayer::m_overcome_size = 20.0f;
const float CPlayer::m_i_frame_timer = 1.0f;
const float CPlayer::m_draw_position = 300.0f;
const int CPlayer::m_first_life_point = 3;
const int CPlayer::m_damage = 5;
const int CPlayer::m_die_score = 1000;

CPlayer::CPlayer(aqua::IGameObject* parent)
	: ICharacter(parent,"Player", m_run_speed, m_width, m_height, m_first_life_point, m_i_frame_timer)
	, m_HitDirection(CHARACTER_HIT_DIRECTION::NONE)
{
}

void CPlayer::Initialize(const aqua::CVector2& position, const aqua::CVector2& travel_distance)
{
	//アニメーションスプライトの作成
	m_Position = position;
	m_TravelDistance = travel_distance;
	m_AnimationSprite.Create("data\\player.ass");
	m_AnimationSprite.position = m_Position;
	m_AnimationSprite.Change("stop_animation");
	m_AnimationSprite.scale = m_texture_scale;
	m_TextureScale = m_texture_scale;
	m_TextureSize = aqua::CVector2(m_AnimationSprite.GetFrameWidth(), m_AnimationSprite.GetFrameHeight());

	//プレイヤーの体力を初期体力にする
	m_GameObjectId = GAME_OBJECT_ID::PLAYER;
	m_IFrameTimer.Setup(m_I_Frame_Time);

	m_Ncolor = 0xffffffff;
	m_Icolor = 0x55ffffff;

	//Uiの更新
	CLifePoint* lp= (CLifePoint*)aqua::FindGameObject("LifePoint");
	if (lp);
	lp->SetLifePoint(m_LifePoint);
}


void CPlayer::Draw(const aqua::CVector2& player_travel_distance)
{
	//キャラクターと所持アイテムの描画
	aqua::CVector2 draw_position = m_Position;
	aqua::CVector2 draw_item_position = m_Position + aqua::CVector2{ -m_TextureSize.x,(float)-m_ItemSprite.GetTextureHeight() };
	draw_item_position.x = m_Position.x + m_TextureSize.x/2.0;

	m_AnimationSprite.position = draw_position;
	m_AnimationSprite.Draw();
	if (!m_ItemObjectTimer.Finished())
	{
		m_ItemSprite.Draw();
	}
	m_ItemSprite.position = draw_item_position;
}

int CPlayer::GetDamage()const
{
	return m_damage;
}

void CPlayer::StateMove(void)
{
	if (m_Velocity.y == 0.0f)
	{
		if (m_Velocity.x == 0.0f)
		{
			m_State = CHARACTER_STATE::STOP;
		}
		else
		{
			m_State = CHARACTER_STATE::RUN;
		}
	}

	//時間の速さを取得
	//時間の速さの倍率を取得

	aqua::CVector2 velocity = m_Velocity;

	//プレイヤーの位置を更新
	m_Position.y += velocity.y * m_TimeSpeed;

	if (m_Position.x < m_draw_position)
	{
		m_Position.x += velocity.x * m_TimeSpeed;
	}
	else
	{
		m_TravelDistance.x += velocity.x * m_TimeSpeed;
	}
}

CHARACTER_HIT_DIRECTION CPlayer::GetHitDirection(const aqua::CVector2& character_position, const aqua::CVector2& character_size)const{
	//プレイヤーの上にキャラクターがいる場合は上から接触、下にいる場合は下から接触、そうでない場合は横から接触とする
	if (character_position.y + m_overcome_size >= m_Position.y+ m_Size.y)
	{
		return CHARACTER_HIT_DIRECTION::UP;
	}
	else if (character_position.y+ character_size.y-m_overcome_size <= m_Position.y )
	{
		return CHARACTER_HIT_DIRECTION::DOWN;
	}
	else
	{
		return CHARACTER_HIT_DIRECTION::SIDE;
	}
}



void CPlayer::Damage(int damage)
{
	//無敵時間の確認
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
			em->Create(EFFECT_ID::CHARACTER_HIT_EFFECT,m_Position+GetTravelDistance());

		if (m_LifePoint <= 0)
		{
			CScoreManager* score = (CScoreManager*)aqua::FindGameObject("ScoreManager");
			if (score)
				score->SubtractScore(m_die_score);
			Finalize();
		}
	}
	else
	{
		return;
	}

	//Uiの更新
	CLifePoint* lp = (CLifePoint*)aqua::FindGameObject("LifePoint");
	if (lp);
	lp->SetLifePoint(m_LifePoint);
}

void CPlayer::Goal()
{
	CGameMainScene* gamemain_scene = (CGameMainScene*)aqua::FindGameObject("GameMainScene");
	if (gamemain_scene)
		gamemain_scene->Goal();
}



