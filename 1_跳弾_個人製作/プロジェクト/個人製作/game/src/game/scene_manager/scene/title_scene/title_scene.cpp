#include "title_scene.h"
#include <game/sound_manager/sound_manager.h>


/*
 *  コンストラクタ
 */
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
    CSoundManager* sound = (CSoundManager*)aqua::FindGameObject("SoundManager");
    sound->Create(SOUND_ID::BATTLE_BGM, true);

}

void
CTitleScene::
Update(void)
{
    // クリックされたらゲームメインシーンへ移行
    if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
    {
        Change(SCENE_ID::GAME_MAIN);
    }
}


void
CTitleScene::
Draw(void)
{
	m_Sprite.Draw();
}

void
CTitleScene::
Finalize(void)
{
	m_Sprite.Delete();
	DeleteObject();
}
