#pragma once
#include "Heap.h"

#include "TypeDescriptorBase.h"

class GObject
{
private:
	TypeDescriptorBae* _tag; //pointer to the typedescriptor
	int _mark;
	int _free;
	friend Heap;

public:
	GObject()
	{
		_mark = 0;
		_free = 0;

		_tag = NULL;
	}
};