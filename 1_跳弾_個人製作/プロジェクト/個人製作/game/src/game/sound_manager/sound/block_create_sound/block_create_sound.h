#pragma once
#include"..\sound.h"

class CBlockCreateSound
	: public ISound
{
public:
	CBlockCreateSound(aqua::IGameObject* parent);
	~CBlockCreateSound(void) = default;
	void Initialize(bool loop) override;
};