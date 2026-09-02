#include"effect_manager.h"
#include"effect/effect.h"
#include"effect/block_clash/block_clash.h"
#include"effect/character_hit/character_hit.h"
#include"..\game_object\character_manager\character_manager.h"

/*
 *  コンストラクタ
 */
CEffectManager::
CEffectManager(aqua::IGameObject* parent)
    : aqua::IGameObject(parent, "EffectManager")
{
}

void CEffectManager::Draw(void)
{
    CCharacterManager* cm = (CCharacterManager*)aqua::FindGameObject("CharacterManager");
    if (!cm)
        return;
    for (auto it : m_ChildObjectList)
    {
        IEffect* effect = (IEffect*)it;
        if(effect->GetGameObjectState()!= aqua::GAME_OBJECT_STATE::DEAD)
        effect->Draw(cm->GetPlayerTravelDistance());
    }
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
    case EFFECT_ID::BLOCK_CLASH_EFFECT:
        effect = (IEffect*)aqua::CreateGameObject<CBlockClash>(this);
        break;
    case EFFECT_ID::CHARACTER_HIT_EFFECT:
        effect = (IEffect*)aqua::CreateGameObject<CCharacterHit>(this);
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

void CEffectManager::SetTimeSpeed(float speed)
{
    for (auto it : m_ChildObjectList)
    {
        IEffect* effect = (IEffect*)it;
        effect->SetTimeSpeed(speed);
    }

}

