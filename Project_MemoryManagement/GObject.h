#pragma once

#include "Heap.h"
#include "TypeDescriptorBase.h"

//The base class for every garbage collected class.
class GObject
{
private:
	TypeDescriptorBase* _tag; //pointer to the typedescriptor
	int _mark;
	int _free;

public:
	friend class Heap;
	GObject()
	{
		_mark = 0;
		_free = 0;
		_tag = NULL;
	}
};