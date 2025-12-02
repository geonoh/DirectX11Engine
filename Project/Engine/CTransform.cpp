#include "pch.h"
#include "CTransform.h"

#include "CConstBuffer.h"
#include "CDevice.h"

void CTransform::FinalTick()
{
}

void CTransform::Binding() const
{
	CConstBuffer* ConstBuffer = CDevice::GetInst()->GetConstBuffer(EConstantBufferType::Transform);
	tTransform trans = {};
	trans.Position = RelativePos;
	trans.Scale = RelativeScale;

	ConstBuffer->SetData(&trans);
	ConstBuffer->Binding();
}

CTransform::CTransform()
	: CComponent(EComponentType::Transform), RelativeScale(1.f, 1.f, 1.f)
{
}

CTransform::~CTransform()
{
}
