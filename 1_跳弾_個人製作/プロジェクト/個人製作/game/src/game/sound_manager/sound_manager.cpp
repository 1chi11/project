#include "sound_manager.h"
#include"sound/sound.h"
#include"sound/battle_bgm/battle_bgm.h"
#include"sound/enemy_hit_sound/enemy_hit_sound.h"
#include"sound/wall_hit_sound/wall_hit_sound.h"
#include"sound/shot_sound/shot_sound.h"
#include "sound/clear_bgm/clear_bgm.h"
#include "sound/block_create_sound/block_create_sound.h"
#include "sound/block_roatate_sound/block_roatate_sound.h"

/*
 *  コンストラクタ
 */
CSoundManager::
CSoundManager(aqua::IGameObject* parent)
    : aqua::IGameObject(parent, "SoundManager")
{
}

void CSoundManager::Create(SOUND_ID id, bool loop)
{
	//サウンドの生成
	ISound* sound = nullptr;
	switch (id)
	{
	case SOUND_ID::BATTLE_BGM:
		sound = aqua::CreateGameObject<CBgm>(this);	break;
	case SOUND_ID::ENEMY_HIT:
		sound = aqua::CreateGameObject<CEnemyHitSound>(this);	break;
	case SOUND_ID::WALL_HIT:
		sound = aqua::CreateGameObject<CWallHitSound>(this);	break;
	case SOUND_ID::BALL_SHOT:
		sound = aqua::CreateGameObject<CShotSound>(this);	break;
	case SOUND_ID::CLEAR_BGM:
		sound = aqua::CreateGameObject<CClearBgm>(this);	break;
	case SOUND_ID::BLOCK_ROATATE:
		sound = aqua::CreateGameObject<CBlockRoatateSound>(this);	break;
	case SOUND_ID::BLOCK_CREATE:
		sound = aqua::CreateGameObject<CBlockCreateSound>(this);	break;
	default:
		break;
	}
	if (sound)
		sound->Initialize(loop);
}
