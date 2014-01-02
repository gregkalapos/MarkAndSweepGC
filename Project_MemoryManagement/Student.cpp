#include "Student.h"
#include "LectureNodeTypeDescriptor.h"

Student::Student(int Id, std::string Name, LectureNode* LectureNode)
{
	_id = Id;
	_name = Name;
	_lectureNode = LectureNode;
}


Student::~Student()
{
}

void Student::Add(Lecture* Lecture)
{
	auto newLectureNode = (LectureNode*)Heap::alloc("LectureNode");
	
	newLectureNode->SetLecture(Lecture);
	
	auto cln = _lectureNode;

	if (cln == NULL)
	{
		_lectureNode = newLectureNode;
	}
	else
	{

		while (cln->GetNext() != NULL)
		{
			cln = cln->GetNext();
		}

		cln->SetNext(newLectureNode);
	}
}

void Student::Remove(Lecture* Lecture)
{
	auto itemToRemove = _lectureNode;
	LectureNode* prevItem = NULL;


	while (itemToRemove->GetLecture() != Lecture)
	{
		prevItem = itemToRemove;
		itemToRemove = itemToRemove->GetNext();
	}

	if (prevItem == NULL)
	{
		if (_lectureNode != NULL)
		{
			_lectureNode = _lectureNode->GetNext();
		}
		else
		{
			_lectureNode = NULL;
		}
	}
	else
	{
		prevItem->SetNext(itemToRemove->GetNext());
	}
}