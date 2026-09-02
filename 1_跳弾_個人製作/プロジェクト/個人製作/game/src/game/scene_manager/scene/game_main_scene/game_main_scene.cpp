#include"game_main_scene.h"
#include"..\..\..\bullet_manager\bullet_manager.h"
#include"..\..\..\chara_manager\chara_manager.h"
#include"..\..\..\block_manager\block_manager.h"
#include"..\..\..\effect_manager\effect_manager.h"
#include"stage_manager/stage_manager.h"
#include "..\..\..\sound_manager/sound_manager.h"
#include"..\..\..\score_manager\score_manager.h"
#include"..\..\..\ui_manager\ui_manager.h"

const float CGameMainScene::m_button_size = 120.0f;
const float CGameMainScene::m_shot_speed = 10.0f;
const float CGameMainScene::m_fade_speed = 255.0f;
const STAGE_ID CGameMainScene::m_stage[] =
{
   STAGE_ID::ONE,
	STAGE_ID::TWO,
	STAGE_ID::THREE,
	STAGE_ID::FOUR,
	STAGE_ID::FIVE,
	STAGE_ID::SIX,
	STAGE_ID::FINAL,
};


/*
 *  コンストラクタ
 */
CGameMainScene::
CGameMainScene(aqua::IGameObject* parent)
    : IScene(parent, "GameMainScene")
    , m_BulletManager(nullptr)
    , m_CharaManager(nullptr)
    , m_BlockManager(nullptr)
    ,m_StageManager(nullptr)
    ,m_EffectManager(nullptr)
    ,m_SoundManager(nullptr)
    ,m_StageClear(false)
    ,m_StageAllClear(false)
    ,m_StageCreate(false)
    ,m_First_Throw(false)
    ,m_PastAngleShot(false)
	, m_Explanation_Finish(false)
    , m_FadeIn(false)
	, m_Explanation_First(false)
    ,m_ShotSpeed(m_shot_speed)
    ,m_ShotPosition(0.0f,0.0f)
    , m_EffectPosition(0.0f, 0.0f)
    ,m_ShotVector(0.0f, 0.0f)
    ,m_ShotAngle(0.0f)
	,m_Throw(0)
	, m_Page(0)
{
}


/*
 *  初期化
 */
void
CGameMainScene::
Initialize(void)
{
	//ゲームオブジェクトの作成又は取得
    m_StageManager= aqua::CreateGameObject<CStageManager>(this);
    m_BulletManager = aqua::CreateGameObject<CBulletManager>(this);
    m_CharaManager = aqua::CreateGameObject<CCharaManager>(this);
    m_BlockManager = aqua::CreateGameObject<CBlockManager>(this);
    m_EffectManager = aqua::CreateGameObject<CEffectManager>(this);
    CUiManager*ui= aqua::CreateGameObject<CUiManager>(this);
	ui->Create(aqua::CVector2(0.0f, 0.0f), UI_ID::BOUNCE_COUNT);
    m_SoundManager= (CSoundManager*)aqua::FindGameObject("SoundManager");
    m_StageManager->SetManager(m_BulletManager, m_CharaManager, m_BlockManager);

    // // 状態設定　最初のステージint型
    m_State = STATE::STATE_GAME_EXPLANATION;
    m_StageNumber = 0;

	//ラベル作成



	//説明画像作成
    m_Explanation.position = aqua::CVector2::ZERO;
    m_Explanation.Create("data\\explanation1.png");
    m_PageTurn.position = aqua::CVector2{580.0f,600.0f};
	m_PageTurn.Create("data\\arrow.png");
	m_PageTurn.rect = aqua::CRect(0.0f, 0.0f, m_button_size, m_button_size);
	m_PageTurn.anchor = aqua::CVector2(m_button_size/2.0f, m_button_size/2.0f);
	m_PageTurn.rotation = aqua::DegToRad(90.0f);

	//フェード用のスプライト作成
	m_FadeSprite.Create("data\\white.png");
	m_FadeSprite.position = aqua::CVector2::ZERO;
    m_FadeSprite.color = aqua::CColor::BLACK;
	m_FadeSprite.color.alpha = (unsigned char)0.0f;

    IGameObject::Initialize();
}

/*
 *  更新
 */
