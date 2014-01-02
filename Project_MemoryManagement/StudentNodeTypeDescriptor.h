#pragma once

#include "TypeDescriptorBase.h"
#include <vector>

struct StudentNodeTypeDescriptor : public TypeDescriptorBase
{

public:

	StudentNodeTypeDescriptor(int Size, std::string CName) :TypeDescriptorBase(Size, CName)
	{
		_offsetList = new std::vector<int>();
		//_offsetList->push_back(sizeof(int)); //TODO
	}


	/*
	TestClassDescriptor();
	~TestClassDescriptor();*/
};

