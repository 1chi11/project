#pragma once
#include"..\sound.h"

class CObjectRoatateSound
	: public ISound
{
public:
	CObjectRoatateSound(aqua::IGameObject* parent);
	~CObjectRoatateSound(void) = default;
	void Initialize(bool loop) override;
};