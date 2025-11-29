#pragma once
class CEntity
{
	static UINT NextId;

	wstring Name;
	UINT Id;

public:
	const wstring& GetName() const { return Name; }
	void SetName(const wstring& InName) { Name = InName; }
	UINT GetId() const { return Id; }

	//// 자기 자신을 복제한 객체를 반환
	//virtual CEntity* Clone() = 0;

	CEntity();
	CEntity(const CEntity& Origin);
	virtual ~CEntity();
};