void
CGameMainScene::
Update(void)
{
    switch (m_State)
    {
		//説明ステート
    case STATE_GAME_EXPLANATION:GameExplanation();   break;
		//ゲームプレイ中の説明ステート
    case STATE_GAME_PLAYING_EXPLANATION:Explanation(); break;
		//ゲーム開始ステート
    case STATE_GAME_START:  GameStart();   break;
		//ゲームプレイステート
    case STATE_GAME_PLAY:   GamePlay();    break;
		//ゲーム終了ステート
    case STATE_GAME_FINISH: GameFinish();  break;
    }
    IGameObject::Update();
}

void CGameMainScene::Draw(void)
{
    IGameObject::Draw();

    switch (m_State)
    {
    case STATE::STATE_GAME_EXPLANATION:
        m_Explanation.Draw();
		m_PageTurn.Draw();
        break;
	case CGameMainScene::STATE_GAME_PLAYING_EXPLANATION:
        m_Explanation.Draw();
        m_PageTurn.Draw();
        break;
    case CGameMainScene::STATE_GAME_START:
        break;
    case CGameMainScene::STATE_GAME_PLAY:
        break;
    case CGameMainScene::STATE_GAME_FINISH:
        break;
    default:
        break;
    }
    m_FadeSprite.Draw();
	//CUiManager* ui = (CUiManager*)aqua::FindGameObject("UiManager");
	//ui->Draw();
}

bool CGameMainScene::GetClearFlg()
{
    return m_StageClear;
}


int CGameMainScene::GetClearStageCount()
{
    return m_StageNumber;
}
void CGameMainScene::FeadIn(void)
{
    float alpha = (float)m_FadeSprite.color.alpha;

    alpha += m_fade_speed * aqua::GetDeltaTime();

    if (alpha > (float)aqua::CColor::MAX_COLOR)
    {
        alpha = (float)aqua::CColor::MAX_COLOR;
        m_State = STATE::STATE_GAME_START;
    }
    m_FadeSprite.color.alpha = (unsigned char)alpha;
}
void CGameMainScene::FeadOut(void)
{
    float alpha = (float)m_FadeSprite.color.alpha;

    alpha -= m_fade_speed * aqua::GetDeltaTime();

    if (alpha < 0.0f)
    {
        alpha = 0.0f;
    }
    m_FadeSprite.color.alpha = (unsigned char)alpha;
}

//任意で説明ステートに移る
void CGameMainScene::Explanation(void)
{
    aqua::CPoint mpos = aqua::mouse::GetCursorPos();
    if (!m_Explanation_First)
    {
        m_Explanation_First = true;
        m_Explanation.Create("data\\explanation1.png");
        m_Page = 0;
    }
	//説明ページの切り替えアイコンのクリックで説明ページの切り替え
	//説明ページ以外の場所をクリックでゲーム開始
    if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
    {
        if (mpos.x > m_PageTurn.position.x &&
            mpos.x < m_PageTurn.position.x + m_PageTurn.rect.right &&
            mpos.y > m_PageTurn.position.y &&
            mpos.y < m_PageTurn.position.y + m_PageTurn.rect.bottom)
        {
           if (m_Page == 0)
           {
               m_Explanation.Create("data\\explanation2.png");
               m_Page = 1;
           }
           else if (m_Page == 1)
           {
               m_Explanation.Create("data\\explanation1.png");
               m_Page = 0;
           }
        }
        else
        {
            m_State = STATE::STATE_GAME_START;
			//m_Explanation.Delete();
            m_Page = 0;
        }
    }
    
}


 // 強制的に説明ステートに移る
void CGameMainScene::GameExplanation(void)
{
    aqua::CPoint mpos = aqua::mouse::GetCursorPos();
    if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
    {
        //説明ページの切り替えアイコンのクリックで説明ページの切り替え
        //説明ページ以外の場所をクリックでゲーム開始
        if (mpos.x > m_PageTurn.position.x &&
            mpos.x < m_PageTurn.position.x + m_PageTurn.rect.right &&
            mpos.y > m_PageTurn.position.y &&
            mpos.y < m_PageTurn.position.y + m_PageTurn.rect.bottom)
        {
            if (m_Page == 0)
            {
                m_Explanation.Create("data\\explanation2.png");
                m_Page = 1;
            }
            else if (m_Page == 1)
            {
                m_Explanation.Create("data\\explanation1.png");
                m_Page = 0;
            }
        }
        else
        {
            m_FadeIn = true;
        }
    }

        if (m_FadeIn)
        {
            FeadIn();
        }
}

/*
 *  ゲーム開始
 */
