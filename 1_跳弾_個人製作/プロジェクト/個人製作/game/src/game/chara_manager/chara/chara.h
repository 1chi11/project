#pragma once
#include"aqua.h"
class CChara : public aqua::IGameObject
{
public:
	CChara(aqua::IGameObject* parent);
	~CChara() = default;
	void Initialize(const aqua::CVector2& position) ;
	void Draw(void) override;
	void Finalize(void) override;
	//キャラの中心点の取得
	aqua::CVector2 GetCenterPosition();	
	//当たった時の処理
	void Hit();	
	//キャラの半径の取得
	float GetRadius();	
private:
	static const float m_radius;	//キャラの半径
	aqua::CSprite m_Sprite;		//キャラのスプライト
	aqua::CVector2 m_Position;	//キャラの位置

	float m_Radius;	//半径
};
