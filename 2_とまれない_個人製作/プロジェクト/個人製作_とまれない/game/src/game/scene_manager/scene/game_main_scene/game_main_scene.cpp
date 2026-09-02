
#include"game_main_scene.h"
#include"..\..\..\effect_manager\effect_manager.h"
#include"..\..\..\score_manager\score_manager.h"
#include"..\..\..\ui_manager\ui_manager.h"
#include"..\..\..\game_object\game_object.h"
#include"..\..\..\button_manager\button_manager.h"
#include"..\..\..\mouse\mouse.h"
#include"..\..\..\time_speed\time_speed.h"
const aqua::CVector2 CGameMainScene::m_button_position[] = { 
    aqua::CVector2(500.0f, 150.0f),
    aqua::CVector2(500.0f, 300.0f),
    aqua::CVector2(500.0f, 450.0f),
    aqua::CVector2(200.0f, 0.0f), 
    aqua::CVector2(400.0f, 0.0f), 
    aqua::CVector2(600.0f, 0.0f),
    aqua::CVector2(1050.0f, 600.0f)
};
const std::array<std::string, 3> CGameMainScene::m_stage_file_names{ "data\\stage1.csv", "data\\stage2.csv", "data\\stage3.csv", };
const float CGameMainScene::m_button_size = 120.0f;
const float CGameMainScene::m_fade_speed = 255.0f;
const float CGameMainScene::m_frame_rate = 60.0f;
const int CGameMainScene::m_max_stage = STAGE_ID::STAGE_3;
const int CGameMainScene::m_start_stage = STAGE_ID::STAGE_1;


CGameMainScene::
CGameMainScene(aqua::IGameObject* parent)
    : IScene(parent, "GameMainScene")
    , m_FadeIn(false)
    , m_StageNumber(0)
	, m_Timer(0.0f)
	, m_TimeCount(0.0f)
    , m_StageManager(nullptr)
    , m_BlockManager(nullptr)
    , m_ButtonManager(nullptr)
    , m_CharacterManager(nullptr)
    , m_EffectManager(nullptr)
    , m_SoundPlayManager(nullptr)
    , m_ItemObjectManager(nullptr)
    , m_StageGimmickManager(nullptr)
	, m_TimeSpeed(nullptr)
{
}


void
CGameMainScene::
Initialize(void)
{
   // 状態設定　最初のステージint型
    m_State = STATE::STATE_GAME_START;
    m_StageNumber = m_start_stage;


	//フェード用のスプライト作成
	m_FadeSprite.Create("data\\white.png");
	m_FadeSprite.position = aqua::CVector2::ZERO;
    m_FadeSprite.color = aqua::CColor::BLACK;
	m_FadeSprite.color.alpha = (unsigned char)0.0f;

    //ブロック、アイテムオブジェクト、ステージギミックのマネージャーを作成
    aqua::CreateGameObject<CMouseControl>(this);
	aqua::CreateGameObject<CStage>(this);
    m_TimeSpeed = aqua::CreateGameObject<CTimeSpeed>(this);
    m_BlockManager = aqua::CreateGameObject<CBlockManager>(this);
    m_ItemObjectManager = aqua::CreateGameObject<CItemObjectManager>(this);
    m_CharacterManager = aqua::CreateGameObject<CCharacterManager>(this);
    m_StageGimmickManager = aqua::CreateGameObject<CStageGimmickManager>(this);
    m_ButtonManager = aqua::CreateGameObject<CButtonManager>(this);
    m_SoundPlayManager = (CSoundPlayManager*)aqua::FindGameObject("SoundPlayManager");
    CUiManager* ui = aqua::CreateGameObject<CUiManager>(this);
    ui->Initialize();
    CScoreManager* score = (CScoreManager*)aqua::FindGameObject("ScoreManager");
	score->InitializeScore(m_max_stage + 1);
    score->SetStageNumber(m_StageNumber);
}


void
CGameMainScene::
Update(void)
{
    switch (m_State)
    {
    case STATE_GAME_START:  GameStart();    break;
    case STATE_GAME_PLAY:   GamePlay();     break;
    case STATE_GAME_FINISH: GameFinish();   break;
    case STATE_GAME_PAUSE:  GamePause();    break;
    }
}

