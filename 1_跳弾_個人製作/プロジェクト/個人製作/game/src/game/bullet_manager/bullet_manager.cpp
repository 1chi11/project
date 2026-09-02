#include "bullet_manager.h"
#include"bullet/bullet.h"
#include"..\block_manager\block_manager.h"
#include"..\effect_manager\effect_manager.h"

CBulletManager::CBulletManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "BulletManager", "Manager")
	, m_Bullet(nullptr)
	, m_BlockManager(nullptr)
{
}

void CBulletManager::Create(const aqua::CVector2& position,int bounce)
{
	//弾の生成
	if(!m_Bullet)
	m_Bullet = aqua::CreateGameObject<CBullet>(this);
	if (!m_Bullet)return;
	m_Bullet->Initialize(position, bounce);
}

void CBulletManager::Set_ShotStatus(const aqua::CVector2& position, float angle, float speed)
{
	//弾のステータスをセット
	if (!m_Bullet)
		return;
	else
		return m_Bullet->Set_ShotStatus(position, angle, speed);
}


aqua::CVector2 CBulletManager::GetCenterPosition()
{
	if (!m_Bullet)
	return aqua::CVector2 (0.0f,0.0f);
	return 	m_Bullet->GetCenterPosition();
}

void CBulletManager::Initialize()
{
	m_BlockManager = (CBlockManager*)aqua::FindGameObject("BlockManager");
}

void CBulletManager::Update()
{
	if (!m_BlockManager || !m_Bullet)return;

	//弾とオブジェクトの当たり判定
	aqua::CVector2 center = m_Bullet->GetCenterPosition();
	float radius = m_Bullet->GetRadius();
	IBlock* block = m_BlockManager->BlockHitRotated(center, radius);
	if (block)
	{
		m_Bullet->HitMove(block);
	}
	IGameObject::Update();
}
void CBulletManager::Delete()
{
	if (!m_Bullet)return;
	m_Bullet->Finalize();
	m_Bullet = nullptr;
}
float CBulletManager::GetRadius()
{

	if (!m_Bullet)
		return 0.0f;

	return 	m_Bullet->GetRadius();
}

float CBulletManager::GetSize()
{
	if (!m_Bullet)
		return 0.0f;

	return 	m_Bullet->GetSize();
}


bool CBulletManager::ActiveCheck(void)
{
	if (!m_Bullet)
		return false;
	else
		return m_Bullet->GetActive();
}

int CBulletManager::GetBounceCount(void)
{
	if (!m_Bullet)
		return 0;
	else
		return m_Bullet->GetBounceCount();
}
