#include "aqua.h"
#include "block_id.h"
#include"..\..\game_object_id.h"
#include"..\..\..\score_manager\score_manager.h"

class CBlock : public aqua::IGameObject
{
public:
	CBlock(aqua::IGameObject* parent);
	~CBlock(void) = default;
	void Initialize(const aqua::CVector2& position, const bool set_flag);
	void Update(void) override;
	void Draw(const aqua::CVector2& player_travel_distance) ;
	void Finalize(void) override;
	aqua::CVector2 GetPosition(void)const;
	aqua::CVector2 GetCenterPosition(void)const;
	aqua::CVector2 GetSize(void)const;
	bool GetSetFlg(void)const;
	GAME_OBJECT_ID GetGameObjectId(void) ;

	//プレイヤーがブロックに当たったときの方向を取得
	BLOCK_DIRECTION GetDirection(const aqua::CVector2& object_position, const aqua::CVector2& object_size, const aqua::CVector2& object_overcome);
	//ブロックの破壊演出
	void Clash(void);
	//ブロックの位置指定の処理
	void Set(const aqua::CVector2& player_travel_distance, const aqua::CVector2& mouse_pos,const bool push_key);
private:
	static const float	m_size;		//ブロックのサイズ
	static const float	m_clash_score;	//ブロックの破壊演出の速度
	aqua::CVector2		m_Position;	//ブロックの位置
	aqua::CSprite		m_Sprite;	//ブロックのスプライト

	BLOCK_DIRECTION m_Direction;	//プレイヤーがブロックに当たったときの方向
	bool m_Set;			//ブロックがセットされているかどうかセットしていたらtrueを返す

	GAME_OBJECT_ID m_GameObjectId;	//ブロックのID
};