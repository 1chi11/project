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
	aqua::CSprite m_Sprite;     //タイトルのスプライト
};
