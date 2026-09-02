#pragma once
#include"..\sound.h"

class CWallHitSound
	: public ISound
{
public:
	CWallHitSound(aqua::IGameObject* parent);
	~CWallHitSound(void) = default;
	void Initialize(bool loop) override;
};