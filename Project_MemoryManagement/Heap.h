#pragma once

#include <string>
#include "FreeBlock.h"
#include <map>
#include "TypeDescriptorBase.h"

using namespace std;

class Heap
{
private:
	static const int LISTSIZE = 80; // 32000;

	static void* _listStart; //pointer to the start of the list
	static FreeBlock* _firstFree; //pointer to the first free block

	static void Heap::putFreeBlock(void* startBit, FreeBlock fb);
	static map<std::string, TypeDescriptorBase> _descriptors;

	static void* alloc(int Size);//Finds the next free block and allocates space for the new object and returns the beginning of the block
	
	Heap();	
public:
	static void initHeap();
	static void* alloc(std::string CName);
	static void dump();
	~Heap();

	static void* addTestObj();
	static void registerType(std::string Key, TypeDescriptorBase &Decriptor);
};

