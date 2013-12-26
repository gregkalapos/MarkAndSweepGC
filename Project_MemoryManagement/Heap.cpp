#include "Heap.h"
#include <iostream>
#include "TestClass.h"
#include "TestClassDescriptor.cpp"

void* Heap::_listStart = malloc(Heap::LISTSIZE);
FreeBlock* Heap::_firstFree;
map<std::string, TypeDescriptorBae>  Heap::_descriptors;
//map<std::string, TypeDescriptorBae*> Heap::_descriptors = new map<std::string, TypeDescriptorBae*>();


Heap::Heap()
{
}


Heap::~Heap()
{
}



void* Heap::alloc(std::string cName)
{		
	//_firstFree = _listStart;

	return _listStart;
}

void* Heap::addTestObj()
{
	auto retObject = (TestClass*)Alloc(sizeof(TestClass));
	retObject->_free = 0;
	retObject->_mark = 0;

	auto tcdesc = _descriptors["TestClassDescriptor"];

	retObject->_tag = &tcdesc;

	return retObject;
}


void Heap::initHeap()
{	
	TestClassDescriptor d;
	std::string s("TestClassDescriptor");
	_descriptors.insert(std::pair<std::string, TypeDescriptorBae>(s, d));

	FreeBlock fb;
	
	auto blockInfoSize = sizeof(fb.lfb) + sizeof(fb.length) + sizeof(fb.next);
	fb.length = Heap::LISTSIZE - blockInfoSize;
	
	fb.next = (FreeBlock*)_listStart;

	putFreeBlock(Heap::_listStart, fb);
	_firstFree = (FreeBlock*)_listStart;
}

void Heap::putFreeBlock(void* startBit, FreeBlock fb)
{
	*(int*)startBit = fb.lfb;	
	
	*((int*) (startBit) +1) = fb.length;
	//* ((int *)startBit + sizeof(int)) = fb.length;
	
	//auto addr = (FreeBlock*)((int*)(startBit)+2);



	*((int*)(startBit)+2) = (int)fb.next;


	

	void* startData = (FreeBlock**) ((int*)startBit + 2) + 1; 

	for (size_t i = 0; i < fb.length; i++)
	{
		*((char*)startData +i) = 0;
	}
}

void Heap::dump()
{
	for (size_t i = 0; i < 20; i++)
	{
		cout << *((int*)Heap::_listStart + i) << endl;
	}

	cout << "dump finished"<<endl;
}


//Returns the address of the first free block. The reutrned pointer points to the first bit including the header infos)
//void* Heap::FirstFitAddress()
//{
//	return NULL;
//}

void* Heap::testAddMethod()
{

	return 0;
}

void* Heap::Alloc(int Size)
{
	FreeBlock* free = (FreeBlock*)_firstFree;
	FreeBlock* prev = free;

	int headerSize = sizeof(int);

	while (free->length > headerSize + Size && free != _firstFree)
	{
		prev = free;
		free = free->next;
	}

	if (free == _firstFree && free->length < Size + sizeof(int))
	{
		return NULL;
	}
	else
	{
		FreeBlock* b = free;
	
		void* startOfTheNewBlock = ((char*)free + sizeof(free->length) + sizeof(free->lfb) + sizeof(free->next) + free->length) - (Size + headerSize) ;
		*(int*)startOfTheNewBlock = 1;
		b->length = b->length - (Size)-headerSize;

		return (int*)startOfTheNewBlock+1;
	}
}