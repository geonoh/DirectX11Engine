#include "pch.h"
#include "CTransform.h"

#include "CConstBuffer.h"
#include "CDevice.h"

void CTransform::finaltick()
{
}

void CTransform::Binding()
{
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	tTransform trans = {};
	trans.Position = m_RelativePos;
	trans.Scale = m_RelativeScale;

	pCB->SetData(&trans);
	pCB->Binding();
}

CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM), m_RelativeScale(1.f, 1.f, 1.f)
{
}

CTransform::~CTransform()
{
}
