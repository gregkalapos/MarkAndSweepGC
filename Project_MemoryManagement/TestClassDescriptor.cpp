#pragma once

#include "TypeDescriptorBase.h"
#include <vector>

struct TestClassDescriptor: public TypeDescriptorBase
{

public:
	
	TestClassDescriptor(int Size, std::string CName):TypeDescriptorBase(Size, CName)
	{
		_offsetList = new std::vector<int>();
		_offsetList->push_back(sizeof(int));
	}


	/*
	TestClassDescriptor();
	~TestClassDescriptor();*/
};

