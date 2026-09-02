#pragma once
#include"..\sound.h"

class CClearBgm
	: public ISound
{
public:
	CClearBgm(aqua::IGameObject* parent);
	~CClearBgm(void) = default;
	void Initialize(bool loop) override;
};