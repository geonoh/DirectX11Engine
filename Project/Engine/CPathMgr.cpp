#include "pch.h"
#include "CPathMgr.h"

CPathMgr::CPathMgr()
{
}

CPathMgr::~CPathMgr()
{
}


void CPathMgr::Init()
{
	GetCurrentDirectory(255, ContentPath);
	const size_t Len = wcslen(ContentPath);

	// 하나의 디렉토리 앞 폴더로 이동
	for (int i = Len - 1; i > 0; --i)
	{
		if (ContentPath[i] == '\\')
		{
			ContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(ContentPath, L"\\content\\");
}

const wchar_t* CPathMgr::GetContentPath() const
{
	return ContentPath;
}
