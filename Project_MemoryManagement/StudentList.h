#pragma once
#include "StudentNode.h"
#include "GObject.h"

class StudentList: public GObject
{

private: 
	StudentNode* _first;

public:
	StudentList();
	~StudentList();

	void Add(Student* Student);
	void Remove(Student* Student);
};

