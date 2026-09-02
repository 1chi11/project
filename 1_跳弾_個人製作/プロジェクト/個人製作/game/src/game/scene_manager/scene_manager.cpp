#include "scene_manager.h"
#include "scene\result_scene\result_scene.h"
#include "scene\title_scene\title_scene.h"
#include "scene\game_main_scene\game_main_scene.h"

const float CSceneManager::m_fade_speed = 255.0f;

CSceneManager::
CSceneManager(aqua::IGameObject* parent)
    : aqua::IGameObject(parent, "SceneManager")
    , m_CurrentSceneID(SCENE_ID::DUMMY)
    , m_NextSceneID(SCENE_ID::DUMMY)
    , m_PushSceneID(SCENE_ID::DUMMY)
    , m_State(STATE::SCENE_IN)
    , m_PushFlag(false)
{
}

void
CSceneManager::
Initialize(void)
{
    // フェード用スプライト生成
    m_FadeSprite.Create("data\\white.png");

    m_FadeSprite.color = aqua::CColor::BLACK;

    //最初のシーン
    Create(SCENE_ID::TITLE);

    // シーンイン状態を設定
    m_State = STATE::SCENE_IN;

    // プッシュフラグOFF
    m_PushFlag = false;
}


void
CSceneManager::
Update(void)
{
    switch (m_State)
    {
    case STATE::SCENE_IN:       SceneIn();         break;
    case STATE::SCENE_UPDATA:   SceneUpdate();     break;
    case STATE::SCENE_OUT:      SceneOut();        break;
    case STATE::SCENE_CHANGE:   SceneChange();     break;
    }
}

void
CSceneManager::
Draw(void)
{
    IGameObject::Draw();

    m_FadeSprite.Draw();
}


void
CSceneManager::
Finalize(void)
{
    IGameObject::Finalize();

    m_FadeSprite.Delete();
}

void
CSceneManager::
Change(SCENE_ID id)
{
    // 次のシーンID
    m_NextSceneID = id;
}

void
CSceneManager::
Push(SCENE_ID id)
{
    // 同フレーム中にすでにプッシュされている
    if (m_PushFlag || m_PushSceneID != SCENE_ID::DUMMY) return;

    // プッシュフラグをON
    m_PushFlag = true;

    // スタックするシーンIDを保存
    m_PushSceneID = id;
}

void
CSceneManager::
Pop(void)
{
    // 子のシーンが1つの場合はポップできない
    if (m_ChildObjectList.size() <= 1)
        return;

    // 末尾のシーンのイテレータ取得
    aqua::GAME_OBJECT_LIST::reverse_iterator it = m_ChildObjectList.rbegin();

    // シーンクラスにキャスト
    IScene* scene = (IScene*)(*it);

    // 末尾のシーンを削除対象に設定
    scene->DeleteObject();

    // ひとつ前のシーンを取得
    scene = (IScene*)(*(++it));

    // ひとつ前のシーンをアクティブ状態に変更
    scene->SetGameObjectState(aqua::GAME_OBJECT_STATE::ACTIVE);
}


void
CSceneManager::
Reset(void)
{
    m_NextSceneID = m_CurrentSceneID;

    m_CurrentSceneID = SCENE_ID::DUMMY;
}


void
CSceneManager::
Create(SCENE_ID id)
{
    IScene* scene = nullptr;

    // idごとに新しくシーンを生成
    switch (id)
    {
    case SCENE_ID::TITLE:       scene = aqua::CreateGameObject<CTitleScene>(this);        break;
    case SCENE_ID::GAME_MAIN:    scene = aqua::CreateGameObject<CGameMainScene>(this);     break;
    case SCENE_ID::RESULT:      scene = aqua::CreateGameObject < CResultScene >(this);     break;
    }

    AQUA_ASSERT(scene, "シーンが生成できませんでした。");

    // シーンを初期化
    scene->Initialize();
}

void
CSceneManager::
Delete(void)
{
    IGameObject::Finalize();
}

void
CSceneManager::
SceneIn(void)
{
    float alpha = (float)m_FadeSprite.color.alpha;

    alpha -= m_fade_speed * aqua::GetDeltaTime();

    if (alpha < 0.0f)
    {
        alpha = 0.0f;

        m_State = STATE::SCENE_UPDATA;
    }

    m_FadeSprite.color.alpha = (unsigned char)alpha;
}

void
CSceneManager::
SceneUpdate(void)
{
    // プッシュ処理が行われていた場合
    if (m_PushFlag)
    {
        // 新しいシーンを生成してスタックする
        Create(m_PushSceneID);

        // 未使用時はダミーIDを入れておく
        m_PushSceneID = SCENE_ID::DUMMY;

        // シーンのプッシュが終了した
        m_PushFlag = false;
    }

    IGameObject::Update();

    // シーンの変更を検知
    if (m_CurrentSceneID != m_NextSceneID)
        m_State = STATE::SCENE_OUT;
}


void
CSceneManager::
SceneOut(void)
{
    float alpha = (float)m_FadeSprite.color.alpha;

    alpha += m_fade_speed * aqua::GetDeltaTime();

    if (alpha > (float)aqua::CColor::MAX_COLOR)
    {
        alpha = (float)aqua::CColor::MAX_COLOR;

        m_State = STATE::SCENE_CHANGE;
    }

    m_FadeSprite.color.alpha = (unsigned char)alpha;
}

void
CSceneManager::
SceneChange(void)
{
    // 現在のシーンを削除
    Delete();

    // 次のシーンを生成
    Create(m_NextSceneID);

    // シーンIDを保存
    m_CurrentSceneID = m_NextSceneID;

    // 状態を移行
    m_State = STATE::SCENE_IN;
}
