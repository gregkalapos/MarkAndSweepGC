#pragma once
class FreeBlock
{
public:
	FreeBlock(int _length);
	FreeBlock();
	~FreeBlock();

	const int lfb = 0;
	int length; //stores the length of the free block
	FreeBlock* next;
	
};