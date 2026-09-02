#include "effect_manager.h"
#include"effect/effect.h"
#include"effect/enemy_hit/enemy_hit.h"
#include"effect/wall_hit/wall_hit.h"
#include"effect/shot_cursor/shot_cursor.h"
#include"..\sound_manager\sound_manager.h"

/*
 *  コンストラクタ
 */
CEffectManager::
CEffectManager(aqua::IGameObject* parent)
    : aqua::IGameObject(parent, "EffectManager")
{
}

/*
 *  生成
 */
void
CEffectManager::
Create(EFFECT_ID id, const aqua::CVector2& position)
{
	//エフェクトの生成
    IEffect* effect = nullptr;
    switch (id)
    {
    case EFFECT_ID::ENEMY_HIT_EFFECT:    effect = aqua::CreateGameObject<CEnemyEffect>(this);
        break;
    case EFFECT_ID::WALL_HIT_EFFECT:   effect = aqua::CreateGameObject<CWallEffect>(this);  
         break;
    case EFFECT_ID::SHOT_CURSOR_EFFECT:   effect = aqua::CreateGameObject<CShotCursorEffect>(this);   
        break;
    }

    if (effect)
        effect->Initialize(position);
}

void CEffectManager::Delete()
{
  for (auto it : m_ChildObjectList)
    {
      IEffect* effect = (IEffect*)it;
          effect->Finalize();
    }
  }

