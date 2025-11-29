#include "pch.h"
#include "CGameObject.h"

#include "CComponent.h"
#include "CMeshRender.h"
#include "CRenderComponent.h"
#include "CTransform.h"

void CGameObject::Begin()
{
	for (CComponent* Component : Components)
	{
		if (!Component)
		{
			continue;
		}
		Component->Begin();
	}
}

void CGameObject::Tick()
{
	for (CComponent* Component : Components)
	{
		if (!Component)
		{
			continue;
		}
		Component->Tick();
	}
}

void CGameObject::FinalTick()
{
	for (CComponent* Component : Components)
	{
		if (!Component)
		{
			continue;
		}
		Component->FinalTick();
	}
}

void CGameObject::Render()
{
	if (!RenderComponent)
	{
		return;
	}

	RenderComponent->Render();
}

void CGameObject::AddComponent(CComponent* Component)
{
	// 입력으로 들어온 컴포넌트의 타입을 확인한다.
	const EComponentType type = Component->GetComponentType();

	// 입력으로 들어온 컴포넌트를 이미 가지고 있는 경우
	assert(!Components[static_cast<UINT>(type)]);

	// 입력된 컴포넌트가 렌더링 관련 컴포넌트인지 확인 
	CRenderComponent* NewRenderComponent = dynamic_cast<CRenderComponent*>(Component);
	if (NewRenderComponent)
	{
		// 이미 렌더링 관련 컴포넌트를 보유한 경우
		assert(!RenderComponent);

		// 렌더링 관련 컴포넌트라면 멤버 변수에 별도 기록
		RenderComponent = NewRenderComponent;
	}

	// 입력된 컴포넌트를 배열의 알맞은 인덱스 자리에 주소값을 기록한다.
	Components[static_cast<UINT>(type)] = Component;

	// 컴포넌트의 소유 오브젝트가 본인임을 알림
	Component->Owner = this;
}

CComponent* CGameObject::GetComponent(EComponentType _Type) const
{
	return Components[static_cast<UINT>(_Type)];
}

CTransform* CGameObject::Transform() const
{
	return dynamic_cast<CTransform*>(Components[static_cast<UINT>(EComponentType::Transform)]);
}

CMeshRender* CGameObject::MeshRender() const
{
	return dynamic_cast<CMeshRender*>(Components[static_cast<UINT>(EComponentType::MeshRender)]);
}

CGameObject::CGameObject() : Components{}, RenderComponent(nullptr)
{
}

CGameObject::~CGameObject()
{
	Safe_Del_Array(Components);
}
