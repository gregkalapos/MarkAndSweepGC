#pragma once

#include "TypeDescriptorBase.h"
#include <vector>
#include "Lecture.h"

struct LectureTypeDescriptor : public TypeDescriptorBase
{

public:

	LectureTypeDescriptor() :TypeDescriptorBase("Lecture")
	{
		_offsetList = new std::vector<int>();
		_size = sizeof(Lecture);
	}
	
	/*
	TestClassDescriptor();
	~TestClassDescriptor();*/
};

