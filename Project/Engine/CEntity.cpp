#include "pch.h"
#include "CEntity.h"

UINT CEntity::NextId = 0;

CEntity::CEntity() : Id(NextId++)
{
}

CEntity::CEntity(const CEntity& Origin) : Id(NextId++)
{
}

CEntity::~CEntity()
{
}
