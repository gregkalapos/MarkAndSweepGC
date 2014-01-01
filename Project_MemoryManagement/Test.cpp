//#include <iostream>
//#include "Heap.h"
//#include "TestClass.h"
//#include "TestClassDescriptor.cpp"
//
//
//
//void InitHeapWithDescriptors()
//{
//	Heap::initHeap();
//	TestClassDescriptor* descriptor = new TestClassDescriptor(sizeof(TestClass), "TestClass");
//	Heap::registerType(descriptor->GetClassName(), descriptor);
//}
//
//int main()
//{
//	
//	InitHeapWithDescriptors();
//
////	void* aa = Heap::alloc("dsf");
//	//std::cout << aa;
//
////	std::cout << "char: " << sizeof(char) << endl;
//	//std::cout << sizeof(int) << endl;
//	//std::cout << sizeof(bool) << endl;
//	
//	
////	auto ro = (TestClass*)Heap::addTestObj();
////	ro->intField = 3;
//	
//	Heap::dump();
//	
//	
//	auto ro = (TestClass*)Heap::alloc("TestClass");
//
//	ro->intField = 33;
//	ro->tp = ro;
//
//	auto r2 = (TestClass*)Heap::alloc("TestClass");
//	r2->intField = 11;
//	r2->tp = ro;
//
//	
//	ro->intField = 3;
//	
//	
//	Heap::dump();
//
//	std::vector<GObject*> roots;
//	
//	roots.push_back(ro);
//	//roots.push_back();
//	
//	//Heap::gc(roots);
//
//	Heap::dump();
//
//	Heap::gc(roots);
//	Heap::dump();
//
//
//	roots.clear();
//	Heap::gc(roots);
//
//	Heap::dump();
//
//	std::cin.get();
//}
//
