#pragma once

#include "GObject.h"
#include <string>

class Lecture: public GObject
{

private: 
	int _id;
	std::string _name;
	int _semester;
	
public:
	Lecture();
	~Lecture();

	int GetId();
	void SetId(int Id);

	std::string GetName();
	void SetName(std::string Name);

	int GetSemester();
	void SetSemester(int Semester);
};

