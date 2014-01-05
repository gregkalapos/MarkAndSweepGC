#pragma once
#include "GObject.h"
#include "Student.h"

class StudentNode: public GObject
{

	Student* _student;
	StudentNode* _next;


public:
	StudentNode();
	~StudentNode();

	Student* GetStudent();
	void SetStudent(Student* Student);

	StudentNode* GetNext();
	void SetNext(StudentNode* Next);
};

