#include <iostream>
#include "Heap.h"
#include "TestClass.h"
#include "TestClassDescriptor.cpp"



void InitHeapWithDescriptors()
{
	Heap::initHeap();
	TestClassDescriptor descriptor(sizeof(TestClass), "TestClass");
	Heap::registerType(descriptor.GetClassName(), descriptor);
}

int main()
{
	
	InitHeapWithDescriptors();

//	void* aa = Heap::alloc("dsf");
	//std::cout << aa;

//	std::cout << "char: " << sizeof(char) << endl;
	//std::cout << sizeof(int) << endl;
	//std::cout << sizeof(bool) << endl;
	
	
//	auto ro = (TestClass*)Heap::addTestObj();
//	ro->intField = 3;
	
	Heap::dump();
	
	
	auto ro = (TestClass*)Heap::alloc("TestClass");

	ro->intField = 33;
	ro->tp = ro;

	auto r2 = (TestClass*)Heap::alloc("TestClass");
	r2->intField = 11;
	r2->tp = ro;

	r2->tp->intField = 21;

	ro->intField = 3;
	ro->tp = new TestClass();
	
	Heap::dump();

	std::cin.get();
}

