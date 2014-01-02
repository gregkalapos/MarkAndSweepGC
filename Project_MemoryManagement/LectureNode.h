#pragma once

#include "Lecture.h"
#include "GObject.h"

class LectureNode: public GObject
{
	LectureNode* _next;
	Lecture* _lecture;

public:
	LectureNode();
	~LectureNode();

	Lecture* GetLecture();
	void SetLecture(Lecture* Lecture);

	LectureNode* GetNext();
	void SetNext(LectureNode* Next);
};

