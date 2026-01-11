#pragma once
#include "CComponent.h"

class CCamera : public CComponent
{
public:
	CCamera();
	virtual ~CCamera() override;
	virtual void FinalTick() override;
	void Render();

	void SetPriority(int InPriority);

private:
	int Priority = INVALID_CAMERA_PRIORITY; // RenderMgr에 등록될 때 우선순위(0 : 메인 카메라, 0보다 큰 경우 : 서브 카메라)

	float FarValue = 1000.f; // Depth Stencil을 1을 최대로 했으므로, 1000에 가까울수록 depthStencil은 1로 판단
	Matrix ViewMatrix;
	Matrix ProjectionMatrix;

	static constexpr int INVALID_CAMERA_PRIORITY = -1; // 아직 렌더러 매니저에 등록되지 않은 카메라
};

