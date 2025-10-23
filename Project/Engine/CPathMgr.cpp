#include "pch.h"
#include "CPathMgr.h"

CPathMgr::CPathMgr()
{
	
}

CPathMgr::~CPathMgr()
{
	
}


void CPathMgr::init()
{
	GetCurrentDirectory(255, m_szContentPath);
	size_t len = wcslen(m_szContentPath);

	// �ϳ��� ���丮 �� ������ �̵�
	for (int i = len - 1; i > 0; --i)
	{
		if (m_szContentPath[i] == '\\')
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, L"\\content\\");
}

const wchar_t* CPathMgr::GetContentPath() const
{
	return m_szContentPath;
}
