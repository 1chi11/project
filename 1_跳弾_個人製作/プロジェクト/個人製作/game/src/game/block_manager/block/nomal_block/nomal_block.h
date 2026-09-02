#pragma once
#include"..\block.h"
class CNomalBlock :public IBlock
{
public:
	CNomalBlock(aqua::IGameObject* parent);
	~CNomalBlock(void) = default;
	void Initialize(aqua::CVector2 position1, aqua::CVector2 position2, float speed)override;
private:

};