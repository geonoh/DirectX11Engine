#pragma once

template<typename T, UINT _Size>
void Safe_Del_Array(T* (&Array)[_Size])
{
	for (int i = 0; i < _Size; ++i)
	{
		if (Array[i])
		{
			delete Array[i];
			Array[i] = nullptr;
		}
	}
}