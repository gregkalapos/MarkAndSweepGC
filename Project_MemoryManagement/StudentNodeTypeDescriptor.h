#pragma once

#include "TypeDescriptorBase.h"
#include <vector>
#include "Student.h"
#include "StudentNode.h"

struct StudentNodeTypeDescriptor : public TypeDescriptorBase
{

public:

	StudentNodeTypeDescriptor() :TypeDescriptorBase("StudentNode")
	{
		_offsetList = new std::vector<int>();

		_offsetList->push_back(0);
		_offsetList->push_back(sizeof(Student*));

		_size = sizeof(StudentNode);
	}


	/*
	TestClassDescriptor();
	~TestClassDescriptor();*/
};

