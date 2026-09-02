#pragma once
#include"..\stage_gimmick.h"

class CFireGimmick : public IStageGimmick
{
	public:
	CFireGimmick(aqua::IGameObject* parent);
	~CFireGimmick(void) = default;
	void Initialize(const aqua::CVector2& position, const bool set_flag) override;
	void Update(void) override;
	void Draw(const aqua::CVector2& player_travel_distance) override;
	//プレイヤーとギミックに当たったときの処理
	void PlayerHit(void) override;
	//ブロックとギミックに当たったときの処理
	void ObjectHit(const aqua::CVector2& object_position, const aqua::CVector2& object_size) override;
private:
	static const aqua::CVector2 m_collsion_size;	//ギミックの当たり判定サイズ
	static const aqua::CVector2 m_texture_size;		//ギミックの描画サイズ
	static const aqua::CVector2 m_adjustment_position;		//ギミックの位置調整
	static const float m_injection_range;	//火の噴射の範囲
	static const int m_damage;	//ギミックのダメージ量
	aqua::CSprite m_FireBottomSprite;	//火の下側のスプライト
	aqua::CVector2 m_InjectionPosition;	//火の噴射の位置
	float m_LeftWidth;	//火の左側の幅
	float m_RightWidth;	//火の右側の幅
};