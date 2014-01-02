#pragma once
#include "StudentNode.h"
#include "GObject.h"

class StudentList: public GObject
{

private: 
	StudentNode* _first;

public:
	StudentList(StudentNode* First);
	~StudentList();

	StudentNode* GetFirst();

};

