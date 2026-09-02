#pragma once
#include"..\stage_gimmick.h"

class CSpikeGimmick : public IStageGimmick
{
public:
	CSpikeGimmick(aqua::IGameObject* parent);
	~CSpikeGimmick(void) = default;
	void Initialize(const aqua::CVector2& position, const bool set_flag) override;
	void PlayerHit(void) override;
private:
	static const aqua::CVector2 m_collsion_size;	//ギミックの当たり判定サイズ
	static const aqua::CVector2 m_texture_size;		//ギミックの描画サイズ
	static const int m_damage;			//ギミックのダメージ量
	static const float m_height_adj;	//ギミックの高さの調整値
}
;