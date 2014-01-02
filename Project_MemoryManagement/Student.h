#pragma once

#include "GObject.h"
#include <string>
#include "LectureNode.h"

class Student: public GObject
{
private: 
	int _id;
	std::string _name;
	LectureNode* _lectureNode;

public:
	Student(int Id, std::string Name, LectureNode* LectureNode);
	~Student();

	void Add(Lecture* Lecture);
	void Remove(Lecture* Lecture);
		
};

