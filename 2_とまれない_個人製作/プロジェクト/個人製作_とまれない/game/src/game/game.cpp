
/*!
 *  @file       game.cpp
 *  @brief      ゲーム管理
 *  @author     Kazuya Maruyama
 *  @date       2021/02/06
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "game.h"
#include "scene_manager/scene_manager.h"
#include"sound_play_manager/sound_play_manager.h"
#include"effect_manager/effect_manager.h"
#include"score_manager/score_manager.h"

const unsigned int CGame::m_clear_color = 0xff7f7f7f;

/*
 *  コンストラクタ
 */
CGame::
CGame( aqua::IGameObject* parent )
    : aqua::IGameObject( parent, "Game" )
{
}

/*
 *  初期化
 */
void
CGame::
Initialize(void)
{
    CSoundPlayManager* sound_manager = aqua::CreateGameObject<CSoundPlayManager>(this);
	aqua::CreateGameObject<CSceneManager>(this);
	aqua::CreateGameObject<CEffectManager>(this);
	aqua::CreateGameObject<CScoreManager>(this);
    // マウスカーソルの表示
    SetMouseDispFlag(TRUE);

    IGameObject::Initialize();
    sound_manager->Play(SOUND_ID::BGM);

}

/*
 *  描画
 */
void
CGame::
Draw(void)
{
    // 画面のクリア
    aqua::Clear(m_clear_color);

    // 描画したいオブジェクト群
    IGameObject::Draw();
}
