#include "LectureNode.h"


LectureNode::~LectureNode()
{
	
}

LectureNode::LectureNode()
{
}

Lecture* LectureNode::GetLecture()
{
	return _lecture;
}

void LectureNode::SetLecture(Lecture* Lecture)
{
	_lecture = Lecture;
}

LectureNode* LectureNode::GetNext()
{
	return _next;
}

void LectureNode::SetNext(LectureNode* Next)
{
	_next = Next;
}