#pragma once
#include "aqua.h"
#include<array>
#include<string>
#include "..\scene.h"

class CStageManager;
class CEffectManager;
class CSoundPlayManager;
class CBlockManager;
class CItemObjectManager;
class CCharacterManager;
class CStageGimmickManager;
class CButtonManager;
class CTimeSpeed;

class CGameMainScene
    : public IScene
{
public:

    CGameMainScene( aqua::IGameObject* parent );
    ~CGameMainScene( void )=default;
    void Initialize( void )override;
    void Update( void )override;
    void Draw(void)override;
    void Finalize(void)override;

	//最大ステージ番号の取得
	int GetMaxStageNumber(void);
	//現在のステージ番号の取得
    int GetCurrentStageNumber(void);
    //ゴール処理
    void Goal(void);
	//フェードインアウト
	void FadeIn(void);
	void FadeOut(void);
    //ステージの生成
	void StageCreate(void);
private:
    //続ける
    void GameContinue(void);
    //再スタート
    void GameRetry(void);
    //ポーズメニュー
    void GamePause(void);
    //ポーズメニューの生成
    void GamePauseCreate(void);
    //ボタンの生成
    void CreateButton(void);
    //ゲーム開始
    void GameStart( void );
    //ゲーム中
    void GamePlay( void );
    //ゲーム終了
    void GameFinish( void );
	//タイマーの更新
	void UpdateTimer(void);
	static const aqua::CVector2 m_button_position[]; //ボタンの位置
    static const std::array<std::string, 3> m_stage_file_names;//ステージファイルパス
    static const float  m_fade_speed;    //フェード速度
	static const float  m_button_size;   //ボタンの大きさ
	static const float  m_frame_rate;    //フレームレート
    static const int    m_max_stage;     //ステージ数   
    static const int    m_start_stage;   //最初のステージ   
    aqua::CSprite   m_FadeSprite;        //フェード用スプライト
    float m_TimeCount;          //タイムカウント
    float m_Timer;                //タイマー
    bool m_FadeIn;              //フェードインアウト判定
    int   m_StageNumber;        //ステージのナンバー

    enum STATE
    {
        STATE_GAME_START,   // ゲーム開始
        STATE_GAME_PLAY,    // ゲーム中
        STATE_GAME_FINISH,  // ゲーム終了
        STATE_GAME_PAUSE    //ポーズメニュー
    };
    STATE m_State;              //状態ID
    enum STAGE_ID
    {
		STAGE_1,  //ステージ1
		STAGE_2,  //ステージ2
		STAGE_3,  //ステージ3
    };
    enum BUTTON_ID
    {
        BUTTON_CONTINUE,    //続ける
        BUTTON_RETRY,       //再スタート
        BUTTON_TITLE,       //タイトルに戻る
        BUTTON_TRAMPOLINE,  //トランポリン
        BUTTON_DRILL,       //ドリル
        BUTTON_UMBRELLA,    //傘
        BUTTON_PAUSE,       //ポーズボタン
	};
    CStageManager* m_StageManager;              //ステージマネージャー
    CEffectManager* m_EffectManager;            //エフェクトマネージャー
    CSoundPlayManager* m_SoundPlayManager;      //サウンドマネージャー
    CBlockManager* m_BlockManager;              //ブロックマネージャー
    CItemObjectManager* m_ItemObjectManager;    //アイテムマネージャー
    CCharacterManager* m_CharacterManager;      //キャラクターマネージャー
    CStageGimmickManager* m_StageGimmickManager;//ギミックマネージャー
    CButtonManager* m_ButtonManager;            //ボタンマネージャー
	CTimeSpeed* m_TimeSpeed;                    //タイムスピードマネージャー
};
