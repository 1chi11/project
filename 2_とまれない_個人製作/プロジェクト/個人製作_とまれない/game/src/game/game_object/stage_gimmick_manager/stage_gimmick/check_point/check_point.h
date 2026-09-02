#pragma once
#include "..\stage_gimmick.h"

class CCheckPoint : public IStageGimmick
{
public:
	CCheckPoint(aqua::IGameObject* parent);
	~CCheckPoint(void) = default;
	void Initialize(const aqua::CVector2& position, const bool set_flag) override;
	void PlayerHit(void) override;
private:
	static const aqua::CVector2 m_collsion_size;	//ギミックの当たり判定サイズ
	static const aqua::CVector2 m_texture_size;		//ギミックの描画サイズ
	static const int m_damage;	//ギミックのダメージ量
	static const int m_score;	//ギミックのスコア量
	bool m_FirstHit;			//最初に接触
};