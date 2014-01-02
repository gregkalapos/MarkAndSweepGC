#pragma once

#include "TypeDescriptorBase.h"
#include <vector>
#include "LectureNode.h"

struct LectureNodeTypeDescriptor : public TypeDescriptorBase
{

public:

	LectureNodeTypeDescriptor() :TypeDescriptorBase("LectureNode")
	{
		_offsetList = new std::vector<int>();

		_offsetList->push_back(0);
		_offsetList->push_back(sizeof(LectureNode*));
		
		_size = sizeof(LectureNode);
	}
};

