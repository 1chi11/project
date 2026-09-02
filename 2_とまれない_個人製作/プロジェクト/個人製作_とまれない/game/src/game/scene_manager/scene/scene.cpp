#include "scene.h"
#include "..\scene_manager.h"

const std::string   IScene::m_scene_category = "Scene";

IScene::
IScene(aqua::IGameObject* parent, const std::string& object_name)
    : aqua::IGameObject(parent, object_name, m_scene_category)
{
}

void
IScene::
Change(SCENE_ID id)
{
    // 親のシーンマネージャーを呼び出す
    CSceneManager* sm = (CSceneManager*)GetParent();

    // シーンを変更する
    sm->Change(id);
}



void
IScene::
Push(SCENE_ID id)
{
    // 親のシーンマネージャーを呼び出す
    CSceneManager* sm = (CSceneManager*)GetParent();

    // シーンをスタックする
    sm->Push(id);

    // 自分は更新を停止し、描画のみ行う
    m_GameObjectState = aqua::GAME_OBJECT_STATE::WAIT;
}

void
IScene::
Pop(void)
{
    // 親のシーンマネージャーを呼び出す
    CSceneManager* sm = (CSceneManager*)GetParent();

    // スタックされたシーンを取り出す
    sm->Pop();
}

void
IScene::
Reset(void)
{
    // 親のシーンマネージャーを呼び出す
    CSceneManager* sm = (CSceneManager*)GetParent();

    // リセット
    sm->Reset();
}
