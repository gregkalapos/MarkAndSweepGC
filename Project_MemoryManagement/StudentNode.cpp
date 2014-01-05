#include "StudentNode.h"


StudentNode::StudentNode()
{
}


StudentNode::~StudentNode()
{
}



Student* StudentNode::GetStudent()
{
	return _student;
}

void StudentNode::SetStudent(Student* Student)
{
	_student = Student;
}

StudentNode* StudentNode::GetNext()
{
	return _next;
}

void StudentNode::SetNext(StudentNode* Next)
{
	_next = Next;
}