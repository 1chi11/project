#include "result_scene.h"
#include <game/sound_manager/sound_manager.h>
#include"..\..\..\score_manager\score_manager.h"

const float CResultScene::m_wait_time = 1.0f;

/*
 *  コンストラクタ
 */
CResultScene::
CResultScene(aqua::IGameObject* parent)
    : IScene(parent, "ResultScene")
{
}

CResultScene::~CResultScene(void)
{
    for (int i = 0;i < 10;i++)
        m_ThrowCountLabel[i].Delete();

    m_Sprite.Delete();
    IGameObject::Finalize();
}

/*
 *  初期化
 */
void
CResultScene::
Initialize(void)
{
    CSoundManager* sound = (CSoundManager*)aqua::FindGameObject("SoundManager");
    sound->Create(SOUND_ID::CLEAR_BGM, true);
	CScoreManager* score = (CScoreManager*)aqua::FindGameObject("ScoreManager");
	m_StageCount = score->GetStageCount()+1;

    // タイマー設定
    for (int i = 0;i < m_StageCount;i++)
    {
        m_ThrowCountLabel[i].Create(40);
        m_ThrowCountLabel[i].position = {600.0f,0.0f + 100.0f*i};
    }
    

    for (int i = 0;i < m_StageCount;i++)
    {
		int sc = score->GetScore(i);

        m_ThrowCountLabel[i].text = "\tSTAGE:" + std::to_string((int)i + 1) + "\tThrow:" + std::to_string((int)sc);
    }
    m_Sprite.position = {0.0f,0.0f};
    m_Sprite.Create("data\\game_clear.png");

}

/*
 *  更新
 */
void
CResultScene::
Update(void)
{
    // タイマー更新

    if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
    {
        // タイトルシーンに変更
        Change(SCENE_ID::TITLE);
    }
    if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::RIGHT))
    {
		// タイトルシーンに変更
		Change(SCENE_ID::TITLE);
    }
}

/*
 *  描画
 */
void
CResultScene::
Draw(void)
{
    m_Sprite.Draw();
    for (int i = 0;i < m_StageCount;i++)
		m_ThrowCountLabel[i].Draw();
}

void CResultScene::Finalize()
{
    m_Sprite.Delete();
	for (int i = 0;i < m_StageCount;i++)
		m_ThrowCountLabel[i].Delete();
    CScoreManager* score = (CScoreManager*)aqua::FindGameObject("ScoreManager");
	score->Finalize();
    CSoundManager* sound = (CSoundManager*)aqua::FindGameObject("SoundManager");
    sound->Finalize();

	DeleteObject();
}



