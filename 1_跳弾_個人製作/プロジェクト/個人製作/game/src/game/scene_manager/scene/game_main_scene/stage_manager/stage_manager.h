#include"aqua.h"
#include"stage_id.h"
class CBulletManager;
class CCharaManager;
class CBlockManager;

class CStageManager
	:public aqua::IGameObject
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent  親のオブジェクト
     */
    CStageManager(aqua::IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CStageManager(void) = default;

    //初期化
	void Initialize(void) override ;

    //描画
	void Draw(void) override;

	//      ステージの作成
    void            Create(STAGE_ID id);

	//	  マネージャーのセット
    void SetManager(CBulletManager* bullet, CCharaManager* chara, CBlockManager* block);

	//	  ステージのリセット
	void StageReset(bool clear);
private:

    CBulletManager* m_BulletManager;

    CCharaManager* m_CharaManager;

    CBlockManager* m_BlockManager;

	//ステージのレイアウトデータのパラメータ
    enum class OBJECT_ID_DATA
    {
        GAMEOBJECT_ID,
    };
	//キャラクターのレイアウトデータのパラメータ
    enum class STAGE_LAYOUT_CHARACTER_DATA_PARAM
    {
        GAMEOBJECT_ID,
        X,
        Y
    };
	//オブジェクトのレイアウトデータのパラメータ
    enum class STAGE_LAYOUT_OBJECT_DATA_PARAM
    {
        GAMEOBJECT_ID,
        X,
        Y
    };
	//動くオブジェクトのレイアウトデータのパラメータ
    enum class STAGE_LAYOUT_MOVE_OBJECT_DATA_PARAM
    {
        GAMEOBJECT_ID,
        X1,
        Y1,
        X2,
        Y2,
        SPEED
    };
	//弾のレイアウトデータのパラメータ
    enum class STAGE_LAYOUT_BALL_DATA_PARAM
    {
        GAMEOBJECT_ID,
        X,
        Y,
        BOUNCE
    };

	//ステージのレイアウトデータ
    struct CHRACTER_TABLE_DATA
    {
        float       x;
        float       y;
    };

	//動くオブジェクトのレイアウトデータ
    struct OBJECT_TABLE_DATA
    {
        float       x1;
        float       y1;
        float       x2;
        float       y2;
        float       speed;
    };

	//弾のレイアウトデータ
    struct BALL_TABLE_DATA
    {
        float       x;
        float       y;
        int         bounce;
    };
	aqua::CSprite m_BackGround; //ステージの背景
};
