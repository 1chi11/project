#pragma once
#include"aqua.h"
#include"..\bullet_manager\bullet_manager.h"
#include"block/block.h"
#include"block_id.h"
#include"block/nomal_block/nomal_block.h"

class CEffectManager;

class CBlockManager
	:public aqua::IGameObject
{
public:
	CBlockManager(aqua::IGameObject* parent);
	~CBlockManager() = default;
	//trueだと動かせる
	//動くオブジェクト
	void Create(BLOCK_ID id, aqua::CVector2 position1, aqua::CVector2 position2,float speed);
	//設置したオブジェクトの消去
	void AllDelete();		
	//所持しているオブジェクトの消去
	void OneDelete();		
	//設置したオブジェクト以外を消去
	void Reset();				
	//回転矩形と円の当たり判定
	IBlock* BlockHitRotated(aqua::CVector2 position, float ball_radius);
	//オブジェクトの設置
	void SetBlock(bool sw);
	//オブジェクトの移動
	void MoveBlock(aqua::CPoint point);
	//つかんでいるオブジェクトの移動
	void CatchMoveBlock(aqua::CPoint point);
	//オブジェクトを掴んでいるか判別
	bool GetHaving();			
	//オブジェクトの回転
	void SpinBlock(int spin);
private:
	IBlock* m_Block;			//現在所持しているオブジェクト
	CEffectManager* m_EffectManager;
	bool m_Having;				//オブジェクトの重なり対策　持ってる時ノット
};