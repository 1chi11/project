#pragma once
#include"..\..\item_object\item_object.h"

class CTrampoline: public IItemObject
{
public:
	CTrampoline(aqua::IGameObject* parent);
	~CTrampoline(void) = default;	
	void Initialize(const aqua::CVector2& position,const bool set_flag) override;
	void Draw(const aqua::CVector2& player_travel_distance) override;
	void Finalize(void)override;
	void Hit(ICharacter*& character) override;
private:
	static const float m_width;			//トランポリンの幅
	static const float m_height;		//トランポリンの高さ
	static const float m_gravity;		//トランポリンのガイドの重力
	static const float m_bounce_power;	//トランポリンの跳ねる力
	static const int m_max_guide;		//ガイドの数
	aqua::CSprite m_GuideSprite;		//トランポリンのガイドスプライト
	aqua::CVector2* m_GuidePoint;		//トランポリンのガイドポイント
	int m_GuidePointInterval;			//トランポリンのガイドポイントの間隔
};