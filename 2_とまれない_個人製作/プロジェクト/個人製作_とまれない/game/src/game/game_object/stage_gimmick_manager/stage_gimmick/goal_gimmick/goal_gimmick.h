#pragma once
#include "..\stage_gimmick.h"

class CGoalGimmick : public IStageGimmick
{
	public:
	CGoalGimmick(aqua::IGameObject* parent);
	~CGoalGimmick(void) = default;
	void Initialize(const aqua::CVector2& position, const bool set_flag) override;
	void PlayerHit(void) override;
private:
	static const int m_damage;	//ギミックのダメージ量
	static const int m_score;	//ギミックのスコア量
	static const aqua::CVector2 m_collsion_size;	//ギミックの当たり判定サイズ
	static const aqua::CVector2 m_texture_size;		//ギミックの描画サイズ

};