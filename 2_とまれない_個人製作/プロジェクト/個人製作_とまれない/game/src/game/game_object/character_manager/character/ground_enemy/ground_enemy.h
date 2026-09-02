#pragma once
#include "..\character.h"

class CGroundEnemy : public ICharacter
{
	public:
		CGroundEnemy(aqua::IGameObject* parent);
		~CGroundEnemy(void) = default;
		void Initialize(const aqua::CVector2& position, const aqua::CVector2& travel_distance) override;
	private:
		static const aqua::CVector2 m_texture_scale;		//キャラクターのテクスチャのスケール
		static const aqua::CVector2 m_position_adjustment;		//キャラクターの位置調整
		static const float	m_width;			//キャラクターの幅
		static const float	m_height;			//キャラクターの高さ
		static const float	m_run_speed;		//地上の敵の走る速度
		static const int	m_first_life_point;	//地上の敵の重力
		static const float	m_i_frame_timer;	//地上の敵の無敵時間
		aqua::CSprite m_Sprite;            //地上の敵のスプライト
};