#pragma once
#include"aqua.h"
#include"block_direction.h"
enum class FELIX_BLOCK_ID
{
	NOMAL_BLOCK,
	FELIX_BLOCK,
};
class IBlock :public aqua::IGameObject
{
public:
	IBlock(aqua::IGameObject* parent, const std::string& object_name);
	~IBlock(void) = default;

	//ブロックの初期化
virtual	void Initialize(aqua::CVector2 position1, aqua::CVector2 position2,float speed);	
	
	void Update(void)override;
	
	void Draw(void)override;
	
	void Finalize(void)override;
	//弾の当たった方向の取得
	BLOCK_DIRECTION GetDirectionLocal(aqua::CVector2 position);
	FELIX_BLOCK_ID GetFelixBlock();
	//回転行列で座標を変換
	aqua::CVector2 RotatePoint(const aqua::CVector2& point, const aqua::CVector2& center);		
	//矩形の頂点座標取得
	void GetRectVertices(aqua::CVector2 verts[4]);												
	//回転矩形と円の当たり判定
	bool HitCircleRotatedRect(const aqua::CVector2& ballet_center, float radius);			

	//ブロックの中心座標取得
	aqua::CVector2 GetCenterPosition(void);		
	//回転角度取得
	float GetAngle(void);	
	//サイズの取得
	float GetSize(void);	
	//ブロックの所持
	void SetBlock(bool sw);
	//ブロックの移動
	void MoveBlock(aqua::CPoint point);
	//ブロックの回転
	void SpinBlock(int spin);

protected:
	static const float m_size;								//ブロックの大きさ
	static const float m_thickness;						//当たり判定の厚さ
	static const float m_max_up_corner;			//上角の判定用（最大値）
	static const float m_min_up_corner;			//上角の判定用（最小値）
	static const float m_max_down_corner;		//下角の判定用（最大値）
	static const float m_min_down_corner;		//下角の判定用（最小値）
	static const float m_vertical_horizontal;		//縦横の判定
	static const float m_moving_range_area;	//ブロックの置ける範囲


	aqua::CSprite m_Sprite;			//ブロックのスプライト
	aqua::CVector2 m_Position;		//ブロックの位置
	aqua::CPoint m_MousePos;		//マウスの位置
	aqua::CRect m_Rect;				//ブロックの矩形情報

	aqua::CVector2 m_CenterPosition;//ブロックの中心座標
	aqua::CVector2 m_Vertices[4];	//矩形の頂点座標

	float m_Angle;					//回転角度

	BLOCK_DIRECTION m_Direction;	//接触した方向
	FELIX_BLOCK_ID m_FELIX_BLOCK;	//固定ブロックかノーマルブロックか

	bool m_SetSw;				//ブロックを固定するスイッチ
};