#pragma once
#include"..\sound.h"

class CBlockRoatateSound
	: public ISound
{
public:
	CBlockRoatateSound(aqua::IGameObject* parent);
	~CBlockRoatateSound(void) = default;
	void Initialize(bool loop) override;
};