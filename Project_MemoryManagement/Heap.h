#pragma once

#include <string>
#include "FreeBlock.h"
#include <map>
#include "TypeDescriptorBase.h"
#include "GObject.h"

using namespace std;

class GObject;

class Heap
{
private:
	static const int LISTSIZE = 80; // 32000;

	static void* _listStart; //pointer to the start of the list
	static FreeBlock* _firstFree; //pointer to the first free block

	static void Heap::putFreeBlock(void* startBit, FreeBlock fb);
	static map<std::string, TypeDescriptorBase*> _descriptors;

	static void* alloc(int Size);//Finds the next free block and allocates space for the new object and returns the beginning of the block
	static void markNaive(GObject* Block);
	static void sweep();
	static GObject* findFirstObjectStart(); //returns the starting byte of the first object in the list
	static void dealloc(GObject* obj);
	static int* FindNextBlock(int* BlockStart);
	static FreeBlock* findFreeBlockBefore(GObject* object);

	Heap();	

public:
	static void initHeap();
	static void* alloc(std::string CName);
	static void dump();
	static void intDump();
	~Heap();

	static void* addTestObj();
	static void registerType(std::string Key, TypeDescriptorBase *Decriptor);

	static void gc(std::vector<GObject*> roots);
};

