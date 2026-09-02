#include "collision.h"

bool Collision::AABB(aqua::CVector2 position1, aqua::CVector2 size1, aqua::CVector2 position2, aqua::CVector2 size2)
{
	if (position1.x <= position2.x + size2.x && position1.x + size1.x >= position2.x
		&& position1.y <= position2.y + size2.y && position1.y + size1.y >= position2.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}
