#include "pch.h"
#include "CGameObject.h"

#include "CComponent.h"
#include "CMeshRender.h"
#include "CRenderComponent.h"
#include "CTransform.h"

void CGameObject::begin()
{
	for (CComponent* pComponent : m_arrCom)
	{
		if (!pComponent)
		{
			continue;
		}
		pComponent->begin();
	}
}

void CGameObject::tick()
{
	for (CComponent* pComponent : m_arrCom)
	{
		if (!pComponent)
		{
			continue;
		}
		pComponent->tick();
	}
}

void CGameObject::finaltick()
{
	for (CComponent* pComponent : m_arrCom)
	{
		if (!pComponent)
		{
			continue;
		}
		pComponent->finaltick();
	}
}

void CGameObject::render()
{
	if (m_RenderCom)
	{
		m_RenderCom->render();
	}
}

void CGameObject::AddComponent(CComponent* _Component)
{
	// 입력으로 들어온 컴포넌트의 타입을 확인한다.
	const COMPONENT_TYPE type = _Component->GetComponentType();

	// 입력으로 들어온 컴포넌트를 이미 가지고 있는 경우
	assert(!m_arrCom[static_cast<UINT>(type)]);

	// 입력된 컴포넌트가 렌더링 관련 컴포넌트인지 확인 
	CRenderComponent* pRenderCom = dynamic_cast<CRenderComponent*>(_Component);
	if (pRenderCom)
	{
		// 이미 렌더링 관련 컴포넌트를 보유한 경우
		assert(!m_RenderCom);

		// 렌더링 관련 컴포넌트라면 멤버 변수에 별도 기록
		m_RenderCom = pRenderCom;
	}

	// 입력된 컴포넌트를 배열의 알맞은 인덱스 자리에 주소값을 기록한다.
	m_arrCom[static_cast<UINT>(type)] = _Component;

	// 컴포넌트의 소유 오브젝트가 본인임을 알림
	_Component->m_Owner = this;
}

CComponent* CGameObject::GetComponent(COMPONENT_TYPE _Type) const
{
	return m_arrCom[static_cast<UINT>(_Type)];
}

CTransform* CGameObject::Transform() const
{
	return dynamic_cast<CTransform*>(m_arrCom[static_cast<UINT>(COMPONENT_TYPE::TRANSFORM)]);
}

CMeshRender* CGameObject::MeshRender() const
{
	return dynamic_cast<CMeshRender*>(m_arrCom[static_cast<UINT>(COMPONENT_TYPE::MESHRENDER)]);
}

CGameObject::CGameObject() : m_arrCom{}, m_RenderCom(nullptr)
{
}

CGameObject::~CGameObject()
{
	Safe_Del_Array(m_arrCom);
}
