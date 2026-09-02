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
    ~CResultScene(void) = default ;
    void        Initialize(void) override;
    void        Update(void) override;
    void        Draw(void) override;
    void        Finalize()override;
private:
    static const aqua::CVector2 m_label_position; //リザルトのラベル位置
    static const int m_label_size;        //リザルトのラベルサイズ
	aqua::CSprite m_Sprite;     //リザルトのスプライト
	aqua::CLabel m_Label;       //リザルトのラベル
};
