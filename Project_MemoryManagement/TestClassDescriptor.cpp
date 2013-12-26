#pragma once

#include "TypeDescriptorBase.h"
#include <vector>

struct TestClassDescriptor: public TypeDescriptorBae
{

public:
	
	TestClassDescriptor()
	{
		_offsetList = new std::vector<int>();
		_offsetList->push_back(sizeof(int));
	}


	/*
	TestClassDescriptor();
	~TestClassDescriptor();*/
};

