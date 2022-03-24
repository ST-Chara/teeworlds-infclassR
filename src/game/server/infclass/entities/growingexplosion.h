/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */

#ifndef GAME_SERVER_ENTITIES_GROWINGEXPLOSION_H
#define GAME_SERVER_ENTITIES_GROWINGEXPLOSION_H

#include "infcentity.h"

#include <game/server/entity.h>
#include <game/server/entities/character.h>

enum class DAMAGE_TYPE;

enum class GROWING_EXPLOSION_EFFECT
{
	INVALID,
	FREEZE_INFECTED,
	POISON_INFECTED,
	ELECTRIC_INFECTED,
	LOVE_INFECTED,
	BOOM_INFECTED,
	HEAL_HUMANS,
	D4C_TP,
	D4C_TP_SELF,
};

class CGrowingExplosion : public CInfCEntity
{
public:
	CGrowingExplosion(CGameContext *pGameContext, vec2 Pos, vec2 Dir, int Owner, int Radius, GROWING_EXPLOSION_EFFECT ExplosionEffect);
	CGrowingExplosion(CGameContext *pGameContext, vec2 Pos, vec2 Dir, int Owner, int Radius, DAMAGE_TYPE DamageType);
	virtual ~CGrowingExplosion();

	virtual void Tick();
	virtual void TickPaused();

	void SetDamage(int Damage);
	void SetDamageType(DAMAGE_TYPE Type);
	int GetActualDamage();

private:
	void ProcessMercenaryBombHit(CInfClassCharacter *pCharacter);

	int m_MaxGrowing;
	int m_GrowingMap_Length;
	int m_GrowingMap_Size;
	DAMAGE_TYPE m_DamageType;
	TAKEDAMAGEMODE m_TakeDamageMode = TAKEDAMAGEMODE::NOINFECTION;
	
	vec2 m_SeedPos;
	int m_SeedX;
	int m_SeedY;
	int m_StartTick;
	int* m_pGrowingMap;
	vec2* m_pGrowingMapVec;
	GROWING_EXPLOSION_EFFECT m_ExplosionEffect = GROWING_EXPLOSION_EFFECT::INVALID;
	bool m_Hit[MAX_CLIENTS];
	int m_Damage = -1;
};

#endif // GAME_SERVER_ENTITIES_GROWINGEXPLOSION_H
