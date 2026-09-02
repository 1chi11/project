#pragma once
#include"..\effect.h"

class CBlockClash
	:public IEffect
{
public:
	CBlockClash(IGameObject* parent);
	~CBlockClash(void) = default;
	void Initialize(const aqua::CVector2& position)override;
	void Draw(const aqua::CVector2& travel_postion)override;
	void Update(void)override;
	void Finalize(void)override;
private:
	static const float m_effect_size;	//エフェクトのサイズ
	static const float m_glavity;		//重力
	static const float m_rotation;		//回転速度
	static const float m_speed;			//初速
	static const int m_angle_range;		//初速の角度範囲
	static const int m_add_angle_range;	//初速の角度範囲
	static const int m_effect_num;		//エフェクトの数
	aqua::CVector2* m_Velocity;			//エフェクトの速度
	aqua::CVector2* m_Position;			//エフェクトの位置
	aqua::CVector2 m_Size;				//エフェクトのサイズ
	float* m_Rotation;					//エフェクトの回転
};