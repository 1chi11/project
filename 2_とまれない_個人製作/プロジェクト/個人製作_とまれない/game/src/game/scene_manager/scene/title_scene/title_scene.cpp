#include "title_scene.h"
const aqua::CVector2 CTitleScene::m_label_position = aqua::CVector2{0.0f,  aqua::GetWindowHeight() - 100.0f };
const int CTitleScene::m_label_size = 50;

CTitleScene::
CTitleScene(aqua::IGameObject* parent)
    : IScene(parent, "TitleScene")
{
}

void
CTitleScene::
Initialize(void)
{
	m_Sprite.Create("data\\title.png");
	m_Sprite.position = aqua::CVector2::ZERO;
	m_Label.Create(m_label_size, 2);
    m_Label.text = "Left Click to Start";
	m_Label.position.x = aqua::GetWindowWidth() / 2.0f - m_Label.GetTextWidth() / 2.0f;
	m_Label.position.y = m_label_position.y;

}

void
CTitleScene::
Update(void)
{
    // クリックされたらゲームメインシーンへ移行
    if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
    {
        CSoundPlayManager* sound = (CSoundPlayManager*)aqua::FindGameObject("SoundPlayManager");
        if (sound)
            sound->Play(SOUND_ID::CLICK);

        Change(SCENE_ID::GAME_MAIN);
    }
}

void
CTitleScene::
Draw(void)
{
	m_Sprite.Draw();
    m_Label.Draw();
}

void
CTitleScene::
Finalize(void)
{
	m_Label.Delete();
	m_Sprite.Delete();
	DeleteObject();
}
