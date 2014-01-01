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

	if (!objStart)
	{
		return NULL;
	}

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

int* Heap::FindNextBlock(int* BlockStart)
{
	int size;
	if (*BlockStart == 1)
	{
		size = ((GObject*)((int*)BlockStart + 1))->_tag->GetObjectSize() + sizeof(int);
	}
	else
	{
		size = ((FreeBlock*)BlockStart)->length + sizeof(int) + sizeof(int) + sizeof(FreeBlock*);
	}

	void* nextStart = ((char*)BlockStart + size);
	if (nextStart < (char*)_listStart + LISTSIZE)
	{		
		return (int*)nextStart;
	}
	else
	{
		return NULL;
	}
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
	cout << "==========Start Dump============" << endl;

	int* actItem = (int*)_listStart;
	while (actItem != NULL)
	{
		if (*actItem == 0)
		{
			cout << "free block" << endl << "length: " << ((FreeBlock*)actItem)->length << endl << "address: " << &*((FreeBlock*)actItem) << endl << endl;
		}
		else
		{
			cout << "used block: " << endl << "class: " << ((GObject*)((int*)actItem + 1))->_tag->GetClassName() << endl << "address: " << &*(GObject*)((int*)actItem + 1) << endl << "size: " << ((GObject*)((int*)actItem + 1))->_tag->GetObjectSize() << endl << endl;
		}

		actItem = FindNextBlock(actItem);
	}

	cout << endl;

	FreeBlock* next = _firstFree->next;
	int FreeSize = _firstFree->length + sizeof(_firstFree->length) +  sizeof(_firstFree->next);
	while (next != _firstFree)
	{
		FreeSize += (next->length + sizeof(next->length) + sizeof(next->next));
		next = next->next;
	}

	cout << "Free space: " << FreeSize << endl;
	
	cout << "==========Dump finished============" << endl <<endl <<endl;
	
}

//Allocates a block of memory with size Size and returns the beginning of the block 
//(the returned address is the address after the leading 1 which marks that it is a used block)
void* Heap::alloc(int Size)
{
	if (!_firstFree)
	{
		return NULL;
	}
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
		
		auto newLength = b->length - (Size)-headerSize;

		if (free->length >= Size+headerSize) //if we can split the block... the next pointer remains the same!
		{
			free->length = newLength;
		}
		else if(free == prev) //last free block
		{
			_firstFree = NULL;
		}
		else //remove block from the list
		{
			prev->next = free->next;
		}

		return (int*)startOfTheNewBlock+1;
	}
}

void Heap::registerType(std::string Key, TypeDescriptorBase *Decriptor)
{
	_descriptors.insert(std::pair<std::string, TypeDescriptorBase*>(Key, Decriptor));
}

void Heap::dealloc(GObject* obj)
{
	int* actPos = (int*)_listStart;	
	int* posBefore = NULL;

	while ((char*)actPos != (char*)((int*)obj-1))
	{
		posBefore = (int*)actPos;
		actPos = FindNextBlock(actPos);
	}

	int* posAfter = FindNextBlock((int*)obj - 1);

	FreeBlock* newFb; //stores a reference to the freeblock which will be processed

	//process the leftnb
	if (*posBefore == 0)
	{
		((FreeBlock*)(posBefore))->length += ((GObject*)obj)->_tag->GetObjectSize() + sizeof(1);
		
		newFb = (FreeBlock*)posBefore;

		*((int*)obj - 1) = 0;
		auto objSize = obj->_tag->GetObjectSize();
		for (size_t i = 0; i < objSize; i++)
		{
			*((char*)obj + i) = 0;
		}
	}
	else
	{
		FreeBlock* lastFreeNb = findFreeBlockBefore(obj);

		FreeBlock fb(obj->_tag->GetObjectSize() + sizeof(int) - sizeof(int) - sizeof(int) - sizeof(FreeBlock*) );
		fb.next = lastFreeNb->next;		
		putFreeBlock(((int*)obj - 1), fb);
		lastFreeNb->next = (FreeBlock*)((int*)obj - 1);
		newFb = (FreeBlock*)((int*)obj - 1);
	}

	//process the rnb
	if (posAfter!= NULL && *posAfter == 0)
	{
		newFb->next = ((FreeBlock*)posAfter)->next;
		newFb->length += ( ((FreeBlock*)posAfter)->length + sizeof(((FreeBlock*)posAfter)->length) +
			sizeof(((FreeBlock*)posAfter)->lfb) + sizeof(((FreeBlock*)posAfter)->next) );

		((FreeBlock*)posAfter)->length = 0;
		((FreeBlock*)posAfter)->next = 0;		
	}

	//*((int*)obj - 1) = 0;
	//auto objSize = obj->_tag->GetObjectSize();
	//for (size_t i = 0; i < objSize; i++)
	//{
	//	*((char*)(obj)+i) = 0;
	//}
}

void Heap::intDump()
{
	for (size_t i = 0; i < (LISTSIZE/4); i++)
	{
		cout << *((int*)Heap::_listStart + i) << endl;
	}
}

FreeBlock* Heap::findFreeBlockBefore(GObject* object)
{
	FreeBlock* next = _firstFree->next;
	FreeBlock* lastNext = _firstFree;

	while (next != _firstFree && (char*)next < (char*)object)
	{
		lastNext = next;
		next = next->next;
	}

	return lastNext;
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

	sweep();
}

void Heap::sweep()
{
	auto aktObj = findFirstObjectStart();
	GObject* nextObject = NULL;

	if (aktObj == NULL)
	{
		return;
	}

	int* n = ((int*)aktObj - 1);
	bool isFinished = false;

	while (!isFinished)
	{	
		n = ((int*)aktObj - 1);
		do
		{		
			n = FindNextBlock(n);
		} while (n != NULL && *n != 1);

		if (n == NULL)
			isFinished = true;
		else
			nextObject = (GObject*)(n + 1);
		
		if (aktObj->_mark == 1)
		{
			aktObj->_mark = 0;
		}
		else
		{
			dealloc(aktObj);
		}

		aktObj = nextObject;
	}
}

GObject* Heap::findFirstObjectStart()
{
	for (size_t i = 0; i < LISTSIZE; i++)
	{
		if (*(int*)((char*)_listStart + i) == 1)
		{
			return (GObject*)((char*)_listStart + i + sizeof(int));
		}
	}
	return NULL;
}