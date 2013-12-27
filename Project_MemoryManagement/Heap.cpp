#include "Heap.h"
#include <iostream>
#include "TestClass.h"

void* Heap::_listStart = malloc(Heap::LISTSIZE);
FreeBlock* Heap::_firstFree;
map<std::string, TypeDescriptorBase*>  Heap::_descriptors;

Heap::Heap()
{
}

Heap::~Heap()
{
}

void* Heap::alloc(std::string CName)
{		
	if (!_descriptors.count(CName))
	{
		throw "Typedescriptor for the given class is not registered";
	}

	auto descriptor = _descriptors[CName];

	auto objStart =  alloc(descriptor->GetObjectSize());
	
	((GObject*)objStart)->_free = 0;
	((GObject*)objStart)->_mark = 0;
	((GObject*)objStart)->_tag = descriptor;

	//TODO set the pointers to NULL!
		
	return objStart;
}

void* Heap::addTestObj()
{
	auto retObject = (TestClass*)alloc(sizeof(TestClass));
	retObject->_free = 0;
	retObject->_mark = 0;

	auto tcdesc = _descriptors["TestClassDescriptor"];

	retObject->_tag = tcdesc;

	return retObject;
}


//Initialization of the heap. After this method the heap is 1 big free block.
void Heap::initHeap()
{	
	FreeBlock fb;
	
	auto blockInfoSize = sizeof(fb.lfb) + sizeof(fb.length) + sizeof(fb.next);
	fb.length = Heap::LISTSIZE - blockInfoSize;
	
	fb.next = (FreeBlock*)_listStart;

	putFreeBlock(Heap::_listStart, fb);
	_firstFree = (FreeBlock*)_listStart;
}

//Puts a freeblock at location contained by the startbit parameter and sets all the bytes to zero
void Heap::putFreeBlock(void* startBit, FreeBlock fb)
{
	*(int*)startBit = fb.lfb;		
	*((int*) (startBit) +1) = fb.length;
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

//Allocates a block of memory with size Size and returns the beginning of the block 
//(the returned address is the address after the leading 1 which marks that it is a use block)
void* Heap::alloc(int Size)
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

void Heap::registerType(std::string Key, TypeDescriptorBase *Decriptor)
{
	_descriptors.insert(std::pair<std::string, TypeDescriptorBase*>(Key, Decriptor));
}

void Heap::markNaive(GObject* Block)
{
	if (Block != NULL && !Block->_mark)
	{
		Block->_mark = 1;
				
		auto offsetVector = Block->_tag->GetOffsetList();	
		for each (auto offsetItem in  *offsetVector) 
		{
			markNaive(*(GObject**)((char*)(Block)+sizeof(GObject)+offsetItem));
		}		
	}
}

void Heap::gc(std::vector<GObject*> roots)
{
	for each (auto rootObject in roots)
	{
		markNaive(rootObject);
	}
}