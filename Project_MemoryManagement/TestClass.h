#pragma once
#include "GObject.h"

class TestClass: public GObject
{
public:
	int intField;
	TestClass* tp;
	TestClass();
	~TestClass();
};

