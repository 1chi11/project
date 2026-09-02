#pragma once
#include "aqua.h"
#include"block/block_id.h"
#include <cstddef>
#include <vector>

class ICharacter;
class IStageGimmick;
class IItemObject;

class CBlockManager : public aqua::IGameObject
{
public:
	CBlockManager(aqua::IGameObject* parent);
	~CBlockManager(void) = default;
	void Initialize(void)override;
	void Update(void) override;
	void Draw(void) override;
	//ブロックの生成
	void Create(const aqua::CVector2& position,const bool set_flg);
	//ブロックの消去
	void Delete(void);
	//キャラクターとブロックの当たり判定
	void CharacterBlockHitCheck(ICharacter*& character);
	//アイテムオブジェクトとブロックの当たり判定
	void ItemObjectBlockHitCheck(IItemObject*& item_object);
	//ステージギミックとブロックの当たり判定
	void GimmickBlockHitCheck(IStageGimmick*& stage_gimmick);
	//ギミックとブロックの当たり判定
	void StageGimmickBlockHitCheck();
	//オブジェクトの当たり判定接触した方向を返す
	BLOCK_DIRECTION ObjectHitCheck(const aqua::CVector2& position, const aqua::CVector2& size, const aqua::CVector2& overcome)const;
	//オブジェクトとブロックの当たった位置を取得
	aqua::CVector2 GetBlockPosition(const aqua::CVector2& position, const aqua::CVector2& size, const aqua::CVector2& overcome)const;
	// 未配置ブロックをマウスで配置する
	void SetBlocks();
	//破壊されたブロックの位置を保存
	void SaveData(const aqua::CVector2& position);
	//破壊されたブロックの再生成
	void CreateSaveBlock();
	//保存内容を消去
	void DeleteSaveData();
private:
	static const int max;	//保存できる容量のMAX値
	int m_SaveNumber;		//現在保存している値
	struct SaveBlockData	//ブロックの保存
	{
		aqua::CVector2 position;
	};
	std::unique_ptr<SaveBlockData[]> m_BlockData;
};