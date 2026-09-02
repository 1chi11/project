#pragma once
#include "../character.h"
//キャラクターの接触方向
enum class CHARACTER_HIT_DIRECTION
{
	NONE,  //接触していない
	UP,    //上から接触
	DOWN,  //下から接触
	LEFT,  //左から接触
	RIGHT, //右から接触
	SIDE,  //横から接触
	DUMMY, //ダミー
};

class CPlayer : public ICharacter
{
public:
	CPlayer(aqua::IGameObject* parent);
	~CPlayer(void) = default;
	void Initialize(const aqua::CVector2& position, const aqua::CVector2& travel_distance) override;
	void Draw(const aqua::CVector2& player_travel_distance) override;

	int GetDamage()const;
	//プレイヤーの状態に応じた処理
	void StateMove(void)override;
	//プレイヤーの接触方向を取得
	CHARACTER_HIT_DIRECTION GetHitDirection(const aqua::CVector2& character_position, const aqua::CVector2& character_size)const;
	//プレイヤーに対してのダメージ
	void Damage(int damage)override;
	//ゴール処理
	void Goal();
private:
	static const aqua::CVector2 m_texture_scale;		//プレイヤーのテクスチャのスケール
	static const float	m_run_speed;		//プレイヤーの走る速度
	static const float	m_gravity;			//プレイヤーの重力
	static const float	m_width;			//プレイヤーの幅
	static const float	m_height;			//プレイヤーの高
	static const float  m_overcome_size;	//プレイヤーが乗り越えるための余裕のサイズ
	static const float  m_i_frame_timer;	//プレイヤーの無敵時間
	static const float  m_draw_position;	//プレイヤーの表示位置
	static const int    m_die_score;			//プレイヤーの死亡時のスコア
	static const int	m_first_life_point;	//プレイヤーの初期体力
	static const int	m_damage;			//プレイヤーの与えるダメージ

	CHARACTER_HIT_DIRECTION m_HitDirection;    //キャラクターの接触方向
};