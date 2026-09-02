#pragma once
#include"chara/chara.h"
#include"..\bullet_manager\bullet_manager.h"

class CEffectManager;

class CCharaManager
	:public aqua::IGameObject
{
public:
	CCharaManager(aqua::IGameObject* parent);
	~CCharaManager() = default;
	void Initialize()override;
	void Update()override;
	void Create(const aqua::CVector2& position);
	//ƒLƒƒƒ‰‚ÌÁ‹
	void Delete();		
	//“–‚½‚è”»’è
	void Hit();					
	//ƒLƒƒƒ‰‚Ì”‚ª0‚É‚È‚Á‚½‚çtrue‚ğ•Ô‚·
	bool CharaExist();			
private:
	CBulletManager* m_BulletManager;
	CEffectManager* m_EffectManager;
};	