void CGameMainScene::Draw(void)
{
    IGameObject::Draw();
    CScoreManager* score = (CScoreManager*)aqua::FindGameObject("ScoreManager");
    score->GamePlayDraw();

}

void CGameMainScene::Finalize(void)
{
    m_FadeSprite.Delete();
    m_BlockManager->Finalize();
    m_CharacterManager->Finalize();
    m_ItemObjectManager->Finalize();
    m_StageGimmickManager->Finalize();

    IGameObject::Finalize();
}

int CGameMainScene::GetMaxStageNumber(void)
{
    return m_max_stage;
}

int CGameMainScene::GetCurrentStageNumber(void)
{
    return m_StageNumber;
}

void CGameMainScene::Goal(void)
{
	CScoreManager* score = (CScoreManager*)aqua::FindGameObject("ScoreManager");    
	score->SetTime((int)m_Timer);
    //最終ステージか確認
    if (m_StageNumber < m_max_stage)
    {
        //違ったら次のステージ
        m_StageNumber++;
        m_State = STATE_GAME_START;
        score->SetStageNumber(m_StageNumber);
    }
    else
    {
        //最終ステージだったら終了
        GameFinish();
    }
}


void CGameMainScene::FadeIn(void)
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
void CGameMainScene::FadeOut(void)
{
    float alpha = (float)m_FadeSprite.color.alpha;

    alpha -= m_fade_speed * aqua::GetDeltaTime();

    if (alpha < 0.0f)
    {
        alpha = 0.0f;
    }
    m_FadeSprite.color.alpha = (unsigned char)alpha;
}


void CGameMainScene::StageCreate(void)
{
	m_TimeCount = 0;
	m_Timer = 0;
    //画面全体をリセット
    m_BlockManager->Delete();
    m_CharacterManager->Delete();
    m_ItemObjectManager->Delete();
    m_StageGimmickManager->Delete();

    //ボタン用のオブジェクト群
    CreateButton();
	//CSVファイルからステージの情報を読み取ってステージを作成
	aqua::CCSVLoader stage_loader;
	stage_loader.Load(m_stage_file_names[m_StageNumber]);
	//1ブロックのサイズを指定
	aqua::CVector2 block_size = aqua::CVector2(150.0f, 150.0f);
	//設置する位置を指定
	aqua::CVector2 stage_position(0.0f, 0.0f);
    for (int row = 0; row < stage_loader.GetRows(); ++row) 
    {
        for (int col = 0; col < stage_loader.GetCols(); ++col) 
        {
            stage_position = aqua::CVector2(block_size.x * col, block_size.y * row);
            switch (stage_loader.GetInteger(row, col)) {
            case 1:
                m_BlockManager->Create(stage_position, true);
                break;
			//case 2:
			//	block_manager->Create(stage_position);
			//	break;
            case 3:
                m_CharacterManager->Create(CHARACTER_ID::PLAYER, stage_position, aqua::CVector2(0.0f, 0.0f));
				break;
			case 4:
                m_CharacterManager->Create(CHARACTER_ID::ENEMY, stage_position, aqua::CVector2(0.0f, 0.0f));
				break;
            case 5:
				break;
			case 6:
				m_ItemObjectManager->Create(GAME_OBJECT_ID::DRILL, stage_position,true);
				break;
			case 7:
                m_ItemObjectManager->Create(GAME_OBJECT_ID::TRAMPOLINE, stage_position,true);
				break;
			case 8:
                m_ItemObjectManager->Create(GAME_OBJECT_ID::UMBRELLA, stage_position,true);
				break;
			case 9:
                m_StageGimmickManager->Create(STAGE_GIMMICK_ID::SPIKE, stage_position,true);
				break;
			case 10:
                m_StageGimmickManager->Create(STAGE_GIMMICK_ID::FIRE, stage_position,true);
				break;
			case 11:
                m_StageGimmickManager->Create(STAGE_GIMMICK_ID::CHECK_POINT, stage_position,true);
				break;
			case 12:
                m_StageGimmickManager->Create(STAGE_GIMMICK_ID::GOAL, stage_position,true);
				break;
            default:
                break;
            }
        }
    }
	//CSVローダーの解放
    stage_loader.Unload();
	//ステートの移行
	m_State = STATE::STATE_GAME_PLAY;
	IGameObject::Initialize();
}

