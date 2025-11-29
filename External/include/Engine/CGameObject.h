#pragma once
#include "CEntity.h"

class CTransform;
class CMeshRender;
class CRenderComponent;
class CComponent;

class CGameObject : public CEntity
{
	CComponent* Components[static_cast<UINT>(EComponentType::End)];
	CRenderComponent* RenderComponent;

public:
	void Begin(); // 레벨이 시작될 때 호출, 레벨에 합류할 때
	void Tick(); // 매 프레임마다 호출, DT 동안 할 일을 구현
	void FinalTick(); // tick에서 발생한 일들의 마무리 작업 or 리소스 바인딩 및 관련 데이터 연산
	void Render(); // 화면에 그려지는 함수

	void AddComponent(CComponent* Component);
	CComponent* GetComponent(EComponentType _Type) const;

	CTransform* Transform() const;
	CMeshRender* MeshRender() const;

	CGameObject();
	virtual ~CGameObject() override;
};
