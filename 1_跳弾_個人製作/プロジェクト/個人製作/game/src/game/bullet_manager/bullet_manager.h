#pragma once
#include"aqua.h"
#include"bullet/bullet.h"
#include"..\block_manager\block_id.h"


class CBlockManager;

class CBulletManager
	:public aqua::IGameObject
{
public:
	CBulletManager(aqua::IGameObject* parent);
	~CBulletManager() = default;
	void Initialize()override;
	void Update()override;
	//’e‚ÌÁ‹
	void Delete();		
	void Create(const aqua::CVector2& position,int bounce);
	//’e‚ÌƒXƒe[ƒ^ƒX‚ğ“ü‚ê‚é
	void Set_ShotStatus(const aqua::CVector2& position, float angle, float speed);		
	//’e‚Ì’†S“_‚Ìæ“¾
	aqua::CVector2 GetCenterPosition();		
	//’e‚Ì”¼Œa‚Ìæ“¾
	float GetRadius();			
	//’e‚ÌƒTƒCƒY‚Ìæ“¾
	float GetSize();
	//’e‚ª‘¶İ‚·‚é‚©‚Ì”»’è		
	bool ActiveCheck(void);																						//’e‚ª‘¶İ‚·‚é‚©Šm”F
	int GetBounceCount(void);																					//’e‚Ì’µ‚Ë•Ô‚è”‚Ìæ“¾
private:
	CBlockManager* m_BlockManager;
	CBullet* m_Bullet;
};