void CGameMainScene::GameContinue(void)
{
    CreateButton();
    m_State = STATE_GAME_PLAY;
}

void CGameMainScene::GameRetry()
{
    m_State = STATE_GAME_START;
}


void CGameMainScene::GamePause(void)
{
    //ボタンの更新
    CButtonManager* button = (CButtonManager*)aqua::FindGameObject("ButtonManager");
    if (!button)
        return;
    button->Update();
}

void CGameMainScene::GamePauseCreate(void)
{
    //設置済みのボタンの消去
    m_ButtonManager->Delete();

    //ポーズ用ボタンの生成
    m_ButtonManager->Create([this] {this->GameContinue();}, m_button_position[BUTTON_ID::BUTTON_CONTINUE],
        "data\\continue.png", GAME_OBJECT_ID::DUMMY);
    m_ButtonManager->Create([this] {this->Change(SCENE_ID::TITLE);}, m_button_position[BUTTON_ID::BUTTON_TITLE],
        "data\\title_button.png", GAME_OBJECT_ID::DUMMY);
    m_ButtonManager->Create([this] {this->GameRetry();}, m_button_position[BUTTON_ID::BUTTON_RETRY],
        "data\\retry.png", GAME_OBJECT_ID::DUMMY);

    //状態をポーズに移行
    m_State = STATE_GAME_PAUSE;

}

void CGameMainScene::CreateButton(void)
{
    //設置済みのボタンの消去
    m_ButtonManager->Delete();

    CCharacterManager* character = (CCharacterManager*)aqua::FindGameObject("CharacterManager");

    //ゲームメイン用ボタンの生成
    m_ButtonManager->Create([character] {character->CreateItemObject(GAME_OBJECT_ID::TRAMPOLINE, aqua::CVector2(0.0f, 0.0f)); }, m_button_position[BUTTON_ID::BUTTON_TRAMPOLINE],
        "data\\trampoline.png", GAME_OBJECT_ID::TRAMPOLINE);
    m_ButtonManager->Create([character] {character->CreateItemObject(GAME_OBJECT_ID::DRILL, aqua::CVector2(0.0f, 0.0f)); }, m_button_position[BUTTON_ID::BUTTON_DRILL],
        "data\\drill.png", GAME_OBJECT_ID::DRILL);
    m_ButtonManager->Create([character] {character->CreateItemObject(GAME_OBJECT_ID::UMBRELLA, aqua::CVector2(0.0f, 0.0f)); }, m_button_position[BUTTON_ID::BUTTON_UMBRELLA],
        "data\\umbrella.png", GAME_OBJECT_ID::UMBRELLA);
    m_ButtonManager->Create([this] {this->GamePauseCreate();}, m_button_position[BUTTON_ID::BUTTON_PAUSE],
        "data\\pause.png", GAME_OBJECT_ID::DUMMY);

}

void
CGameMainScene::
GameStart(void)
{
	StageCreate();
}

void
CGameMainScene::
GamePlay(void)
{
	IGameObject::Update();
    UpdateTimer();
}


void
CGameMainScene::
GameFinish(void)
{
    Change(SCENE_ID::RESULT);
}

void CGameMainScene::UpdateTimer(void)
{
	m_TimeCount += 1;
	//1秒経過したらタイマーを更新 60フレームで1秒なので、フレームレートを60に設定している
    if (m_TimeCount / (m_frame_rate /m_TimeSpeed->GetTimeSpeed()) > 1.0f)
    {
        m_Timer += 1;
		m_TimeCount = 0.0f;
		CScoreManager* score = (CScoreManager*)aqua::FindGameObject("ScoreManager");
		score->SetTime((int)m_Timer);
    }
}
