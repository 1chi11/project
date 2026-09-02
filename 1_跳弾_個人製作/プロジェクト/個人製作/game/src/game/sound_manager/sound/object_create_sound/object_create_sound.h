#pragma once
#include"..\sound.h"

class CObjectCreateSound
	: public ISound
{
public:
	CObjectCreateSound(aqua::IGameObject* parent);
	~CObjectCreateSound(void) = default;
	void Initialize(bool loop) override;
};