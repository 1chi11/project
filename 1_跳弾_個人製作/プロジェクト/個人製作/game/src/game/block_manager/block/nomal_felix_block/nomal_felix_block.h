#pragma once
#include"..\block.h"

class CNomalFelixBlock :public IBlock
{
public:
	CNomalFelixBlock(aqua::IGameObject* parent);
	~CNomalFelixBlock(void) = default;
	void Initialize(aqua::CVector2 position1, aqua::CVector2 position2, float speed)override;
private:
};