void
CGameMainScene::
GameStart(void)
{
	FeadOut();
    aqua::CPoint mpos = aqua::mouse::GetCursorPos();
    //ステージ生成
    if (!m_StageCreate)
    {
        m_StageManager->Create(m_stage[m_StageNumber]);
        m_StageCreate = true;
    }
	//説明ステートに移行
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::H))
    {
		m_State = STATE_GAME_PLAYING_EXPLANATION;
    }

    //すべてのオブジェクトの消去
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Q))
    {
        if (m_BlockManager)
            m_BlockManager->AllDelete();
    }
            
    //つかんでいるオブジェクトの消去
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::G))
    {
        if (m_BlockManager)
            m_BlockManager->OneDelete();
    }

    //オブジェクト生成
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::SPACE))
    {
        if (m_BlockManager)
        {
            m_BlockManager->Create(BLOCK_ID::NOMAL_BLOCK,aqua::CVector2(0.0f,0.0f), aqua::CVector2(0.0f, 0.0f),0.0f);
        }
    }

	//オブジェクト設置
    if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
    {
        if (m_BlockManager)
        {
            m_BlockManager->SetBlock(false);
        }
    }

    //設置したオブジェクトをつかむ
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::E))
    {
        if (m_BlockManager)
        {
            m_BlockManager->CatchMoveBlock(mpos);
        }
    }
    //オブジェクトの移動
    if (m_BlockManager)
        m_BlockManager->MoveBlock(mpos);
    //オブジェクトの回転
    if (m_BlockManager)
        m_BlockManager->SpinBlock(aqua::mouse::GetWheel());

    //前回の場所にむけボールを発射する
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::X)&&m_First_Throw)
    {
        m_PastAngleShot = true;
    }
        //弾発射
    if ((aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::RIGHT) && m_BlockManager->GetHaving()) || m_PastAngleShot)
    {
        m_Throw++;
        m_First_Throw = true;
        m_EffectManager->Delete();

        if (m_PastAngleShot)
        {
            //前回の位置に発射
            m_PastAngleShot = false;
        }
        else
        {
            //マウスに向け発射
            m_ShotPosition = m_BulletManager->GetCenterPosition();
            m_ShotVector = aqua::CVector2((float)mpos.x, (float)mpos.y) - m_ShotPosition;
            m_ShotPosition.x -= m_BulletManager->GetRadius();
            m_ShotPosition.y -= m_BulletManager->GetRadius();
            m_ShotAngle = aqua::RadToDeg(atan2(m_ShotVector.y, m_ShotVector.x));

            m_EffectPosition = { (float)mpos.x,(float)mpos.y };
        }

        if (m_BulletManager)
        {
			//弾のステータスをセット
            m_BulletManager->Set_ShotStatus(m_ShotPosition, m_ShotAngle, m_ShotSpeed);
        }
        //発射した瞬間にステートを移行
        m_State = STATE_GAME_PLAY;
        aqua::CVector2 cursor_position = { (float)mpos.x,(float)mpos.y };
        m_EffectManager->Create(EFFECT_ID::SHOT_CURSOR_EFFECT, m_EffectPosition);
    }
}

/*
 *  ゲーム中
 */
void
CGameMainScene::
GamePlay(void)
{
    //途中リセット
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
    {
        m_State = STATE_GAME_FINISH;
        m_StageClear = false;
    }
    //ゲームの終了条件
    //ゲームクリア
    if ( m_CharaManager->CharaExist())
    {
        m_State = STATE_GAME_FINISH;

            m_StageClear = true;
    }
    //ゲームオーバー
    else if (!m_BulletManager->ActiveCheck())
    {
        m_State = STATE_GAME_FINISH;

        m_StageClear = false;
    }
}

/*
 *  ゲーム終了
 */
void
CGameMainScene::
GameFinish(void)
{
	//スコアの保存
	CScoreManager* score = (CScoreManager*)aqua::FindGameObject("ScoreManager");
	score->SetScore(m_Throw, m_StageNumber);
    //ステージの進行
    if (m_StageClear)
    {
		//Thorw数のリセット
		m_Throw = 0;
        m_EffectManager->Delete();
		//最終ステージのクリア
        if (m_stage[m_StageNumber] == STAGE_ID::FINAL)
        {
            m_StageAllClear = true;
            Push(SCENE_ID::RESULT);
			m_SoundManager->Finalize();

        }
		//次のステージへ
        m_StageNumber++;
        m_First_Throw = false;
    }

	//ステージリセット&再作成
	m_StageManager->StageReset(m_StageClear);
	m_State = STATE_GAME_START;
	m_StageCreate = false;
}
