#pragma once



#pragma once

#include "aqua.h"
#include "..\scene.h"
#include"..\game_main_scene\game_main_scene.h"
#include"..\..\..\score_manager\score_manager.h"
 
class CResultScene
    : public IScene
{
public:
    
    CResultScene(aqua::IGameObject* parent);
    ~CResultScene(void) ;
    void        Initialize(void) override;
    void        Update(void) override;
    void        Draw(void) override;
    void        Finalize()override;

private:
    static const float  m_wait_time;            //! 待機時間
	static const float  m_score_size;            //! スコアのサイズ
	int m_StageCount;                               //!クリアステージの数

    aqua::CSprite       m_Sprite;
	aqua::CLabel        m_ThrowCountLabel[10];      //投げた回数ラベル
	aqua::CSprite      m_ScoreOneDigit[10];           //スコアのスプライト
	aqua::CSprite      m_ScoreTwoDigit[10];           //スコアのスプライト
};
