#pragma once

#include "TypeDescriptorBase.h"
#include <vector>
#include "Student.h"

struct StudentTypeDescriptor : public TypeDescriptorBase
{

public:

	StudentTypeDescriptor() :TypeDescriptorBase("Student")
	{
		_offsetList = new std::vector<int>();
		_offsetList->push_back( ((sizeof(int) + sizeof(std::string))) );

		_size = sizeof(Student);
	}


	/*
	TestClassDescriptor();
	~TestClassDescriptor();*/
};

