#pragma once
#include "aqua.h"
#include"effect_id.h"

class CEffectManager
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     */
    CEffectManager(aqua::IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CEffectManager(void) = default;

    /*!
     *  @brief      エフェクト生成
     *
     *  @param[in]  id          エフェクトID
     *  @param[in]  position    位置
     */
    void        Create(EFFECT_ID id, const aqua::CVector2& position);
   
    /*!
    *  @brief      エフェクト消去
    *
    */
    void        Delete();
};
