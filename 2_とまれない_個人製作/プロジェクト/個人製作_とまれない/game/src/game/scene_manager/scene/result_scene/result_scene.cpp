#include "result_scene.h"
#include"..\..\..\score_manager\score_manager.h"
const aqua::CVector2 CResultScene::m_label_position = aqua::CVector2(0.0f, aqua::GetWindowHeight() - 100.0f);
const int CResultScene::m_label_size = 50;

CResultScene::
CResultScene(aqua::IGameObject* parent)
    : IScene(parent, "ResultScene")
{
}

void
CResultScene::
Initialize(void)
{
	CScoreManager* score_manager = (CScoreManager*)aqua::FindGameObject("ScoreManager");
    if(score_manager)
        if (score_manager->GetClearFlag())
        {
			// ゲームクリアのスプライトを生成
            m_Sprite.Create("data\\game_clear.png");

        }
        else
        {
			// ゲームオーバーのスプライトを生成
            m_Sprite.Create("data\\game_over.png");
        }
	m_Sprite.position = aqua::CVector2::ZERO;
	m_Label.Create(m_label_size, 2);
	m_Label.text = "Left Click to Return Title";
	m_Label.position.x = aqua::GetWindowWidth() / 2.0f - m_Label.GetTextWidth() / 2.0f;
    m_Label.position.y = m_label_position.y;

}

void
CResultScene::
Update(void)
{
    if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
    {
        CSoundPlayManager* sound = (CSoundPlayManager*)aqua::FindGameObject("SoundPlayManager");
        if (sound)
            sound->Play(SOUND_ID::CLICK);
        // タイトルシーンに変更
        Change(SCENE_ID::TITLE);
    }
}

void
CResultScene::
Draw(void)
{
    m_Sprite.Draw();
	CScoreManager* score_manager = (CScoreManager*)aqua::FindGameObject("ScoreManager");
    if(score_manager)
		score_manager->ResultDraw();
	m_Label.Draw();
}

void CResultScene::Finalize()
{
	m_Sprite.Delete();
	m_Label.Delete();
	DeleteObject();
}



