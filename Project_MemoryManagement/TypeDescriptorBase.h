#pragma once

#include <vector>

struct TypeDescriptorBase
{
protected:
	int _size;
	///Stores the offset for every pointer in the class. Offset of the first pointer is offset OffsetList[0] etc...
	std::vector<int>*  _offsetList;

	std::string _className; //Stores the name of the class

public:
	std::vector<int>* GetOffsetList()
	{
		return _offsetList;
	}

	int GetObjectSize()
	{
		return _size;
	}

	std::string GetClassName()
	{
		return _className;
	}

	TypeDescriptorBase()
	{}

	TypeDescriptorBase(int Size, std::string CName) : _size(Size), _className(CName)
	{
		
	}
}; 