#pragma once

#include "TypeDescriptorBase.h"
#include <vector>
#include "StudentList.h"

struct StudentListTypeDescriptor : public TypeDescriptorBase
{

public:

	StudentListTypeDescriptor() :TypeDescriptorBase("StudentList")
	{
		_offsetList = new std::vector<int>();

		_offsetList->push_back(0);

		_size = sizeof(StudentList);
	}

	/*
	TestClassDescriptor();
	~TestClassDescriptor();*/
};

