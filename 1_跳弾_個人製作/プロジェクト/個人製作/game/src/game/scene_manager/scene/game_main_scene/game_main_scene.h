#pragma once
#include "aqua.h"
#include "..\scene.h"
#include"stage_manager\stage_id.h"

class CBulletManager;
class CCharaManager;
class CBlockManager;
class CStageManager;
class CEffectManager;
class CSoundManager;
class CGameMainScene
    : public IScene
{
public:
    CGameMainScene( aqua::IGameObject* parent );
    ~CGameMainScene( void )=default;
    void Initialize( void );
    void Update( void );
    void Draw(void);

    //クリア判定の取得
    bool GetClearFlg();

    //クリアしたステージ数
    int  GetClearStageCount();
	//フェードインアウト
	void FeadIn(void);
	void FeadOut(void);

    void Explanation(void);
private:
    //ゲーム説明
    void GameExplanation(void);
    //ゲーム開始
    void GameStart( void );
    //ゲーム中
    void GamePlay( void );
    //ゲーム終了
    void GameFinish( void );

    //ゲームメインの状態
    enum STATE
    {
        STATE_GAME_EXPLANATION,         // ゲーム説明
		STATE_GAME_PLAYING_EXPLANATION, // ゲームプレイ中の説明
        STATE_GAME_START,               // ゲーム開始
        STATE_GAME_PLAY,                // ゲーム中
        STATE_GAME_FINISH,              // ゲーム終了
    };

    static const    float   m_shot_speed;   //弾の速さ
    static const    STAGE_ID    m_stage[];  //ステージID
    static const float  m_fade_speed;       //フェード速度
	static const float m_button_size;       //ボタンの大きさ

    aqua::CSprite       m_FadeSprite;       //フェード用スプライト
	bool 				  m_FadeIn;         //フェードインアウト判定

    aqua::CVector2  m_ShotPosition;         //発射position
    aqua::CVector2  m_ShotVector;           //発射vector
    float                   m_ShotAngle;    //発射angle
    float                   m_ShotSpeed;    //ボールの速さ

    aqua::CVector2 m_EffectPosition;        //エフェクトのposition
	aqua::CSprite   m_Explanation;	        //説明画像
	aqua::CSprite   m_PageTurn;             //ページをめくるための矢印スプライト
	int                     m_Page;                 //ページ数
	bool                    m_Explanation_First;    //初回説明フラグ
    bool                    m_StageClear;           //クリア判定
	bool                    m_StageCreate;	        //ステージ作成   
    bool                    m_StageAllClear;        //全ステージクリア
    bool                    m_First_Throw;          //一回は投げたか
    bool                    m_PastAngleShot;        //過去の場所に発射するか
	bool                    m_Explanation_Finish;   //説明終了判定
	bool 				   m_Loading_Finish;        //ロード終了判定 

    int                     m_StageNumber;      //ステージのナンバー
    int                     m_Throw;            //投げた回数

    float                  m_PastAngle;     //前回投げた角度
    aqua::CVector2 m_PastPosition;          //前回投げたposition

    STATE                   m_State;        //状態ID

    CBulletManager*   m_BulletManager;
    CCharaManager*  m_CharaManager;
    CBlockManager* m_BlockManager;
    CStageManager*  m_StageManager;
    CEffectManager* m_EffectManager;
	CSoundManager* m_SoundManager;
};
