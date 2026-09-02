#pragma once
#include"..\sound.h"

class CEnemyHitSound
	: public ISound
{
public:
	CEnemyHitSound(aqua::IGameObject* parent);
	~CEnemyHitSound(void) = default;
	void Initialize(bool loop) override;
};