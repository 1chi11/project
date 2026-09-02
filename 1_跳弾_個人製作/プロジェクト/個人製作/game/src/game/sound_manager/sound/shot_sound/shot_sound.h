#pragma once
#include"..\sound.h"

class CShotSound
	: public ISound
{
public:
	CShotSound(aqua::IGameObject* parent);
	~CShotSound(void) = default;
	void Initialize(bool loop) override;
};