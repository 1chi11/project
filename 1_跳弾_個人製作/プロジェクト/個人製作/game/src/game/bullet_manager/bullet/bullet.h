#pragma once
#include"aqua.h"
#include"..\..\block_manager\block\block_direction.h"

class IBlock;

//ボールクラス
class CBullet :public aqua::IGameObject
{
public:
	CBullet(aqua::IGameObject* parent);
	~CBullet() = default;
	void Initialize(const aqua::CVector2& position,int bounce);
	void Update()override;
	void Draw()override;
	void Finalize()override;
	//壁判定
	void WallCheckHit();		
	//跳ね返ったかの確認
	void BounceCheckHit();	
	//跳ね返った後の動作
	void HitMove(IBlock* block);
	//中心点の取得
	aqua::CVector2 GetCenterPosition();		
	//半径の取得
	float GetRadius();	
	//サイズの取得
	float GetSize();
	//弾のステータスをセット
	void Set_ShotStatus( aqua::CVector2 positon,float angle, float speed);
	//アクティブフラグの取得
	bool GetActive();				
	//跳ね返り回数の取得
	int GetBounceCount();
	//オブジェクトにめり込み対策
	aqua::CVector2 BackPosition(aqua::CVector2 velocity);
	//オブジェクトに接触したときの参照すべき位置を取得
	aqua::CVector2 GetNearPosition(aqua::CVector2 ballet_pos, aqua::CVector2 velocity,float block_angle,float block_size);
private:
	static const float	m_bullet_size;				//弾の大きさ
	static const float	m_bounce_count;	//跳ね返る限界回数

	aqua::CSprite		m_Sprite;							//弾のスプライト
	aqua::CVector2	m_Position;						//弾の位置
	aqua::CVector2	m_Velocity;						//加速度
	aqua::CTimer		m_BounceTimer;				//次のバウンドまでのタイマー

	float m_Angle;		//弾の飛ぶアングル			
	float m_Radius;	//弾の半径
	float m_Speed;		//弾のスピード
	float m_Rad;			//弾の飛ぶラジアル
	bool m_Active;		//アクティブフラグ


	float m_Bounce;			//跳ね返る角度
	int m_BounceCount;	//跳ね返る限界回数
};