#pragma once
#include"..\sound.h"

class CBgm
	: public ISound
{
public:
	CBgm(aqua::IGameObject* parent);
	~CBgm(void) = default;
	void Initialize(bool loop) override;
};