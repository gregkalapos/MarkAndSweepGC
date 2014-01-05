#include "StudentList.h"



void StudentList::Add(Student* Student)
{
	auto newStudentNode = (StudentNode*) Heap::alloc("StudentNode");

	newStudentNode->SetStudent(Student);

	auto cs = _first;

	if (cs == NULL)
	{
		_first = newStudentNode;
	}
	else
	{
		while (cs->GetNext() != NULL)
		{
			cs = cs->GetNext();
		}

		cs->SetNext(newStudentNode);
	}
}


void StudentList::Remove(Student* Student)
{
	auto itemToRemove = _first;
	StudentNode* prevItem = NULL;
	
	while (itemToRemove->GetStudent() != Student)
	{
		prevItem = itemToRemove;
		itemToRemove = itemToRemove->GetNext();
	}

	if (prevItem == NULL)
	{
		if (_first != NULL)
		{
			_first = _first->GetNext();
		}
		else
		{
			_first = NULL;
		}
	}
	else
	{
		prevItem->SetNext(itemToRemove->GetNext());
	}
}



StudentList::StudentList()
{
}


StudentList::~StudentList()
{
}
