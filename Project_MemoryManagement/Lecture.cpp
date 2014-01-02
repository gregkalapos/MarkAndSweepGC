#include "Lecture.h"


Lecture::Lecture()
{
}


Lecture::~Lecture()
{
}


int Lecture::GetId()
{
	return _id;
}


void Lecture::SetId(int Id)
{
	_id = Id;
}

std::string Lecture::GetName()
{
	return _name;
}

void Lecture::SetName(std::string Name)
{
	_name = Name;
}

int Lecture::GetSemester()
{
	return _semester;
}

void Lecture::SetSemester(int Semester)
{
	_semester = Semester;
}
