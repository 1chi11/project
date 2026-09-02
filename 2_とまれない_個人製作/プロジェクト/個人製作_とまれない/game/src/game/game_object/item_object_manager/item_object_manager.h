#pragma once
#include "aqua.h"
#include"..\game_object_id.h"
class ICharacter;


class CItemObjectManager : public aqua::IGameObject
{
	public:
	CItemObjectManager(aqua::IGameObject* parent);
	~CItemObjectManager(void) = default;
	void Update(void) override;
	void Draw(void) override;
	//アイテムの生成
	void Create(const GAME_OBJECT_ID id, const aqua::CVector2& position,const bool set_flag);
	//アイテムの消去
	void Delete(void);
	GAME_OBJECT_ID GetCharacterHitObjectCheck(const aqua::CVector2& position, const aqua::CVector2& size)const;
	//キャラクターとアイテムオブジェクトの当たり判定
	void CharacterItemObjectCheckHit(ICharacter*& character) ;
	//アイテムオブジェクトとブロックの当たり判定
	void BlockItemObjectCheckHit(void);
	//ステージギミックとアイテムオブジェクトの当たり判定
	void StageGimmickItemObjectCheckHit(void);
	//アイテムオブジェクトの位置指定の処理
	void ItemObjectSet(void);
	//時間の速さをセット
	void SetTimeSpeed(const float rate);
};