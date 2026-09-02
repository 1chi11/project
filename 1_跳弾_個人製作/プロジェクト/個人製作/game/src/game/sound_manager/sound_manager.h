#pragma once
#include"aqua.h"
enum class SOUND_ID
{
    BATTLE_BGM,
	CLEAR_BGM,
    ENEMY_HIT,
    WALL_HIT,
    BALL_SHOT,
	BLOCK_ROATATE,
	BLOCK_CREATE,

    MAX,
};
class CSoundManager
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     */
    CSoundManager(aqua::IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CSoundManager(void) = default;

	void Create(SOUND_ID id,bool loop);
private:
};
