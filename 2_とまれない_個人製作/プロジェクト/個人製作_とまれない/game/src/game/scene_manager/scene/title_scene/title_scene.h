#pragma once
#include "aqua.h"
#include "..\scene.h"

class CTitleScene
    : public IScene
{
public:
    CTitleScene(aqua::IGameObject* parent);
    ~CTitleScene(void) = default;
    void        Initialize(void) override;
    void        Update(void) override;
    void        Draw(void) override;
    void        Finalize(void) override;

private:
	static const aqua::CVector2 m_label_position; //タイトルのラベル位置
	static const int m_label_size;        //タイトルのラベルサイズ
	aqua::CSprite m_Sprite;     //タイトルのスプライト
	aqua::CLabel m_Label;       //タイトルのラベル
};
