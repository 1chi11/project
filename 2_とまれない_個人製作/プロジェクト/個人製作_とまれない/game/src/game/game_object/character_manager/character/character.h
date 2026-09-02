#pragma once
#include "aqua.h"
#include "..\..\game_object_id.h"
#include "..\..\block_manager\block_manager.h"
#include "..\..\item_object_manager\item_object_manager.h"
#include "..\..\stage_gimmick_manager\stage_gimmick_manager.h"
#include"..\..\..\sound_play_manager\sound_play_manager.h"
#include"..\..\..\effect_manager\effect_manager.h"
#include"..\..\..\score_manager\score_manager.h"

enum class CHARACTER_HAVE_ITEM_OBJECT
{
	NONE,		//アイテムオブジェクトを所持していない状態
	DRILL,		//ドリル
	DUMMY,		//ダミー
};

class ICharacter : public aqua::IGameObject
{
	public:
		ICharacter(aqua::IGameObject* parent, const std::string& name, const float run_speed,const float width,const float height,const int life_point,const float i_frame_timer);
		~ICharacter(void) = default;
		virtual void Initialize(const aqua::CVector2& position, const aqua::CVector2& travel_distance);
		virtual void Update(void) override;
		virtual void Draw(const aqua::CVector2& player_travel_distance) ;
		virtual void Finalize(void) override;
		
		aqua::CVector2 GetTravelDistance(void)const;
		aqua::CVector2 GetCenterPosition(void)const;
		aqua::CVector2 GetPosition(void)const;
		aqua::CVector2 GetSize(void)const;
		aqua::CVector2 GetOverComeSize(void)const;
		float GetWidth(void)const;
		float GetHeight(void)const;
		float GetRunSpeed(void)const;
		float GetLifePoint(void)const;
		float GetBouncePower(void)const;
		int	GetDamage(void)const;
		CHARACTER_HAVE_ITEM_OBJECT GetCharacterHaveItemObject(void)const;
		GAME_OBJECT_ID GetGameObjectId(void)const;

		//時間の速さを入れる
		void SetTimeSpeed(const float rate);
		//キャラクターの位置をブロックの上に戻す
		void BackPosition(const aqua::CVector2& block_position);
		//キャラクターの状態に応じた処理
		virtual void StateMove(void);
		//重力の処理
		void Gravity(void);
		//キャラクターがブロックに当たったときの処理
		void BlockHit(const aqua::CVector2& hit_position, const BLOCK_DIRECTION direction);
		//キャラクターのジャンプの処理
		void Jump(const float power);
		//キャラクターがダメージを受けたときの処理
		virtual void Damage(const int damage);
		//キャラクターがアイテムオブジェクトを拾ったときの処理
		void PickUpItemObject(const CHARACTER_HAVE_ITEM_OBJECT item_object, const float time);
		//キャラクターの無敵時間の処理
		void IFrameTimerUpdate(void);
		//キャラクターのアイテムオブジェクトの効果時間の処理
		void ItemObjectTimerUpdate(void);
		//キャラクターのアニメーションの処理
		void AnimationChange(void);
		//位置の確認
		void PositionChecker(void);
	private:
		static const std::string    m_item_file_names[];   //サウンドファイルパス
		static const aqua::CVector2 m_overcome_size;//キャラクターの超えられる段差の高さ
		static const float	m_bounce_power;			//キャラクターの跳ねる力
		static const float	m_gravity;				//キャラクターの重力
		static const float  m_i_frame_timer;		//キャラクター無敵時間
		static const int	m_first_life_point;		//キャラクターの初期体力
		static const int	m_damage;				//ヒット時のダメージ
		static const int	m_damage_score;				//ヒット時のスコア
		static const int    m_die_score;				//死亡時のスコア

	protected:
		GAME_OBJECT_ID	m_GameObjectId;				//キャラクターのID
		aqua::CSprite	m_Sprite;					//キャラクターのスプライト
		aqua::CSprite	m_ItemSprite;				//キャラクターのスプライト
		aqua::CVector2	m_Position;					//キャラクターの位置
		aqua::CVector2  m_TextureSize;				//テクスチャのサイズ
		aqua::CVector2  m_Size;						//キャラクターのサイズ
		aqua::CVector2	m_Velocity;					//キャラクターの速度
		aqua::CVector2	m_TravelDistance;			//キャラクターの移動距離
		aqua::CVector2  m_TextureScale;				//テクスチャのスケール
		aqua::CAnimationSprite m_AnimationSprite;	//キャラクターのアニメーションスプライト
		aqua::CTimer	m_IFrameTimer;				//キャラクターの無敵時間タイマー
		aqua::CTimer    m_ItemObjectTimer;			//キャラクターのアイテムオブジェクトの効果時間タイマー
		aqua::CColor	m_Ncolor;			//通常時の色
		aqua::CColor	m_Icolor;			//無敵時の色
		float	m_I_Frame_Time;				//キャラクターの無敵時間
		float	m_RunSpeed;					//キャラクターの走る速度
		float	m_TimeSpeed;				//時間の速さ
		int		m_LifePoint;				//キャラクターの体力
		bool	m_LandingFlg;				//キャラクターが地面にいるかどうか

		//キャラクターの状態
		enum class CHARACTER_STATE
		{
			STOP,		//停止状態
			RUN,		//走る状態
			UP,			//上昇状態
			FALL,		//落下状態
			JUMP,		//ジャンプ状態
			DUMMY,		//ダミー
		};

		CHARACTER_HAVE_ITEM_OBJECT m_CharacterHaveItemObject;    //キャラクターが所持しているアイテムオブジェクト

		CHARACTER_STATE	m_State;        //キャラクターの状態

};