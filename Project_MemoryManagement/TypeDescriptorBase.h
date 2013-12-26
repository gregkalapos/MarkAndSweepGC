#pragma once

#include <vector>

struct TypeDescriptorBae
{
protected:
	int _size;
	///Stores the offset for every pointer in the class. Offset of the first pointer is offset OffsetList[0] etc...
	std::vector<int>*  _offsetList;

public:

	std::vector<int>* GetOffsetList()
	{
		return _offsetList;
	}

	int GetObjectSize()
	{
		return _size;
	}
}; 